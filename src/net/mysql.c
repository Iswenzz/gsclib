#include "mysql.h"
#include <mysql.h>

int MySQLcode;
static MYSQL_INSTANCE mysql;

void GScr_MySQL_Version()
{
    if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Version()");
		return;
	}
    Plugin_Scr_AddString(mysql_get_client_info());
}

void GScr_MySQL_Prepare()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_Prepare(<query>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();
	MySQL_Free_Statement();
	MySQL_Free_Result();
	
	const char *query = Plugin_Scr_GetString(0);

	mysql.stmt = mysql_stmt_init(mysql.handle);
	if (mysql_stmt_prepare(mysql.stmt, query, strlen(query)))
	{
		Plugin_Scr_Error(fmt("SQL_Prepare(): Prepare statement failed: %s", mysql_stmt_error(mysql.stmt)));
		Plugin_Scr_AddBool(qfalse);
	}
	else
		Plugin_Scr_AddBool(qtrue);
}

void GScr_MySQL_BindParam()
{
	if (Plugin_Scr_GetNumParam() != 2)
	{
		Plugin_Scr_Error("Usage: SQL_BindParam(<value>, <type>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();
	CHECK_MYSQL_STMT();

	const char *value = Plugin_Scr_GetString(0);
	enum_field_types type = (enum_field_types)Plugin_Scr_GetInt(1);

	if (!mysql.binds)
		mysql.binds = (MYSQL_BIND_BUFFER *)malloc(sizeof(MYSQL_BIND_BUFFER));
	else
		mysql.binds = (MYSQL_BIND_BUFFER *)realloc(mysql.binds, 
			sizeof(MYSQL_BIND_BUFFER) * (mysql.bindsLength + 1));

	MySQL_PrepareBindBuffer(&mysql.binds[mysql.bindsLength], value, strlen(value), type);
	mysql.bindsLength++;
}

void GScr_MySQL_BindResult()
{
	if (Plugin_Scr_GetNumParam() < 1)
	{
		Plugin_Scr_Error("Usage: SQL_BindResult(<type>, <?valueLength>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();
	CHECK_MYSQL_STMT();

	enum_field_types type = Plugin_Scr_GetInt(0);

	if (!mysql.bindsResult)
		mysql.bindsResult = (MYSQL_BIND_BUFFER *)malloc(sizeof(MYSQL_BIND_BUFFER));
	else
		mysql.bindsResult = (MYSQL_BIND_BUFFER *)realloc(mysql.bindsResult, 
			sizeof(MYSQL_BIND_BUFFER) * (mysql.bindsResultLength + 1));

	if (Plugin_Scr_GetNumParam() == 2) // Alloc a string buffer
		MySQL_PrepareBindBuffer(&mysql.bindsResult[mysql.bindsResultLength], NULL, Plugin_Scr_GetInt(1) + 1, type);
	else
		MySQL_PrepareBindBuffer(&mysql.bindsResult[mysql.bindsResultLength], NULL, 0, type);
	mysql.bindsResultLength++;
}

void MySQL_PrepareBindBuffer(MYSQL_BIND_BUFFER *b, const char *value, int valueLength, enum_field_types type)
{
	memset(&b->bind, 0, sizeof(b->bind));
	b->bind.buffer_type = type;
	
	switch (MySQL_TypeToGSC(b->bind.buffer_type))
	{
		case VAR_STRING:
		{
			char *str = (char *)malloc(sizeof(char) * valueLength + 1);
			*str = '\0';

			if (value)
				strcpy(str, value);
			b->buffer = str;
			b->bind.buffer_length = valueLength;
		}
		break;
		case VAR_INTEGER:
		{
			long long *number = (long long *)malloc(sizeof(long long));
			*number = 0;

			if (value)
				*number = strtoll(value, NULL, 10);
			b->buffer = number;
		}
		break;
		case VAR_FLOAT:
		{
			float *number = (float *)malloc(sizeof(float));
			*number = 0;

			if (value)
				*number = strtof(value, NULL);
			b->buffer = number;
		}
		break;
	}
	b->bind.buffer = (char *)b->buffer;
}

int MySQL_TypeToGSC(enum_field_types type)
{
	switch (type)
	{
		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_VAR_STRING:
		case MYSQL_TYPE_VARCHAR:
		case MYSQL_TYPE_JSON:
		case MYSQL_TYPE_GEOMETRY:
		case MYSQL_TYPE_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_SET:
		case MYSQL_TYPE_TIME2:
		case MYSQL_TYPE_DATETIME2:
		case MYSQL_TYPE_TIMESTAMP2:
		case MYSQL_TYPE_NEWDATE:
		case MYSQL_TYPE_YEAR:
		case MYSQL_TYPE_DATETIME:
		case MYSQL_TYPE_TIME:
		case MYSQL_TYPE_DATE:
		case MYSQL_TYPE_TIMESTAMP:
			return VAR_STRING;

		case MYSQL_TYPE_ENUM:
		case MYSQL_TYPE_BIT:
		case MYSQL_TYPE_INT24:
		case MYSQL_TYPE_LONGLONG:
		case MYSQL_TYPE_LONG:
		case MYSQL_TYPE_NULL:
		case MYSQL_TYPE_SHORT:
		case MYSQL_TYPE_TINY:
			return VAR_INTEGER;

		case MYSQL_TYPE_NEWDECIMAL:
		case MYSQL_TYPE_DECIMAL:
		case MYSQL_TYPE_DOUBLE:
		case MYSQL_TYPE_FLOAT:
			return VAR_FLOAT;

		default:
			return VAR_UNDEFINED;
	}
}

void GScr_MySQL_Execute()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Execute()");
		return;
	}
	CHECK_MYSQL_INSTANCE();
	CHECK_MYSQL_STMT();

	// Remap the binds
	MYSQL_BIND binds[mysql.bindsLength];
	MYSQL_BIND bindsResult[mysql.bindsResultLength];

	for (int i = 0; i < mysql.bindsLength; i++)
		binds[i] = mysql.binds[i].bind;
	for (int i = 0; i < mysql.bindsResultLength; i++)
		bindsResult[i] = mysql.bindsResult[i].bind;
	
	// Bind params
	if (mysql.bindsLength && mysql_stmt_bind_param(mysql.stmt, binds))
	{
		Plugin_Scr_Error(fmt("SQL_Execute(): Bind statement failed: %s", mysql_stmt_error(mysql.stmt)));
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Bind results
	if (mysql.bindsResultLength && mysql_stmt_bind_result(mysql.stmt, bindsResult))
	{
		Plugin_Scr_Error(fmt("SQL_Execute(): Bind statement failed: %s", mysql_stmt_error(mysql.stmt)));
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Execute statement
	if (mysql_stmt_execute(mysql.stmt))
	{
		Plugin_Scr_Error(fmt("SQL_Execute(): Execute statement failed: %s", mysql_stmt_error(mysql.stmt)));
		Plugin_Scr_AddBool(qfalse);
		MySQL_Free_Statement();
	}
	else
	{
		mysql_stmt_store_result(mysql.stmt);
		mysql.resultStmt = mysql_stmt_result_metadata(mysql.stmt);
		Plugin_Scr_AddBool(qtrue);
	}

	// Free binds
	if (mysql.binds)
	{
		for (int i = 0; i < mysql.bindsLength; i++)
			free(mysql.binds[i].buffer);

		free(mysql.binds);
		mysql.binds = NULL;
		mysql.bindsLength = 0;
	}
}

void GScr_MySQL_ListDB()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_ListDB()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	MYSQL_RES *result = mysql_list_dbs(mysql.handle, "%");
	MYSQL_ROW row;

	if (!result)
	{
		Plugin_Scr_Error(fmt("SQL_ListDB(): Couldn't get db list: %s", mysql_error(mysql.handle)));
		return;
	}
	
	Plugin_Scr_MakeArray();
	while ((row = mysql_fetch_row(result)))
	{
		Plugin_Scr_AddString(row[0]);
		Plugin_Scr_AddArray();
	}
	mysql_free_result(result);
}

void GScr_MySQL_ListTables()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_ListTables()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	MYSQL_RES *result = mysql_list_tables(mysql.handle, "%");
	MYSQL_ROW row;

	if (!result)
	{
		Plugin_Scr_Error(fmt("SQL_ListTables(): Couldn't get table list: %s", mysql_error(mysql.handle)));
		return;
	}

	Plugin_Scr_MakeArray();
	while ((row = mysql_fetch_row(result)))
	{
		Plugin_Scr_AddString(row[0]);
		Plugin_Scr_AddArray();
	}
	mysql_free_result(result);
}

void GScr_MySQL_EscapeString()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_EscapeString(<string>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	const char *from = Plugin_Scr_GetString(0);
    char to[strlen(from) + 1];
    unsigned long len = mysql_real_escape_string(mysql.handle, to, from, strlen(from));
    to[len] = '\0';

	Plugin_Scr_AddString(to);
}

void GScr_MySQL_HexString()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_HexString(<string>)");
		return;
	}
	const char *from = Plugin_Scr_GetString(0);
    char to[(strlen(from) * 2) + 1];
    unsigned long len = mysql_hex_string(to, from, strlen(from));
    to[len] = '\0';

    Plugin_Scr_AddString(to);
}

