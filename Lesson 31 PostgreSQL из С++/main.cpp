#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <pqxx/pqxx>
#include <locale.h>
#include <Windows.h>

std::string utf8_to_cp1251(std::string const& utf8)
{
  if (!utf8.empty())
  {
    int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
    if (wchlen > 0 && wchlen != 0xFFFD)
    {
      std::vector<wchar_t> wbuf(wchlen);
      int result_u = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
      if (!result_u) {
        throw std::runtime_error("utf8_to_cp1251 cannot convert MultiByteToWideChar!");
      }
      std::vector<char> buf(wchlen);
      int result_c = WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);
      if (!result_c) {
        throw std::runtime_error("utf8_to_cp1251 cannot convert WideCharToMultiByte!");
      }

      return std::string(&buf[0], wchlen);
    }
  }
  return std::string();
}

std::string cp1251_to_utf8(const std::string& cp1251) {
  std::string res;
  int result_u, result_c;
  enum { CP1251 = 1251 };

  result_u = MultiByteToWideChar(CP1251, 0, cp1251.c_str(), -1, 0, 0);
  if (!result_u) {
    throw std::runtime_error("cp1251_to_utf8 cannot convert MultiByteToWideChar!");
  }

  wchar_t* ures = new wchar_t[result_u];
  if (!MultiByteToWideChar(CP1251, 0, cp1251.c_str(), -1, ures, result_u)) {
    delete[] ures;
    throw std::runtime_error("cp1251_to_utf8 cannot convert MultiByteToWideChar 2!");
  }

  result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
  if (!result_c) {
    delete[] ures;
    throw std::runtime_error("cp1251_to_utf8 cannot convert WideCharToMultiByte!");
  }

  char* cres = new char[result_c];
  if (!WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0)) {
    delete[] cres;
    throw std::runtime_error("cp1251_to_utf8 cannot convert WideCharToMultiByte 2!");
  }

  delete[] ures;
  res.append(cres);
  delete[] cres;
  return res;
}

void printOutput(const std::string& data)
{
  std::string output = data;
  output = utf8_to_cp1251(output);
  std::cout << output;
  std::cout.flush();
}
std::string readInput()
{
  std::string input;
  std::getline(std::cin, input);
  input = cp1251_to_utf8(input);
  return input;
}

class ClientManager {
private:
  std::unique_ptr<pqxx::connection> conn;

public:
  ClientManager(const std::string& conn_str) {
    try {
      conn = std::make_unique<pqxx::connection>(conn_str);
      if (!conn->is_open()) {
        throw std::runtime_error("Can't open database connection");
      }
    }
    catch (const std::exception& e) {
      throw std::runtime_error("Database connection failed: " + std::string(e.what()));
    }
  }

  ~ClientManager() {
    if (conn && conn->is_open()) {
      conn->close();
    }
  }

  void createDatabaseStructure() {
    pqxx::work txn(*conn);

    try {
      txn.exec(
        "CREATE TABLE IF NOT EXISTS clients ("
        "id SERIAL PRIMARY KEY,"
        "first_name VARCHAR(50) NOT NULL,"
        "last_name VARCHAR(50) NOT NULL,"
        "email VARCHAR(100) UNIQUE NOT NULL"
        ")"
      );

      txn.exec(
        "CREATE TABLE IF NOT EXISTS client_phones ("
        "id SERIAL PRIMARY KEY,"
        "client_id INTEGER NOT NULL REFERENCES clients(id) ON DELETE CASCADE,"
        "phone VARCHAR(20) UNIQUE"
        ")"
      );

      txn.commit();
      std::cout << "Database structure created successfully" << std::endl;
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to create database structure: " + std::string(e.what()));
    }
  }

  int addClient(const std::string& first_name, const std::string& last_name, const std::string& email) {
    pqxx::work txn(*conn);
    
    try {
      pqxx::result r = txn.exec_params(      
        "INSERT INTO clients (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING id",
        cp1251_to_utf8(first_name), cp1251_to_utf8(last_name), email
      );

      int client_id = r[0][0].as<int>();
      txn.commit();
      return client_id;
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to add client: " + std::string(e.what()));
    }
  }

  int addPhone(int client_id, const std::string& phone) {
    pqxx::work txn(*conn);

    try {
      pqxx::result r = txn.exec_params(
        "INSERT INTO client_phones (client_id, phone) VALUES ($1, $2) RETURNING id",
        client_id, phone
      );
      int phone_id = r[0][0].as<int>();
      txn.commit();
      return phone_id;
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to add phone: " + std::string(e.what()));
    }
    
  }

  void updateClient(int client_id, const std::string& first_name, const std::string& last_name, const std::string& email) {
    pqxx::work txn(*conn);

    try {
      txn.exec_params(
        "UPDATE clients SET first_name = $1, last_name = $2, email = $3 WHERE id = $4",
        cp1251_to_utf8(first_name), cp1251_to_utf8(last_name), email, client_id
      );

      txn.commit();
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to update client: " + std::string(e.what()));
    }
  }

  void deletePhone(int phone_id) {
    pqxx::work txn(*conn);

    try {
      txn.exec_params(
        "DELETE FROM client_phones WHERE id = $1",
        phone_id
      );

      txn.commit();
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to delete phone: " + std::string(e.what()));
    }
  }

