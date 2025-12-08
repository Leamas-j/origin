# pragma once

#include "iostream"
#include <map>
#include <vector>
#include <string>

struct Query {
  uint8_t id_;
  std::string name_;
  std::string phone_;
  std::string nameColumn_;
  std::string nameTable_;
  std::string where_;
};

class SqlSelectQueryBuilder {
public:
  explicit SqlSelectQueryBuilder();
  Query BuildQuery() noexcept;
  SqlSelectQueryBuilder& AddColumn(const std::string& nameColumn) noexcept;
  SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
  SqlSelectQueryBuilder& AddFrom(const std::string& nameTable) noexcept;
  SqlSelectQueryBuilder& AddWhere(const std::string& col_name, const std::string& cond) noexcept;
  SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
  void check_empty(std::string& fild, const std::string& if_empty, const std::string& if_not_empty) noexcept;
protected:
  Query query;
};

class AdvancedSqlSelectQueryBuilder : public SqlSelectQueryBuilder {
public:
  AdvancedSqlSelectQueryBuilder& AddGreaterThan(const std::string& col_name, const std::string& value) noexcept;
  AdvancedSqlSelectQueryBuilder& AddLessThan(const std::string& col_name, const std::string& value) noexcept;
  AdvancedSqlSelectQueryBuilder& AddCondition(const std::string& col_name, const std::string& op, const std::string& value) noexcept;
};