void GScr_MySQL_SelectDB()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_SelectDB(<name>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql_select_db(mysql.handle, Plugin_Scr_GetString(0)) == 0) 
		Plugin_Scr_AddBool(qtrue);
	else
	{
		Plugin_Scr_Error(fmt("SQL_SelectDB(): Changing DBs failed: '%s'", mysql_error(mysql.handle)));
		Plugin_Scr_AddBool(qfalse);
	}
}

void GScr_MySQL_FetchFields()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchFields()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	MYSQL_RES *res = mysql.result ? mysql.result : mysql.resultStmt;
	if (!res)
	{
		Plugin_Scr_AddUndefined();
		Plugin_Scr_Error("SQL_FetchFields(): MySQL result not found.");
		return;
	}

	unsigned int num_fields = mysql_num_fields(res);
	Plugin_Scr_MakeArray();
	mysql_field_seek(res, 0);
	for (int i = 0; i < num_fields; i++) 
	{
		MYSQL_FIELD *field = mysql_fetch_field(res);
		if (!field)
		{
			Plugin_Scr_AddUndefined();
			Plugin_Scr_AddArray();
			Plugin_Scr_Error("SQL_FetchFields(): Error while fetching fields.");
			return;
		}
		else
			Plugin_Scr_AddString(field->name);

		Plugin_Scr_AddArray();
	}
}

