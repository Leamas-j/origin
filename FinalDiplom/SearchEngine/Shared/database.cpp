#include <iostream>
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
std::vector<DataBase::SearchResult> DataBase::selectDocuments(const std::vector<std::string>& words)
{
  if (words.empty())
  {
    return {};
  }

  std::lock_guard<std::mutex> lock(mutex_);
  pqxx::work txn(*conn_);

  try 
  {
    std::string placeholders;
    for (size_t i = 0; i < words.size(); ++i) {
      if (i > 0) {
        placeholders += ", ";
      }
      placeholders += "$" + std::to_string(i + 1);
    }
  
    std::string query =
      "SELECT d.id, d.doc_name, SUM(dw.words_count) as total_relevance "
      "FROM documents d "
      "JOIN documents_words dw ON dw.doc_id = d.id "
      "JOIN words w ON w.id = dw.word_id "
      "WHERE w.word IN (" + placeholders + ") "
      "GROUP BY d.id, d.doc_name "
      "HAVING COUNT(DISTINCT w.id) = " + std::to_string(words.size()) + " "
      "ORDER BY total_relevance DESC;";

    pqxx::params params;
    for (const auto& word : words) 
    {
      params.append(word);
    }

    pqxx::result res = txn.exec(query, params);
    txn.commit();

    std::vector<SearchResult> results;
    for (const auto& row : res) 
    {
      results.push_back({
          row["id"].as<int>(),
          row["doc_name"].as<std::string>(),
          row["total_relevance"].as<int>()
        });
    }

    return results;
  }
  catch (const std::exception& e) 
  {
    txn.abort();
    throw std::runtime_error("Failed to select documents: " + std::string(e.what()));
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