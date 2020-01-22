#include <psql_wrapper.h>
#include <iostream>

CPSQLWrapper::CPSQLWrapper(std::string dbHostname, std::string dbName, std::string dbUser, std::string dbPassword)
{
   mDbHost=dbHostname;
   mDbName=dbName;
   mDbPassword=dbPassword;
   mDbUser = dbUser;
   mDbConnection = nullptr;
   mQueryResult = nullptr;
}

ExecStatusType CPSQLWrapper::processQuery(const std::string& queryString)
{
   if(mQueryResult != nullptr)
   {
      PQclear(mQueryResult);
   }
   mQueryResult = PQexec(mDbConnection, queryString.c_str());
   return PQresultStatus(mQueryResult);

}

ExecStatusType CPSQLWrapper::processExecParamsQuery( std::string queryToPrep, int_least32_t nParams, const char * const *paramValues, const int *paramLengths)
{
   if(mQueryResult != nullptr)
   {
      PQclear(mQueryResult);
   }
   if((paramValues == nullptr) || (paramLengths == nullptr))
   {
      return PGRES_FATAL_ERROR;
   }
   const char *command = queryToPrep.c_str();
   const int paramFormats[] = {0};
   
   mQueryResult = PQexecParams(mDbConnection, command, nParams, NULL, paramValues, paramLengths, paramFormats, 0);
   return PQresultStatus(mQueryResult);
}
const std::string CPSQLWrapper::getDbName() const
{
   return mDbName;
}

std::string CPSQLWrapper::getQueryErrorMessage()
{
   return std::string (PQresultErrorMessage(mQueryResult));
}


int_least32_t CPSQLWrapper::openConnection()
{
   std::string connectionString = std::string("host=") + mDbHost + std::string(" dbname=") + 
      mDbName + std::string(" user=")+mDbUser+ std::string(" password=") + mDbPassword;
   mDbConnection =  PQconnectdb(connectionString.c_str());
   if(PQstatus(mDbConnection) != CONNECTION_OK)
   {
      return -1;
   }
   return 0;
}

int_least32_t CPSQLWrapper::closeConnection()
{
   if(PQstatus(mDbConnection) == CONNECTION_OK)
   {
      PQfinish(mDbConnection);
      return 0;
   }
   return -1;
}

int_least32_t CPSQLWrapper::GetResultSetSize()
{
   if(( mQueryResult != NULL) && (PQresultStatus(mQueryResult) == PGRES_TUPLES_OK))
   {
      return PQntuples(mQueryResult);
   }
   return -1;
}

int_least32_t CPSQLWrapper::GetColumnSize()
{
   if(( mQueryResult != NULL) && (PQresultStatus(mQueryResult) == PGRES_TUPLES_OK))
   {
      return PQnfields(mQueryResult);
   }
   return -1;
}
PGresult* CPSQLWrapper::GetQueryResult()
{
   return mQueryResult;
}