
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
#include <postgresql/libpq-fe.h>
#include <string>
#include <cstdlib>
#include <memory>

class CPSQLWrapper
{
   private:
      std::unique_ptr<PGconn> mDbConnection;
      std::unique_ptr<PGresult> mQueryResult;
      std::string mDbHost;
      std::string mDbName;
      std::string mDbPassword;
   public:
      int_least32_t openConnection();
      int_least32_t closeConnection();
      CPSQLWrapper();
      CPSQLWrapper(std::string& dbHostname, std::string& dbName, std::string& dbPassword);
      ~CPSQLWrapper();
      int_least32_t processQuery(const std::string& queryString);
};
// CENSUS_BND_FILE_PARSER ends here.
#endif