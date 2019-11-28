
/***********************************************************
 * 
 *   File: psql_wrapper.h
 * 
 *   Author: Arunkumar Mourougappane 
 * 
 *   Copyright 2019.          Language: C++11
 * 
 ***********************************************************/
#ifndef PSQL_WRAPPER_H
#define PSQL_WRAPPER_H
#include <algorithm>
#include <libpq-fe.h>
#include <string>
#include <cstdlib>

class CPSQLWrapper
{
   private:
      PGconn *mDbConnection;
      PGresult* mQueryResult;
      std::string mDbHost;
      std::string mDbName;
      std::string mDbPassword;
   public:
      int_least32_t openConnection();
      int_least32_t closeConnection();
      CPSQLWrapper(){};
      CPSQLWrapper(std::string dbHostname, std::string dbName, std::string dbPassword);
      ~CPSQLWrapper(){};
      ExecStatusType processQuery(const std::string& queryString);
      const std::string getDbName() const;
      std::string getQueryErrorMessage();

};
// CENSUS_BND_FILE_PARSER ends here.
#endif