  void deleteClient(int client_id) {
    pqxx::work txn(*conn);

    try {
      txn.exec_params(
        "DELETE FROM clients WHERE id = $1",
        client_id
      );

      txn.commit();
    }
    catch (const std::exception& e) {
      txn.abort();
      throw std::runtime_error("Failed to delete client: " + std::string(e.what()));
    }
  }

  std::vector<std::tuple<int, std::string, std::string, std::string, std::vector<std::string>>>
    findClients(const std::string& search_term) {
    pqxx::read_transaction txn(*conn);
    std::vector<std::tuple<int, std::string, std::string, std::string, std::vector<std::string>>> results;

    try {     
      pqxx::result r = txn.exec_params(
        "SELECT c.id, c.first_name, c.last_name, c.email, "
        "ARRAY(SELECT phone FROM client_phones cp WHERE cp.client_id = c.id) as phones "
        "FROM clients c "
        "WHERE c.first_name LIKE '%' || $1 || '%' "
        "OR c.last_name LIKE '%' || $1 || '%' "
        "OR c.email LIKE '%' || $1 || '%' "
        "OR EXISTS ("
        "  SELECT 1 FROM client_phones cp "
        "  WHERE cp.client_id = c.id AND cp.phone LIKE '%' || $1 || '%'"
        ")",
        cp1251_to_utf8(search_term)
      );

      for (const auto& row : r) {
        int id = row[0].as<int>();
        std::string first_name = row[1].as<std::string>();
        std::string last_name = row[2].as<std::string>();
        std::string email = row[3].as<std::string>();

        std::vector<std::string> phones;
        if (!row[4].is_null()) {
          pqxx::array_parser parser = row[4].as_array();
          auto [type, phone] = parser.get_next();
          while (type != pqxx::array_parser::juncture::done) {
            if (type == pqxx::array_parser::juncture::string_value) {
              phones.push_back(phone);
            }
            std::tie(type, phone) = parser.get_next();
          }
        }

        results.emplace_back(id, first_name, last_name, email, phones);
      }

      return results;
    }
    catch (const std::exception& e) {
      throw std::runtime_error("Failed to find clients: " + std::string(e.what()));
    }
  }

  void printAllClients() {
    pqxx::read_transaction txn(*conn);

    try {
      pqxx::result r = txn.exec(
        "SELECT c.id, c.first_name, c.last_name, c.email, "
        "ARRAY(SELECT phone FROM client_phones cp WHERE cp.client_id = c.id) as phones "
        "FROM clients c"
      );

      std::cout << "All clients (" << r.size() << "):" << std::endl;
      for (const auto& row : r) {
        std::cout << "ID: " << row[0].as<int>() << std::endl;
        std::cout << "Name: " << row[1].as<std::string>() << " " << row[2].as<std::string>() << std::endl;
        std::cout << "Email: " << row[3].as<std::string>() << std::endl;

        std::cout << "Phones: ";
        if (row[4].is_null()) {
          std::cout << "none" << std::endl;
        }
        else {
          pqxx::array_parser parser = row[4].as_array();
          bool first = true;
          auto [type, phone] = parser.get_next();
          while (type != pqxx::array_parser::juncture::done) {
            if (type == pqxx::array_parser::juncture::string_value) {
              if (!first) std::cout << ", ";
              std::cout << phone;
              first = false;
            }
            std::tie(type, phone) = parser.get_next();
          }
          std::cout << std::endl;
        }
        std::cout << "---------------------" << std::endl;
      }
    }
    catch (const std::exception& e) {
      throw std::runtime_error("Failed to retrieve clients: " + std::string(e.what()));
    }
  }
};

int main() {

  setlocale(LC_ALL, "ru_RU.UTF-8");
  std::locale::global(std::locale("ru_RU.UTF-8"));

  try {
    std::string conn_str = "host = localhost "
      "port=5432 "
      "dbname=testdb "
      "user=postgres "
      "password=1248892 ";

    ClientManager manager(conn_str);

    manager.createDatabaseStructure();

    int client_id = manager.addClient("Иван", "Иванов", "ivan@example.com");
    std::cout << "Added client with ID: " << client_id << std::endl ;

    int client_id_1 = manager.addClient("Петр", "Петров", "petr@example.com");
    std::cout << "Added client with ID: " << client_id_1 << std::endl;

    int phone_id = manager.addPhone(client_id, "+79161234563");
    int phone_id_1 = manager.addPhone(client_id, "+74951234564");
    int phone_id_2 = manager.addPhone(client_id_1, "+74951234567");

    manager.updateClient(client_id, "Иван", "Петров", "ivan.petrov@example.com");

    std::cout << std::endl;

    manager.printAllClients();

    std::cout << std::endl;

    std::cout << "Searching for '" << cp1251_to_utf8("Иван") << "':" << std::endl;

    auto found_clients = manager.findClients("Иван");
    for (const auto& client : found_clients) {
      auto [id, first_name, last_name, email, phones] = client;
      std::cout << "Found client: " << first_name << " " << last_name << " (" << email << ")" << std::endl;
      std::cout << "Phones: ";
      for (const auto& phone : phones) {
        std::cout << phone << " ";
      }
      std::cout << std::endl;
    } 

    manager.deletePhone(phone_id_1);
    manager.deleteClient(client_id_1);

    std::cout << std::endl;

    manager.printAllClients();
  }
  catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}