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
	MYSQL_RES *resultStmt;
	MYSQL_STMT *stmt;
	MYSQL_BIND_BUFFER *binds;
	MYSQL_BIND_BUFFER *bindsResult;
	int bindsLength;
	int bindsResultLength;
} MYSQL_INSTANCE;

/**
 * @brief 
 * Free all MySQL resources.
 */
void MySQL_Free();

/**
 * @brief 
 * Free the MySQL query & statement result.
 */
void MySQL_Free_Result();

/**
 * @brief 
 * Free the MySQL statement.
 */
void MySQL_Free_Statement();

/**
 * @brief 
 * Converts a MySQL type to a GSC variable type.
 * @param type - The MySQL type.
 * @return int - The GSC variable type.
 */
int MySQL_TypeToGSC(enum_field_types type);

/**
 * @brief 
 * Generic bind for a prepare statement.
 * @param b - The MySQL bind pointer.
 * @param value - The param bind value or NULL for a result bind.
 * @param valueLength - The length of the string to allocate (0 for other types).
 * @param type - The MySQL type to bind.
 */
void MySQL_PrepareBindBuffer(MYSQL_BIND_BUFFER *b, const char *value, int valueLength, enum_field_types type);

/**
 * @brief 
 * Generic fetch row function for both queries and statements.
 * @param all - Retrieve all rows or only one.
 * @param stringIndexed - Return as a string indexed array or a regular array.
 */
void MySQL_FetchRowsInternal(qboolean all, qboolean stringIndexed);

/**
 * @brief 
 * Prepare a MySQL statement.
 */
void GScr_MySQL_Prepare();

/**
 * @brief 
 * Bind a value param for the MySQL statement.
 */
void GScr_MySQL_BindParam();

/**
 * @brief 
 * Bind a result param for the MySQL statement.
 */
void GScr_MySQL_BindResult();

/**
 * @brief 
 * Execute the MySQL statement.
 */
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