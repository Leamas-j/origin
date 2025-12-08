#include "sqlselectquerybuilder.h"

SqlSelectQueryBuilder:: SqlSelectQueryBuilder(){}

Query SqlSelectQueryBuilder:: BuildQuery() noexcept
{
    std::string select_all{"*"};
    if (query.nameColumn_.empty()) {
        query.nameColumn_ = select_all;
    }

    std::cout << "SELECT " << query.nameColumn_ << " FROM " << query.nameTable_ << query.where_ << ";" <<std::endl;

    return query;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& nameColumn) noexcept
{
    if(query.nameColumn_.empty())
    {
        query.nameColumn_ = nameColumn;
    }
    else{
        query.nameColumn_ += (", " + nameColumn);
    }
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& nameTable)
{
    query.nameTable_ = nameTable;
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& col_name, const std::string& cond)
{
    if(query.where_.empty())
    {
        query.where_ = " WHERE ";
    }
    else
    {
        query.where_ += " AND ";
    }
    query.where_ += (col_name + "=" + cond);
    return *this;
}
