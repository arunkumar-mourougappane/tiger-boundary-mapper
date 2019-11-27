#include <psql_wrapper.h>

CPSQLWrapper::CPSQLWrapper(std::string& dbHostname, std::string& dbName, std::string& dbPassword)
{
   mDbHost=dbHostname;
   mDbName=dbName;
   mDbPassword=dbPassword;
   mDbConnection = std::make_unique<PGConn>();
   mQueryResult = std::make_unique<PGresult>();
}

int_least32_t CPSQLWrapper::processQuery(const std::string& queryString)
{

   mQueryResult = std::unique_ptr <PGresult>( PQexec(mDbConnection.get(), queryString.c_str()));
   if(( PQresultStatus(mQueryResult.get()) == PGRES_COMMAND_OK) || ( PQresultStatus(mQueryResult.get()) == PGRES_TUPLES_OK))
   {
      return 0;
   }
   mQueryResult.reset();
   return -1;
}


int_least32_t CPSQLWrapper::openConnection()
{
   std::string connectionString = std::string("host=") + mDbHost + std::string(" dbname=") + mDbName + std::string(" password=") + mDbPassword;
   mDbConnection = std::unique_ptr( PQconnectdb(connectionString));
   if(PQstatus(mDbConnection) != CONNECTION_OK)
   {
      return -1;
   }
   return 0;
}

int_least32_t CCensusFileManager::closeConnection()
{
   if(PQstatus(mDbConnection.get()) == CONNECTION_OK)
   {
      PQfinish(mDbConnection.get());
      return 0;
   }
   return -1;
}

