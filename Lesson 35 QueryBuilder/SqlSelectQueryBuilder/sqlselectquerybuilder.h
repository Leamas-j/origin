# pragma once

#include "iostream"

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

    SqlSelectQueryBuilder& AddFrom(const std::string& nameTable);
    SqlSelectQueryBuilder& AddWhere(const std::string& col_name, const std::string& cond);
private:
    Query query;
};

