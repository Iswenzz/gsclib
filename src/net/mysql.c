#include "mysql.h"
#include <mysql.h>

#define MYSQL_ERROR(x, msg) \
if (x == NULL) 				\
{							\
	Plugin_Scr_Error(msg);	\
	return;					\
}

#define MYSQL_CHECK_INSTANCE(x) MYSQL_ERROR(x, "MySQL connection not found.")
#define MYSQL_CHECK_STMT(x) MYSQL_ERROR(x, "MySQL statement not found.")

int mysql_library_init_code;
static MYSQL_INSTANCE instance;

void GScr_MySQL_Version()
{
    if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Version()");
		return;
	}
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), "SQL_Version(): MySQL Client: %s", mysql_get_client_info());
    Plugin_Scr_AddString(buffer);
}

void GScr_MySQL_Prepare()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_Prepare(<query>)");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);
	MySQL_Free_Statement();
	MySQL_Free_Result();
	
	const char *query = Plugin_Scr_GetString(0);

	instance.stmt = mysql_stmt_init(instance.mysql);
	if (mysql_stmt_prepare(instance.stmt, query, strlen(query)))
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Prepare(): Prepare statement failed: %s", mysql_stmt_error(instance.stmt));
		Plugin_Scr_Error(buffer);
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
	MYSQL_CHECK_INSTANCE(instance.mysql);
	MYSQL_CHECK_STMT(instance.stmt);

	const char *value = Plugin_Scr_GetString(0);
	enum_field_types type = (enum_field_types)Plugin_Scr_GetInt(1);

	if (!instance.binds)
		instance.binds = (MYSQL_BIND_BUFFER *)malloc(sizeof(MYSQL_BIND_BUFFER));
	else
		instance.binds = (MYSQL_BIND_BUFFER *)realloc(instance.binds, 
			sizeof(MYSQL_BIND_BUFFER) * (instance.bindsLength + 1));

	MySQL_PrepareBindBuffer(&instance.binds[instance.bindsLength], value, strlen(value), type);
	instance.bindsLength++;
}

void GScr_MySQL_BindResult()
{
	if (Plugin_Scr_GetNumParam() < 1)
	{
		Plugin_Scr_Error("Usage: SQL_BindResult(<type>, <?stringLength>)");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);
	MYSQL_CHECK_STMT(instance.stmt);

	enum_field_types type = (enum_field_types)Plugin_Scr_GetInt(0);

	if (!instance.bindsResult)
		instance.bindsResult = (MYSQL_BIND_BUFFER *)malloc(sizeof(MYSQL_BIND_BUFFER));
	else
		instance.bindsResult = (MYSQL_BIND_BUFFER *)realloc(instance.bindsResult, 
			sizeof(MYSQL_BIND_BUFFER) * (instance.bindsResultLength + 1));

	if (Plugin_Scr_GetNumParam() == 2) // Alloc a string buffer
		MySQL_PrepareBindBuffer(&instance.bindsResult[instance.bindsResultLength], NULL, Plugin_Scr_GetInt(1) + 1, type);
	else
		MySQL_PrepareBindBuffer(&instance.bindsResult[instance.bindsResultLength], NULL, 0, type);
	instance.bindsResultLength++;
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
				strcpy_s(str, valueLength + 1, value);

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
	MYSQL_CHECK_INSTANCE(instance.mysql);
	MYSQL_CHECK_STMT(instance.stmt);

	// Remap the binds
	MYSQL_BIND binds[instance.bindsLength];
	MYSQL_BIND bindsResult[instance.bindsResultLength];

	for (int i = 0; i < instance.bindsLength; i++)
		binds[i] = instance.binds[i].bind;
	for (int i = 0; i < instance.bindsResultLength; i++)
		bindsResult[i] = instance.bindsResult[i].bind;
	
	// Bind params
	if (instance.bindsLength && mysql_stmt_bind_param(instance.stmt, binds))
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Execute(): Bind statement failed: %s", mysql_stmt_error(instance.stmt));
		Plugin_Scr_Error(buffer);
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Bind results
	if (instance.bindsResultLength && mysql_stmt_bind_result(instance.stmt, bindsResult))
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Execute(): Bind statement failed: %s", mysql_stmt_error(instance.stmt));
		Plugin_Scr_Error(buffer);
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Execute statement
	if (mysql_stmt_execute(instance.stmt))
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Execute(): Execute statement failed: %s", mysql_stmt_error(instance.stmt));
		Plugin_Scr_Error(buffer);
		Plugin_Scr_AddBool(qfalse);
		MySQL_Free_Statement();
	}
	else
	{
		mysql_stmt_store_result(instance.stmt);
		instance.resultStmt = mysql_stmt_result_metadata(instance.stmt);
		Plugin_Scr_AddBool(qtrue);
	}

	// Free binds
	if (instance.binds)
	{
		for (int i = 0; i < instance.bindsLength; i++)
			free(instance.binds[i].buffer);

		free(instance.binds);
		instance.binds = NULL;
		instance.bindsLength = 0;
	}
}

