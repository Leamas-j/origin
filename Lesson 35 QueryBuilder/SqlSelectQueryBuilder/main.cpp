#include "sqlselectquerybuilder.h"


int main()
{
  SqlSelectQueryBuilder query_builder;
  query_builder.AddColumn("name").AddColumn("phone");
  query_builder.AddFrom("students");
  query_builder.AddWhere("id", "42").AddWhere("name", "John");

  query_builder.BuildQuery();

  return 0;
}