void GScr_MySQL_FetchRow()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRow()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Scr_MySQL_FetchQueryRow(qfalse);
	else if (mysql.stmt)
		Scr_MySQL_FetchStatementRow(qfalse);
}

void GScr_MySQL_FetchRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRows()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Scr_MySQL_FetchQueryRows(qfalse);
	else if (mysql.stmt)
		Scr_MySQL_FetchStatementRows(qfalse);
}

void GScr_MySQL_FetchRowDict()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRowDict()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Scr_MySQL_FetchQueryRow(qtrue);
	else if (mysql.stmt)
		Scr_MySQL_FetchStatementRow(qtrue);
}

void GScr_MySQL_FetchRowsDict()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRowsDict()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Scr_MySQL_FetchQueryRows(qtrue);
	else if (mysql.stmt)
		Scr_MySQL_FetchStatementRows(qtrue);
}

void Scr_MySQL_FetchStatementRows(qboolean stringIndexed)
{
	CHECK_MYSQL_INSTANCE();
	CHECK_MYSQL_STMT();

	Plugin_Scr_MakeArray();
	mysql_stmt_data_seek(mysql.stmt, 0);

	while (!mysql_stmt_fetch(mysql.stmt))
	{
		Scr_MySQL_FetchStatementRow(stringIndexed);
		Plugin_Scr_AddArray();
	}
}

