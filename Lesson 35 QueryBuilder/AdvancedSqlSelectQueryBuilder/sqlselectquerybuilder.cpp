#include "sqlselectquerybuilder.h"

SqlSelectQueryBuilder::SqlSelectQueryBuilder() {}

Query SqlSelectQueryBuilder::BuildQuery() noexcept
{
  std::string select_all{ "*" };
  if (query.nameColumn_.empty()) {
    query.nameColumn_ = select_all;
  }

  std::cout << "SELECT " << query.nameColumn_ << " FROM " << query.nameTable_ << query.where_ << ";" << std::endl;

  return query;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& nameColumn) noexcept
{
  std::string more_column{ ", " + nameColumn };
  check_empty(query.nameColumn_, nameColumn, more_column);
  return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept
{
  std::string more_column{ ", " };
  std::string empty_str;
  check_empty(query.nameColumn_, empty_str, more_column);

  for (size_t i = 0; i < columns.size(); ++i)
  {
    query.nameColumn_ += columns[i];
    if ((i + 1) != columns.size())
    {
      query.nameColumn_ += more_column;
    }
  }
  return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& nameTable) noexcept
{
  query.nameTable_ = nameTable;
  return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& col_name, const std::string& cond) noexcept
{
  std::string str_where{ " WHERE " };
  std::string str_and{ " AND " };
  check_empty(query.where_, str_where, str_and);

  query.where_ += (col_name + "=" + cond);

  return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept
{
  std::string str_where{ " WHERE " };
  std::string str_and{ " AND " };
  check_empty(query.where_, str_where, str_and);
  size_t i = 0;
  size_t total = kv.size();

  for (const auto& k : kv)
  {
    query.where_ += (k.first + "=" + k.second);
    if (i++ < total - 1)
    {
      query.where_ += str_and;
    }
  }
  return *this;
}

void SqlSelectQueryBuilder::check_empty(std::string& fild, const std::string& if_empty, const std::string& if_not_empty) noexcept
{
  if (fild.empty())
  {
    if (!if_empty.empty())
    {
      fild = if_empty;
    }
  }
  else
  {
    fild += if_not_empty;
  }
}

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddGreaterThan(const std::string& col_name, const std::string& value) noexcept
{
  return AddCondition(col_name, ">", value);
}

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddLessThan(const std::string& col_name, const std::string& value) noexcept
{
  return AddCondition(col_name, "<", value);
}

AdvancedSqlSelectQueryBuilder& AdvancedSqlSelectQueryBuilder::AddCondition(const std::string& col_name, const std::string& op, const std::string& value) noexcept
{
  std::string str_where{ " WHERE " };
  std::string str_and{ " AND " };
  check_empty(query.where_, str_where, str_and);

  query.where_ += (col_name + op + value);

  return *this;
}