#include "database.h"

DataBase::DataBase(const std::string& str_connect)
{
  conn_ = std::make_unique<pqxx::connection>(str_connect);

  if (!conn_->is_open())
  {
    throw std::runtime_error("Can`t open database connection!");
  }
  else std::cout << "Database connect!" << std::endl;

  createDatabaseStructure();
}

int DataBase::addWord(const std::string& word)
{
  std::lock_guard<std::mutex> lock(mutex_);

  pqxx::work txn(*conn_);

  try {
    pqxx::result check = txn.exec(
      "SELECT id FROM words WHERE word = $1",
      pqxx::params{ word }
    );

    if (!check.empty())
    {
      txn.commit();
      return check[0][0].as<int>();
    }

    pqxx::result r = txn.exec(
      "INSERT INTO words (word) values ($1) RETURNING id",
      pqxx::params{ word }
    );

    int word_id = r[0][0].as<int>();   
    txn.commit();
    return word_id;   
  }
  catch (const std::exception& e) 
  {
    txn.abort();
    std::cerr << "Filed to add word: " << std::string(e.what());
  }
}

int DataBase::addDocument(const std::string& document)
{
  std::lock_guard<std::mutex> lock(mutex_);

  pqxx::work txn(*conn_);

  try {
    pqxx::result r = txn.exec(
      "INSERT INTO documents (doc_name) values ($1) RETURNING id",
      pqxx::params{ document }
    );

    int doc_id = r[0][0].as<int>();    
    txn.commit();
    return doc_id;
   
  }
  catch (const std::exception& e) {
    txn.abort();
    std::cerr << "Filed to add document: " << std::string(e.what());
  }
}

void DataBase::addWordsDocuments(const int& document_id, const int& word_id, const int& words_count)
{
  std::lock_guard<std::mutex> lock(mutex_);

  pqxx::work txn(*conn_);

  try {
    pqxx::result r = txn.exec(
      "INSERT INTO documents_words (doc_id, word_id, words_count) values ($1, $2, $3)",
      pqxx::params{ document_id, word_id, words_count }
    );

    txn.commit();
  }
  catch (const std::exception& e) {
    txn.abort();
    std::cerr << "Filed to add words count : " <<  std::string(e.what());
  }
}
void  DataBase::createDatabaseStructure()
{
  pqxx::work txn(*conn_);

  try {
    txn.exec(
      "CREATE TABLE IF NOT EXISTS documents ("
      "id SERIAL PRIMARY KEY,"
      "doc_name VARCHAR(200) UNIQUE NOT NULL"
      ")"
    );

    txn.exec(
      "CREATE TABLE IF NOT EXISTS words ("
      "id SERIAL PRIMARY KEY,"
      "word VARCHAR(80) UNIQUE NOT NULL"
      ")"
    );

    txn.exec(
      "CREATE TABLE IF NOT EXISTS documents_words ("
      "id SERIAL PRIMARY KEY,"
      "doc_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE,"
      "word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,"
      "words_count INTEGER NOT NULL"
      ")"
    );

    txn.commit();
  }
  catch (const std::exception& e) {
    txn.abort();
    throw std::runtime_error("Filed to create database structure: " + std::string(e.what()));
  }
}

DataBase :: ~DataBase()
{
  if (conn_ && conn_->is_open())
  {
    conn_->close();
  }
}

