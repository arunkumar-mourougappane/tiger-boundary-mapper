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
#include <memory>
#include <string_view>
#include <libpq-fe.h>

struct PGConnDeleter {
    void operator()(PGconn* conn) const { if (conn) PQfinish(conn); }
};

struct PGResultDeleter {
    void operator()(PGresult* res) const { if (res) PQclear(res); }
};

/**
 * @brief A class wrapper for libpq library to store, query result
 *        perform commands and handle connections.
 * 
 */
class CPSQLWrapper
{
   private:
      // PSQL database connection.
      std::unique_ptr<PGconn, PGConnDeleter> mDbConnection;
      // PSQL Quert Result
      std::unique_ptr<PGresult, PGResultDeleter> mQueryResult;
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
      CPSQLWrapper() = default;
      CPSQLWrapper(std::string_view dbHostname, std::string_view dbName, std::string_view dbUser, std::string_view dbPassword);
      ~CPSQLWrapper() = default;
      CPSQLWrapper(const CPSQLWrapper&) = delete; // Disable copy
      CPSQLWrapper& operator=(const CPSQLWrapper&) = delete; // Disable assignment
      CPSQLWrapper(CPSQLWrapper&&) = default; // Enable move
      CPSQLWrapper& operator=(CPSQLWrapper&&) = default; // Enable move assignment

      ExecStatusType processQuery(std::string_view queryString);
      ExecStatusType processExecParamsQuery(std::string_view queryToPrep, int_least32_t nParams, const char * const *paramValues, const int *paramLengths);
      [[nodiscard]] std::string_view getDbName() const;
      [[nodiscard]] std::string getQueryErrorMessage() const;
      [[nodiscard]] int_least32_t GetResultSetSize() const;
      [[nodiscard]] int_least32_t GetColumnSize() const;
      [[nodiscard]] PGresult* GetQueryResult() const;
};
// CENSUS_BND_FILE_PARSER ends here.
#endif