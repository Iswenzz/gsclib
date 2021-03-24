#pragma once
#include <mysql.h>
#include <cgsc.h>

extern int mysql_library_init_code;

typedef struct
{
	MYSQL_BIND bind;
	void *buffer;
} MYSQL_BIND_BUFFER;

typedef struct 
{
	MYSQL *mysql;
	MYSQL_RES *result;
	MYSQL_STMT *stmt;
	MYSQL_BIND_BUFFER *binds;
	MYSQL_BIND_BUFFER *bindsResult;
	int bindsLength;
	int bindsResultLength;
} MYSQL_INSTANCE;

void MySQL_Free();

void MySQL_Free_Result();

void MySQL_Free_Statement();

int MySQL_TypeToGSC(enum_field_types type);

void MySQL_PrepareBindBuffer(MYSQL_BIND_BUFFER *b, const char *value, int valueLength, enum_field_types type);

void MySQL_FetchRowsInternal(qboolean all, qboolean stringIndexed);

void GScr_MySQL_Prepare();

void GScr_MySQL_BindParam();

void GScr_MySQL_BindResult();

void GScr_MySQL_Execute();

/**
 * @brief 
 * Print information about the MySQL client.
 */
void GScr_MySQL_Version();

/**
 * @brief 
 * Connect to a MySQL server.
 */
void GScr_MySQL_Connect();

/**
 * @brief 
 * Return the number of affected rows after a query.
 */
void GScr_MySQL_AffectedRows();

/**
 * @brief 
 * Close the MySQL connection.
 */
void GScr_MySQL_Close();

/**
 * @brief 
 * Select a MySQL database.
 */
void GScr_MySQL_SelectDB();

/**
 * @brief 
 * Get all database names.
 */
void GScr_MySQL_ListDB();

/**
 * @brief 
 * Get all table names.
 */
void GScr_MySQL_ListTables();

/**
 * @brief 
 * Command for performing a statement on the database server.
 */
void GScr_MySQL_Query();

/**
 * @brief 
 * Return the number of rows after a SELECT query.
 */
void GScr_MySQL_NumRows();

/**
 * @brief 
 * Return the number of fields after a SELECT query.
 */
void GScr_MySQL_NumFields();

/**
 * @brief 
 * Retrieve a single row data in a GSC array after a query.
 */
void GScr_MySQL_FetchRow();

/**
 * @brief 
 * Retrieve rows data in a two dimensional GSC array after a query.
 */
void GScr_MySQL_FetchRows();

/**
 * @brief 
 * Retrieve a single row data in a GSC string indexed array after a query.
 */
void GScr_MySQL_FetchRowDict();

/**
 * @brief 
 * Retrieve rows data in a two dimensional GSC string indexed array after a query.
 */
void GScr_MySQL_FetchRowsDict();

/**
 * @brief 
 * Retrieve all fields in a GSC array after a query.
 */
void GScr_MySQL_FetchFields();

/**
 * @brief 
 * Prepends backslashes to the following characters: \x00 , \n , \r , \ , ' , " and \x1a. 
 * This function must always (with few exceptions) be used to make data safe before sending a query to MySQL.
 */
void GScr_MySQL_EscapeString();

/**
 * @brief 
 * Return a hex representation of the string.
 */
void GScr_MySQL_HexString();