void GScr_MySQL_ListDB()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_ListDB()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	MYSQL_RES *result = mysql_list_dbs(instance.mysql, "%");
	if (!result)
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_ListDB(): Couldn't get db list: %s", mysql_error(instance.mysql));
		Plugin_Scr_Error(buffer);
	}
	else 
	{
		MYSQL_ROW row;
		Plugin_Scr_MakeArray();
		while ((row = mysql_fetch_row(result)))
		{
			Plugin_Scr_AddString(row[0]);
			Plugin_Scr_AddArray();
		}
		mysql_free_result(result);
	}
}

void GScr_MySQL_ListTables()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_ListTables()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	MYSQL_RES *result = mysql_list_tables(instance.mysql, "%");
	if (!result)
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_ListTables(): Couldn't get table list: %s", mysql_error(instance.mysql));
		Plugin_Scr_Error(buffer);
	}
	else 
	{
		MYSQL_ROW row;
		Plugin_Scr_MakeArray();
		while ((row = mysql_fetch_row(result)))
		{
			Plugin_Scr_AddString(row[0]);
			Plugin_Scr_AddArray();
		}
		mysql_free_result(result);
	}
}

void GScr_MySQL_EscapeString()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_EscapeString(<string>)");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	const char *from = Plugin_Scr_GetString(0);
    char to[strlen(from) + 1];
    unsigned long len = mysql_real_escape_string(instance.mysql, to, from, strlen(from));
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
    char to[strlen(from) + 1];
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
	MYSQL_CHECK_INSTANCE(instance.mysql);

	if (mysql_select_db(instance.mysql, Plugin_Scr_GetString(0))) 
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_SelectDB(): Changing DBs failed: '%s'", mysql_error(instance.mysql));
		Plugin_Scr_Error(buffer);
		Plugin_Scr_AddBool(qfalse);
    }
	else
		Plugin_Scr_AddBool(qtrue);
}

void GScr_MySQL_FetchFields()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchFields()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	MYSQL_RES *res = instance.result ? instance.result : instance.resultStmt;
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
	MySQL_FetchRowsInternal(qfalse, qfalse);
}

void GScr_MySQL_FetchRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRows()");
		return;
	}
	MySQL_FetchRowsInternal(qtrue, qfalse);
}

void GScr_MySQL_FetchRowDict()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRowDict()");
		return;
	}
	MySQL_FetchRowsInternal(qfalse, qtrue);
}

void GScr_MySQL_FetchRowsDict()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRowsDict()");
		return;
	}
	MySQL_FetchRowsInternal(qtrue, qtrue);
}

void MySQL_FetchRowsInternal(qboolean all, qboolean stringIndexed)
{
	MYSQL_CHECK_INSTANCE(instance.mysql);

	// Statement results
	if (instance.resultStmt)
	{
		if (all) 
		{
			Plugin_Scr_MakeArray();
			mysql_stmt_data_seek(instance.stmt, 0);
		}
		while (!mysql_stmt_fetch(instance.stmt))
		{
			mysql_field_seek(instance.resultStmt, 0);

			Plugin_Scr_MakeArray();
			for (int i = 0; i < instance.bindsResultLength; i++) 
			{
				// Get the field name
				MYSQL_FIELD *field = mysql_fetch_field(instance.resultStmt);
				if (!field)
				{
					Plugin_Scr_AddUndefined();
					Plugin_Scr_AddArray();
					Plugin_Scr_Error("SQL_FetchRowsDict(): Error while fetching fields.");
					return;
				}

				// Add the row value
				if (instance.bindsResult[i].bind.is_null_value)
					Plugin_Scr_AddUndefined();
				else
				{
					switch (MySQL_TypeToGSC(instance.bindsResult[i].bind.buffer_type))
					{
						case VAR_STRING:
							Plugin_Scr_AddString((const char *)instance.bindsResult[i].bind.buffer);
							break;
						case VAR_INTEGER:
							Plugin_Scr_AddInt(*(int *)instance.bindsResult[i].bind.buffer);
							break;
						case VAR_FLOAT:
							Plugin_Scr_AddFloat(*(float *)instance.bindsResult[i].bind.buffer);
							break;
					}
				}

				// Add the value to an array
				if (stringIndexed && Plugin_Sys_GetCommonVersion() >= 20.0f)
					Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
				else
					Plugin_Scr_AddArray();
			}
			if (!all)
				break;
			else
				Plugin_Scr_AddArray();
		}
	}
	else if (instance.result)
	{
		MYSQL_ROW row;
		unsigned int num_fields = mysql_num_fields(instance.result);

		if (all) 
		{
			Plugin_Scr_MakeArray();
			mysql_data_seek(instance.result, 0);
		}
		while ((row = mysql_fetch_row(instance.result)) != NULL)
		{
			Plugin_Scr_MakeArray();
			mysql_field_seek(instance.result, 0);

			for (int i = 0; i < num_fields; i++) 
			{
				// Get the field name
				MYSQL_FIELD *field = mysql_fetch_field(instance.result);
				if (!field)
				{
					Plugin_Scr_AddUndefined();
					Plugin_Scr_AddArray();
					Plugin_Scr_Error("SQL_FetchRowsDict(): Error while fetching fields.");
					return;
				}

				// Add the row value
				if (!row[i])
					Plugin_Scr_AddUndefined();
				else
					Plugin_Scr_AddString(row[i]);

				// Add the value to an array
				if (stringIndexed && Plugin_Sys_GetCommonVersion() >= 20.0f)
					Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
				else
					Plugin_Scr_AddArray();
			}
			if (!all)
				break;
			else
				Plugin_Scr_AddArray();
		}		
	}
}