void Scr_MySQL_FetchStatementRow(qboolean stringIndexed)
{
	CHECK_MYSQL_INSTANCE();
	CHECK_MYSQL_STMT();

	mysql_field_seek(mysql.resultStmt, 0);
	Plugin_Scr_MakeArray();

	for (int i = 0; i < mysql.bindsResultLength; i++)
	{
		// Get the field name
		MYSQL_FIELD* field = mysql_fetch_field(mysql.resultStmt);
		if (!field)
		{
			Plugin_Scr_AddUndefined();
			Plugin_Scr_AddArray();
			Plugin_Scr_Error("SQL_FetchRowsDict(): Error while fetching fields.");
			return;
		}

		// Add the row value
		if (mysql.bindsResult[i].bind.is_null_value)
			Plugin_Scr_AddUndefined();
		else
		{
			switch (MySQL_TypeToGSC(mysql.bindsResult[i].bind.buffer_type))
			{
			case VAR_STRING:
				Plugin_Scr_AddString((const char*)mysql.bindsResult[i].bind.buffer);
				break;
			case VAR_INTEGER:
				Plugin_Scr_AddInt(*(int*)mysql.bindsResult[i].bind.buffer);
				break;
			case VAR_FLOAT:
				Plugin_Scr_AddFloat(*(float*)mysql.bindsResult[i].bind.buffer);
				break;
			}
		}

		// Add the value to an array
		if (CGSC_SupportIndexedString() && stringIndexed)
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
		else
			Plugin_Scr_AddArray();
	}
}

void Scr_MySQL_FetchQueryRows(qboolean stringIndexed)
{
	CHECK_MYSQL_INSTANCE();

	Plugin_Scr_MakeArray();
	mysql_data_seek(mysql.result, 0);

	while (Scr_MySQL_FetchQueryRow(stringIndexed))
		Plugin_Scr_AddArray();
}

qboolean Scr_MySQL_FetchQueryRow(qboolean stringIndexed)
{
	MYSQL_ROW row = mysql_fetch_row(mysql.result);
	unsigned int num_fields = mysql_num_fields(mysql.result);
	if (row == NULL) 
		return qfalse;

	Plugin_Scr_MakeArray();
	mysql_field_seek(mysql.result, 0);

	for (int i = 0; i < num_fields; i++)
	{
		// Get the field name
		MYSQL_FIELD* field = mysql_fetch_field(mysql.result);
		if (!field)
		{
			Plugin_Scr_AddUndefined();
			Plugin_Scr_AddArray();
			Plugin_Scr_Error("SQL_FetchRowsDict(): Error while fetching fields.");
			return qfalse;
		}

		// Add the row value
		if (!row[i])
			Plugin_Scr_AddUndefined();
		else
			Plugin_Scr_AddString(row[i]);

		// Add the value to an array
		if (CGSC_SupportIndexedString() && stringIndexed)
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
		else
			Plugin_Scr_AddArray();
	}
	return qtrue;
}

void GScr_MySQL_NumRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumRows()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Plugin_Scr_AddInt(mysql_num_rows(mysql.result));
	else if (mysql.stmt)
		Plugin_Scr_AddInt(mysql_stmt_num_rows(mysql.stmt));
}

void GScr_MySQL_NumFields()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumFields()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Plugin_Scr_AddInt(mysql_num_fields(mysql.result));
	else if (mysql.stmt)
		Plugin_Scr_AddInt(mysql_stmt_field_count(mysql.stmt));
}

