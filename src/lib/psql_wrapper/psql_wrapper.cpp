#include <psql_wrapper.h>

CPSQLWrapper::CPSQLWrapper(std::string dbHostname, std::string dbName, std::string dbPassword)
{
   mDbHost=dbHostname;
   mDbName=dbName;
   mDbPassword=dbPassword;
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
   std::string connectionString = std::string("host=") + mDbHost + std::string(" dbname=") + mDbName + std::string(" user=amouroug ")+ std::string(" password=") + mDbPassword;
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

