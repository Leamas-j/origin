#include "sqlselectquerybuilder.h"


int main()
{
  SqlSelectQueryBuilder query_builder;
  query_builder.AddFrom("students");
  query_builder.AddWhere("course", "C++");
  query_builder.AddColumn("id");

  std::map<std::string, std::string> map_where;
  map_where["id"] = "42";
  map_where["name"] = "John";
  query_builder.AddWhere(map_where);

  query_builder.AddColumns({ "name", "phone" });

  query_builder.BuildQuery();

  return 0;
}