void GScr_MySQL_AffectedRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_AffectedRows()");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	if (mysql.result)
		Plugin_Scr_AddInt(mysql_affected_rows(mysql.handle));
	else if (mysql.stmt)
		Plugin_Scr_AddInt(mysql_stmt_affected_rows(mysql.stmt));
}

void GScr_MySQL_Query()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_Query(<query string>)");
		return;
	}
	CHECK_MYSQL_INSTANCE();

	MySQL_Free_Result();
	if (mysql_query(mysql.handle, Plugin_Scr_GetString(0))) 
	{
		Plugin_Scr_Error(fmt("SQL_Query(): Query failed: %s\n", mysql_error(mysql.handle)));
		Plugin_Scr_AddBool(qfalse);
	} 
	else 
	{
		mysql.result = mysql_store_result(mysql.handle);
		Plugin_Scr_AddBool(qtrue);
	}
}

void GScr_MySQL_Connect()
{
	if (Plugin_Scr_GetNumParam() != 4)
	{
		Plugin_Scr_Error("Usage: SQL_Connect(<host>, <port>, <user>, <password>)");
		return;
	}
	if (mysql.handle)
	{
		mysql_close(mysql.handle);
		mysql.handle = NULL;
	}

	mysql.handle = mysql_init(mysql.handle);
	if (!mysql.handle)
	{
		Plugin_Scr_Error("SQL_Connect(): MySQL failed to initialize");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Auto reconnection
	qboolean reconnect = qtrue;
	mysql_options(mysql.handle, MYSQL_OPT_RECONNECT, &reconnect);

	if (!mysql_real_connect(mysql.handle, /* MYSQL structure to use */
		Plugin_Scr_GetString(0),  			/* server hostname or IP address */ 
		Plugin_Scr_GetString(2),  			/* handle user */
		Plugin_Scr_GetString(3),  			/* password */
		NULL,  								/* default database to use, NULL for none */
		Plugin_Scr_GetInt(1),     			/* port number, 0 for default */
		NULL,  								/* socket file or named pipe name */
		0 									/* connection flags */ 
	))
	{
		// Close previous connection
		Plugin_Scr_Error("SQL_Connect(): Connection failed");
		MySQL_Free();
		Plugin_Scr_AddBool(qfalse);
	}
	else
	{
		Plugin_Printf("SQL_Connect(): Connected MySQL Server: %s\n", mysql_get_server_info(mysql.handle));
		Plugin_Scr_AddBool(qtrue);
	}
}

void GScr_MySQL_Close()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Close()");
		return;
	}

	MySQL_Free();
	Plugin_Printf("SQL_Close(): Successfully closed MySQL connection.\n");
	Plugin_Scr_AddBool(qtrue);
}

void MySQL_Free_Statement()
{
	if (mysql.stmt)
	{
		mysql_stmt_free_result(mysql.stmt);
		mysql_stmt_close(mysql.stmt);
		mysql.stmt = NULL;
	}
}

void MySQL_Free_Result()
{
	if (mysql.resultStmt)
	{
		mysql_free_result(mysql.resultStmt);
		mysql.resultStmt = NULL;

		// Free results binds
		if (mysql.bindsResult)
		{
			for (int i = 0; i < mysql.bindsResultLength; i++)
				free(mysql.bindsResult[i].buffer);

			free(mysql.bindsResult);
			mysql.bindsResult = NULL;
			mysql.bindsResultLength = 0;
		}
	}
	else if (mysql.result)
	{
		mysql_free_result(mysql.result);
		mysql.result = NULL;
	}
}

void MySQL_Free()
{
	MySQL_Free_Statement();
	MySQL_Free_Result();

	if (mysql.handle)
	{
		mysql_close(mysql.handle);
		mysql.handle = NULL;
	}
}
