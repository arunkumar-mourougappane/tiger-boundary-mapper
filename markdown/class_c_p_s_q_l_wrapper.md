
# Class CPSQLWrapper


[**Class List**](../README.md) **>** [**CPSQLWrapper**](class_c_p_s_q_l_wrapper.md)



_A class wrapper for libpq library to store, query result perform commands and handle connections._ 

* `#include <psql_wrapper.h>`















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CPSQLWrapper**](class_c_p_s_q_l_wrapper.md#function-cpsqlwrapper-1-2) () <br> |
|   | [**CPSQLWrapper**](class_c_p_s_q_l_wrapper.md#function-cpsqlwrapper-2-2) (std::string dbHostname, std::string dbName, std::string dbUser, std::string dbPassword) <br>_Construct a new_ [_**CPSQLWrapper**_](class_c_p_s_q_l_wrapper.md) _object._ |
|  int\_least32\_t | [**GetColumnSize**](class_c_p_s_q_l_wrapper.md#function-getcolumnsize) () <br>[_**GetColumnSize()**_](class_c_p_s_q_l_wrapper.md#function-getcolumnsize) _returns number of columns in the result set._ |
|  PGresult \* | [**GetQueryResult**](class_c_p_s_q_l_wrapper.md#function-getqueryresult) () <br>[_**GetQueryResult()**_](class_c_p_s_q_l_wrapper.md#function-getqueryresult) _returns a pointer to the result set. WARNING: Treading with caution._ |
|  int\_least32\_t | [**GetResultSetSize**](class_c_p_s_q_l_wrapper.md#function-getresultsetsize) () <br>[_**GetResultSetSize()**_](class_c_p_s_q_l_wrapper.md#function-getresultsetsize) _returns the number of results returned by query._ |
|  int\_least32\_t | [**closeConnection**](class_c_p_s_q_l_wrapper.md#function-closeconnection) () <br>[_**closeConnection()**_](class_c_p_s_q_l_wrapper.md#function-closeconnection) _Cleanly closes an open connection._ |
|  const std::string | [**getDbName**](class_c_p_s_q_l_wrapper.md#function-getdbname) () const<br>[_**getDbName()**_](class_c_p_s_q_l_wrapper.md#function-getdbname) _returns an immuatble instance of database name._ |
|  std::string | [**getQueryErrorMessage**](class_c_p_s_q_l_wrapper.md#function-getqueryerrormessage) () <br>[_**getQueryErrorMessage()**_](class_c_p_s_q_l_wrapper.md#function-getqueryerrormessage) _returns the query result's error in human readable format._ |
|  int\_least32\_t | [**openConnection**](class_c_p_s_q_l_wrapper.md#function-openconnection) () <br>[_**openConnection()**_](class_c_p_s_q_l_wrapper.md#function-openconnection) _opens a connection with psql database using the given psql parameters. On success, the data connection pointer ,a member of the instance is populated and returns 0._ |
|  ExecStatusType | [**processExecParamsQuery**](class_c_p_s_q_l_wrapper.md#function-processexecparamsquery) (std::string queryToPrep, int\_least32\_t nParams, const char \*const \* paramValues, const int \* paramLengths) <br>_processExecParamsQuery(...) takes in a prepared statement, number of parameters, parameter values as an array, array of parameter value sizes and return status Type on failure, processes the statement; populates result set and return query execution status._  |
|  ExecStatusType | [**processQuery**](class_c_p_s_q_l_wrapper.md#function-processquery) (const std::string & queryString) <br>[_**processQuery(const std::string&)**_](class_c_p_s_q_l_wrapper.md#function-processquery) _processes a database query and returns a PSQL (libpq) status code._ |
|   | [**~CPSQLWrapper**](class_c_p_s_q_l_wrapper.md#function-cpsqlwrapper) () <br> |








## Public Functions Documentation


### <a href="#function-cpsqlwrapper-1-2" id="function-cpsqlwrapper-1-2">function CPSQLWrapper [1/2]</a>


```cpp
inline CPSQLWrapper::CPSQLWrapper () 
```



### <a href="#function-cpsqlwrapper-2-2" id="function-cpsqlwrapper-2-2">function CPSQLWrapper [2/2]</a>


```cpp
CPSQLWrapper::CPSQLWrapper (
    std::string dbHostname,
    std::string dbName,
    std::string dbUser,
    std::string dbPassword
) 
```




**Parameters:**


* `dbHostname` - database host(127.0.0.1) to connect 
* `dbName` - database name 
* `dbUser` - database username for credential 
* `dbPassword` - database password for credential 



        

### <a href="#function-getcolumnsize" id="function-getcolumnsize">function GetColumnSize </a>


```cpp
int_least32_t CPSQLWrapper::GetColumnSize () 
```




**Returns:**

int\_least32\_t Returns number of columns. 




        

### <a href="#function-getqueryresult" id="function-getqueryresult">function GetQueryResult </a>


```cpp
PGresult * CPSQLWrapper::GetQueryResult () 
```




**Returns:**

PGresult\* - pointer to query result. 




        

### <a href="#function-getresultsetsize" id="function-getresultsetsize">function GetResultSetSize </a>


```cpp
int_least32_t CPSQLWrapper::GetResultSetSize () 
```




**Returns:**

int\_least32\_t Returns number of results. 




        

### <a href="#function-closeconnection" id="function-closeconnection">function closeConnection </a>


```cpp
int_least32_t CPSQLWrapper::closeConnection () 
```




**Returns:**

int\_least32\_t - returned 0 on success and -1 on failure. 




        

### <a href="#function-getdbname" id="function-getdbname">function getDbName </a>


```cpp
const std::string CPSQLWrapper::getDbName () const
```




**Returns:**

const std::string 




        

### <a href="#function-getqueryerrormessage" id="function-getqueryerrormessage">function getQueryErrorMessage </a>


```cpp
std::string CPSQLWrapper::getQueryErrorMessage () 
```




**Returns:**

std::string - returns error message string. 




        

### <a href="#function-openconnection" id="function-openconnection">function openConnection </a>


```cpp
int_least32_t CPSQLWrapper::openConnection () 
```




**Returns:**

int\_least32\_t - returns 0 on success. 




        

### <a href="#function-processexecparamsquery" id="function-processexecparamsquery">function processExecParamsQuery </a>


```cpp
ExecStatusType CPSQLWrapper::processExecParamsQuery (
    std::string queryToPrep,
    int_least32_t nParams,
    const char *const * paramValues,
    const int * paramLengths
) 
```




**Parameters:**


* `queryToPrep` - Prepared query statement. 
* `nParams` - number of parameters to be used for the prepared query. 
* `paramValues` - Pointer to array of parameter values. 
* `paramLengths` - Pointer to array of sizes of parameters 



**Returns:**

ExecStatusType - Result status type to return. 




        

### <a href="#function-processquery" id="function-processquery">function processQuery </a>


```cpp
ExecStatusType CPSQLWrapper::processQuery (
    const std::string & queryString
) 
```




**Parameters:**


* `queryString` - database query as const string to be processed. 



**Returns:**

ExecStatusType - returns command status code. 




        

### <a href="#function-cpsqlwrapper" id="function-cpsqlwrapper">function ~CPSQLWrapper </a>


```cpp
inline CPSQLWrapper::~CPSQLWrapper () 
```



------------------------------
The documentation for this class was generated from the following file `include/psql_wrapper.h`