void GScr_MySQL_NumRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumRows()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	if (instance.result)
		Plugin_Scr_AddInt(mysql_num_rows(instance.result));
	else if (instance.stmt)
		Plugin_Scr_AddInt(mysql_stmt_num_rows(instance.stmt));
}

void GScr_MySQL_NumFields()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumFields()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	if (instance.result)
		Plugin_Scr_AddInt(mysql_num_fields(instance.result));
	else if (instance.stmt)
		Plugin_Scr_AddInt(mysql_stmt_field_count(instance.stmt));
}

void GScr_MySQL_AffectedRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_AffectedRows()");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	if (instance.result)
		Plugin_Scr_AddInt(mysql_affected_rows(instance.mysql));
	else if (instance.stmt)
		Plugin_Scr_AddInt(mysql_stmt_affected_rows(instance.stmt));
}

void GScr_MySQL_Query()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_Query(<query string>)");
		return;
	}
	MYSQL_CHECK_INSTANCE(instance.mysql);

	MySQL_Free_Result();
	if (mysql_query(instance.mysql, Plugin_Scr_GetString(0))) 
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Query(): Query failed: %s\n", mysql_error(instance.mysql));
		Plugin_Scr_Error(buffer);
		Plugin_Scr_AddBool(qfalse);
	} 
	else 
	{
		instance.result = mysql_store_result(instance.mysql);
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
	if (instance.mysql)
	{
		mysql_close(instance.mysql);
		instance.mysql = NULL;
	}

	instance.mysql = mysql_init(instance.mysql);
	if (!instance.mysql)
	{
		Plugin_Scr_Error("SQL_Connect(): MySQL failed to initialize");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Auto reconnection
	qboolean reconnect = qtrue;
	mysql_options(instance.mysql, MYSQL_OPT_RECONNECT, &reconnect);

	if (!mysql_real_connect(instance.mysql, /* MYSQL structure to use */
		Plugin_Scr_GetString(0),  			/* server hostname or IP address */ 
		Plugin_Scr_GetString(2),  			/* mysql user */
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
		Plugin_Printf("SQL_Connect(): Connected MySQL Server: %s\n", mysql_get_server_info(instance.mysql));
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
	if (instance.stmt)
	{
		mysql_stmt_free_result(instance.stmt);
		mysql_stmt_close(instance.stmt);
		instance.stmt = NULL;
	}
}

void MySQL_Free_Result()
{
	if (instance.resultStmt)
	{
		mysql_free_result(instance.resultStmt);
		instance.resultStmt = NULL;

		// Free results binds
		if (instance.bindsResult)
		{
			for (int i = 0; i < instance.bindsResultLength; i++)
				free(instance.bindsResult[i].buffer);

			free(instance.bindsResult);
			instance.bindsResult = NULL;
			instance.bindsResultLength = 0;
		}
	}
	if (instance.result)
	{
		mysql_free_result(instance.result);
		instance.result = NULL;
	}
}

void MySQL_Free()
{
	MySQL_Free_Statement();
	MySQL_Free_Result();

	if (instance.mysql)
	{
		mysql_close(instance.mysql);
		instance.mysql = NULL;
	}
}
