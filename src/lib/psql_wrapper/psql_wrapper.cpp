/**
 * @file psql_wrapper.cpp
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief Implementation of Postgresql wrapper API.
 * @version 1.0
 * @date 01-25-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <psql_wrapper.h>
#include <iostream>

/**
 * @brief Construct a new CPSQLWrapper object
 * 
 * @param dbHostname - database host(127.0.0.1) to connect
 * @param dbName - database name 
 * @param dbUser - database username for credential
 * @param dbPassword - database password for credential
 */
CPSQLWrapper::CPSQLWrapper(std::string dbHostname, std::string dbName, std::string dbUser, std::string dbPassword)
{
   mDbHost=dbHostname;
   mDbName=dbName;
   mDbPassword=dbPassword;
   mDbUser = dbUser;
   mDbConnection = nullptr;
   mQueryResult = nullptr;
}

/**
 * @brief processQuery(const std::string&) processes a database query
 *       and returns a PSQL (libpq) status code.
 * 
 * @param queryString - database query as const string to be processed.
 * @return ExecStatusType - returns command status code.
 */
ExecStatusType CPSQLWrapper::processQuery(const std::string& queryString)
{
   // Clear any previous result.
   if(mQueryResult != nullptr)
   {
      PQclear(mQueryResult);
   }
   // Save Result Information returned by executing the query.
   mQueryResult = PQexec(mDbConnection, queryString.c_str());
   // Parse and return status of Query.
   return PQresultStatus(mQueryResult);
}

/**
 * @brief  processExecParamsQuery(...) takes in a prepared statement, number of
 *         parameters, parameter values as an array, array of parameter value sizes
 *         and return status Type on failure, processes the statement; populates
 *         result set and return query execution status.
 * 
 * @param queryToPrep     - Prepared query statement.
 * @param nParams         - number of parameters to be used for the prepared query.
 * @param paramValues     - Pointer to array of parameter values.
 * @param paramLengths    - Pointer to array of sizes of parameters
 * @return ExecStatusType - Result status type to return.
 */
ExecStatusType CPSQLWrapper::processExecParamsQuery( std::string queryToPrep, int_least32_t nParams, const char * const *paramValues, const int *paramLengths)
{
   // Clear any previous result.
   if(mQueryResult != nullptr)
   {
      PQclear(mQueryResult);
   }
   // if no params are going to supplied we don't need a prepared statement.
   if((paramValues == nullptr) || (paramLengths == nullptr))
   {
      return PGRES_FATAL_ERROR;
   }
   // Prepare arguments.
   const char *command = queryToPrep.c_str();
   const int paramFormats[] = {0};
   // Actual query being processed.
   mQueryResult = PQexecParams(mDbConnection, command, nParams, NULL, paramValues, paramLengths, paramFormats, 0);
   // Parse and return status of Query.
   return PQresultStatus(mQueryResult);
}

/**
 * @brief getDbName() returns an immuatble instance of
 *        database name.
 * 
 * @return const std::string 
 */
const std::string CPSQLWrapper::getDbName() const
{
   return mDbName;
}

/**
 * @brief getQueryErrorMessage() returns the query result's error
 *        in human readable format.
 * 
 * @return std::string - returns error message string.
 */
std::string CPSQLWrapper::getQueryErrorMessage()
{
   return std::string (PQresultErrorMessage(mQueryResult));
}

/**
 * @brief openConnection() opens a connection with psql database
 *        using the given psql parameters. On success, the data
 *        connection pointer ,a member of the instance is populated
 *         and returns 0.
 * 
 * @return int_least32_t - returns 0 on success.
 */
int_least32_t CPSQLWrapper::openConnection()
{
   std::string connectionString = std::string("host=") + mDbHost + std::string(" dbname=") + 
      mDbName + std::string(" user=")+mDbUser+ std::string(" password=") + mDbPassword;
   mDbConnection =  PQconnectdb(connectionString.c_str());
   // Status of connection.
   if(PQstatus(mDbConnection) != CONNECTION_OK)
   {
      return -1;
   }
   return 0;
}

/**
 * @brief closeConnection() Cleanly closes an open connection.
 * 
 * @return int_least32_t - returned 0 on success and -1 on failure.
 */
int_least32_t CPSQLWrapper::closeConnection()
{
   if(PQstatus(mDbConnection) == CONNECTION_OK)
   {
      PQfinish(mDbConnection);
      return 0;
   }
   return -1;
}

/**
 * @brief GetResultSetSize() returns the number of results returned by query.
 * 
 * @return int_least32_t Returns number of results.
 */
int_least32_t CPSQLWrapper::GetResultSetSize()
{
   // if there is an actual query that has a result size then return it.
   if(( mQueryResult != NULL) && (PQresultStatus(mQueryResult) == PGRES_TUPLES_OK))
   {
      return PQntuples(mQueryResult);
   }
   return -1;
}

/**
 * @brief GetColumnSize() returns number of columns in the result set.
 * 
 * @return int_least32_t Returns number of columns.
 */
int_least32_t CPSQLWrapper::GetColumnSize()
{
   if(( mQueryResult != NULL) && (PQresultStatus(mQueryResult) == PGRES_TUPLES_OK))
   {
      return PQnfields(mQueryResult);
   }
   return -1;
}

/**
 * @brief GetQueryResult() returns a pointer to the result set.
 *        WARNING: Treading with caution.
 * 
 * @return PGresult* - pointer to query result.
 */
PGresult* CPSQLWrapper::GetQueryResult()
{
   return mQueryResult;
}