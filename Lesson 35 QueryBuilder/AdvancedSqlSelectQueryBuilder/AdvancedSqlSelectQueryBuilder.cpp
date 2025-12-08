#include "sqlselectquerybuilder.h"

int main()
{  
  AdvancedSqlSelectQueryBuilder query_builder;
  query_builder.AddColumns({ "name", "phone" });
  query_builder.AddFrom("students");
  query_builder.AddGreaterThan("id", "42");

  query_builder.BuildQuery();

  return 0;
}