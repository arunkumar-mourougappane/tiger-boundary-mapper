#include<iostream>
#include <libpq-fe.h>


int main()
{
   PGresult* mQueryResult;
   std::string connectionString = "host=127.0.0.1 dbname=amouroug user=amouroug password=FullMetalAlchemist#8";
   PGconn* mDbConnection =  PQconnectdb(connectionString.c_str());
   if(PQstatus(mDbConnection) != CONNECTION_OK)
   {
      return -1;
   }
   const char command[] = "SELECT * FROM COUNTY WHERE iname LIKE '%' || $1 || '%';";
   char iname[] = "Illinois";
   int nParams = 1;
   const char *const paramValues[] = {iname};
   const int paramLengths[] = {sizeof(iname)};
   const int paramFormats[] = {0};
   int resultFormat = 0;
   mQueryResult = PQexecParams(mDbConnection, command, nParams, NULL, paramValues, paramLengths, paramFormats, resultFormat);
   if (PQresultStatus(mQueryResult) != PGRES_TUPLES_OK) 
   {
      std::cout << "PQexecParams failed: " << PQresultErrorMessage(mQueryResult) << std::endl;
   }
   std::cout << PQntuples(mQueryResult);
   PQclear(mQueryResult);
   if(PQstatus(mDbConnection) == CONNECTION_OK)
   {
      PQfinish(mDbConnection);
   }
   return 0;
}