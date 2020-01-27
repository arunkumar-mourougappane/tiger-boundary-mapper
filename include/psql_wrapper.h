/**
 * @file psql_wrapper.h
 * @author Arunkumar Mourougappane (amouroug@buffalo.edu)
 * @brief A C++ wrapper across psql C API to perform queries,
 *        parse result sets and perform commands.
 * @version 1.1
 * @date 01-22-2020
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef PSQL_WRAPPER_H
#define PSQL_WRAPPER_H
#include <algorithm>
#include <libpq-fe.h>
#include <string>
#include <cstdlib>
/**
 * @brief A class wrapper for libpq library to store, query result
 *        perform commands and handle connections.
 * 
 */
class CPSQLWrapper
{
   private:
      // PSQL database connection.
      PGconn *mDbConnection;
      // PSQL Quert Result
      PGresult* mQueryResult;
      // Host to connect to
      std::string mDbHost;
      // Database Name
      std::string mDbName;
      // Database user information.
      std::string mDbUser;
      // Database password
      std::string mDbPassword;
   public:
      int_least32_t openConnection();
      int_least32_t closeConnection();
      CPSQLWrapper(){};
      CPSQLWrapper(std::string dbHostname, std::string dbName, std::string  dbUser, std::string dbPassword);
      ~CPSQLWrapper(){};
      ExecStatusType processQuery(const std::string& queryString);
      ExecStatusType processExecParamsQuery( std::string queryToPrep, int_least32_t nParams, const char * const *paramValues, const int *paramLengths);
      const std::string getDbName() const;
      std::string getQueryErrorMessage();
      int_least32_t GetResultSetSize();
      int_least32_t GetColumnSize();
      PGresult* GetQueryResult();
};
// CENSUS_BND_FILE_PARSER ends here.
#endif