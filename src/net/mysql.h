#pragma once
#include <mysql.h>
#include <CGSC/cgsc.h>

#define MYSQL_ERROR(x, msg)	\
if (x == NULL)				\
{							\
	Plugin_Scr_Error(msg);	\
	return;					\
}

#define CHECK_MYSQL_INSTANCE()	MYSQL_ERROR(mysql.handle, "MySQL connection not found.");
#define CHECK_MYSQL_STMT()		MYSQL_ERROR(mysql.stmt, "MySQL statement not found.");

extern int MySQLcode;

typedef struct 
{
	MYSQL *handle;
	MYSQL_RES *result;
	MYSQL_RES *resultStmt;
	MYSQL_STMT *stmt;
	MYSQL_BIND *binds;
	MYSQL_BIND *bindsResult;
	int bindsLength;
	int bindsResultLength;
} MYSQL_INSTANCE;

/// <summary>
/// Free all MySQL resources.
/// </summary>
void MySQL_Free();

/// <summary>
/// Free the MySQL query & statement result.
/// </summary>
void MySQL_Free_Result();

/// <summary>
/// Free the MySQL statement.
/// </summary>
void MySQL_Free_Statement();

/// <summary>
/// Converts a MySQL type to a GSC variable type.
/// </summary>
/// <param name="type">The MySQL type.</param>
/// <returns>The GSC variable type.</returns>
int MySQL_TypeToGSC(enum_field_types type);

/// <summary>
/// Generic bind for a prepare statement.
/// </summary>
/// <param name="b">The MySQL bind pointer.</param>
/// <param name="value">The param bind value or NULL for a result bind.</param>
/// <param name="valueLength">The length of the string to allocate (0 for other types).</param>
/// <param name="type">The MySQL type to bind.</param>
void MySQL_PrepareBindBuffer(MYSQL_BIND* b, void *value, int valueLength, enum_field_types type);

/// <summary>
/// Prepare a MySQL statement.
/// </summary>
void GScr_MySQL_Prepare();

/// <summary>
/// Bind a value param for the MySQL statement.
/// </summary>
void GScr_MySQL_BindParam();

/// <summary>
/// Bind a result param for the MySQL statement.
/// </summary>
void GScr_MySQL_BindResult();

/// <summary>
/// Execute the MySQL statement.
/// </summary>
void GScr_MySQL_Execute();

/// <summary>
/// Print information about the MySQL client.
/// </summary>
void GScr_MySQL_Version();

/// <summary>
/// Connect to a MySQL server.
/// </summary>
void GScr_MySQL_Connect();

/// <summary>
/// Return the number of affected rows after a query.
/// </summary>
void GScr_MySQL_AffectedRows();

/// <summary>
/// Close the MySQL connection.
/// </summary>
void GScr_MySQL_Close();

/// <summary>
/// Select a MySQL database.
/// </summary>
void GScr_MySQL_SelectDB();

/// <summary>
/// Get all database names.
/// </summary>
void GScr_MySQL_ListDB();

/// <summary>
/// Get all table names.
/// </summary>
void GScr_MySQL_ListTables();

/// <summary>
/// Command for performing a statement on the database server.
/// </summary>
void GScr_MySQL_Query();

/// <summary>
/// Return the number of rows after a SELECT query.
/// </summary>
void GScr_MySQL_NumRows();

/// <summary>
/// Return the number of fields after a SELECT query.
/// </summary>
void GScr_MySQL_NumFields();

/// <summary>
/// Retrieve a single row data in a GSC array after a query.
/// </summary>
void GScr_MySQL_FetchRow();

/// <summary>
/// Retrieve rows data in a two dimensional GSC array after a query.
/// </summary>
void GScr_MySQL_FetchRows();

/// <summary>
/// Retrieve a single row data in a GSC string indexed array after a query.
/// </summary>
void GScr_MySQL_FetchRowDict();

/// <summary>
/// Retrieve rows data in a two dimensional GSC string indexed array after a query.
/// </summary>
void GScr_MySQL_FetchRowsDict();

/// <summary>
/// Retrieve all fields in a GSC array after a query.
/// </summary>
void GScr_MySQL_FetchFields();

/// <summary>
/// Prepends backslashes to the following characters: \x00 , \n , \r , \ , ' , " and \x1a. 
/// This function must always(with few exceptions) be used to make data safe before sending a query to MySQL.
/// </summary>
void GScr_MySQL_EscapeString();

/// <summary>
/// Return a hex representation of the string.
/// </summary>
void GScr_MySQL_HexString();

/// <summary>
/// Fetch row for queries.
/// </summary>
/// <param name="stringIndexed">Return as a string indexed array.</param>
/// <returns></returns>
qboolean Scr_MySQL_FetchQueryRow(qboolean stringIndexed);

/// <summary>
/// Fetch rows for queries.
/// </summary>
/// <param name="stringIndexed">Return as a string indexed array.</param>
/// <returns></returns>
void Scr_MySQL_FetchQueryRows(qboolean stringIndexed);

/// <summary>
/// Fetch row for statement.
/// </summary>
/// <param name="stringIndexed">Return as a string indexed array.</param>
/// <returns></returns>
qboolean Scr_MySQL_FetchStatementRow(qboolean stringIndexed);

/// <summary>
/// Fetch rows for statement.
/// </summary>
/// <param name="stringIndexed">Return as a string indexed array.</param>
/// <returns></returns>
void Scr_MySQL_FetchStatementRows(qboolean stringIndexed);
