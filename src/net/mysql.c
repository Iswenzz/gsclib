#include "mysql.h"
#include "sys/system.h"

MYSQL_HANDLER mysql_handler = { 0 };

void GScr_MySQL_Version()
{
	CHECK_PARAMS(0, "Usage: SQL_Version()");
    Plugin_Scr_AddString(mysql_get_client_info());
}

void GScr_MySQL_Prepare()
{
	CHECK_PARAMS(1, "Usage: SQL_Prepare(<query>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)calloc(1, sizeof(MYSQL_REQUEST));
	mysql->handle = mysql_handler.handle;

	CHECK_MYSQL_WORKING();
	CHECK_MYSQL_INSTANCE(mysql->handle);

	MySQL_Working(qtrue);
	MySQL_Free_Result(mysql);
	MySQL_Free_Statement(mysql);

	const char *query = Plugin_Scr_GetString(0);
	mysql->stmt = mysql_stmt_init(mysql->handle);

	if (mysql_stmt_prepare(mysql->stmt, query, strlen(query)))
	{
		Plugin_Scr_Error(fmt("SQL_Prepare(): Prepare statement failed: %s", mysql_stmt_error(mysql->stmt)));
		Plugin_Scr_AddBool(qfalse);
	}
	else
		Plugin_Scr_AddInt((int)mysql);
}

void GScr_MySQL_BindParam()
{
	CHECK_PARAMS(3, "Usage: SQL_BindParam(<request>, <value>, <type>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);
	CHECK_MYSQL_STMT(mysql->stmt);

	VariableValue *variable = Plugin_Scr_SelectParam(1);
	enum_field_types type = (enum_field_types)Plugin_Scr_GetInt(2);

	mysql->binds = !mysql->binds
		? (MYSQL_BIND*)malloc(sizeof(MYSQL_BIND))
		: (MYSQL_BIND*)realloc(mysql->binds, sizeof(MYSQL_BIND) * (mysql->bindsLength + 1));

	void* value = NULL;
	int valueSize = 0;

	switch (variable->type)
	{
	case VAR_STRING:
		value = (void *)Plugin_SL_ConvertToString(variable->u.stringValue);
		valueSize = strlen((const char *)value);
		break;
	case VAR_INTEGER:
		value = (void *)&variable->u.intValue;
		break;
	case VAR_FLOAT:
		value = (void *)&variable->u.floatValue;
		break;
	}
	MySQL_PrepareBindBuffer(&mysql->binds[mysql->bindsLength], value, valueSize, type);
	mysql->bindsLength++;
}

void GScr_MySQL_BindResult()
{
	if (Plugin_Scr_GetNumParam() < 2)
	{
		Plugin_Scr_Error("Usage: SQL_BindResult(<request>, <type>, <?valueLength>)");
		return;
	}

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);
	CHECK_MYSQL_STMT(mysql->stmt);

	enum_field_types type = Plugin_Scr_GetInt(1);
	int stringLength = Plugin_Scr_GetNumParam() == 3 ? Plugin_Scr_GetInt(2) + 1 : 0;

	mysql->bindsResult = !mysql->bindsResult
		? (MYSQL_BIND*)malloc(sizeof(MYSQL_BIND))
		: (MYSQL_BIND*)realloc(mysql->bindsResult, sizeof(MYSQL_BIND) * (mysql->bindsResultLength + 1));

	MySQL_PrepareBindBuffer(&mysql->bindsResult[mysql->bindsResultLength], NULL, stringLength, type);
	mysql->bindsResultLength++;
}

void GScr_MySQL_Execute()
{
	CHECK_PARAMS(1, "Usage: SQL_Execute(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);
	CHECK_MYSQL_STMT(mysql->stmt);

	mysql->worker = Plugin_AsyncWorker(asyncHandler, mysql, &MySQL_Execute, NULL);

	Plugin_Scr_AddBool(qtrue);
}

void GScr_MySQL_ListDB()
{
	CHECK_PARAMS(0, "Usage: SQL_ListDB()");
	CHECK_MYSQL_INSTANCE(mysql_handler.handle);

	MYSQL_RES *result = mysql_list_dbs(mysql_handler.handle, "%");
	MYSQL_ROW row;

	if (!result)
	{
		Plugin_Scr_Error(fmt("SQL_ListDB(): Couldn't get db list: %s", mysql_error(mysql_handler.handle)));
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
	CHECK_PARAMS(0, "Usage: SQL_ListTables()");
	CHECK_MYSQL_INSTANCE(mysql_handler.handle);

	MYSQL_RES *result = mysql_list_tables(mysql_handler.handle, "%");
	MYSQL_ROW row;

	if (!result)
	{
		Plugin_Scr_Error(fmt("SQL_ListTables(): Couldn't get table list: %s", mysql_error(mysql_handler.handle)));
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
	CHECK_PARAMS(1, "Usage: SQL_EscapeString(<string>)");
	CHECK_MYSQL_INSTANCE(mysql_handler.handle);

	const char *from = Plugin_Scr_GetString(0);
    char to[strlen(from) + 1];
    unsigned long len = mysql_real_escape_string(mysql_handler.handle, to, from, strlen(from));
    to[len] = '\0';

	Plugin_Scr_AddString(to);
}

void GScr_MySQL_HexString()
{
	CHECK_PARAMS(1, "Usage: SQL_HexString(<string>)");

	const char *from = Plugin_Scr_GetString(0);
    char to[(strlen(from) * 2) + 1];
    unsigned long len = mysql_hex_string(to, from, strlen(from));
    to[len] = '\0';

    Plugin_Scr_AddString(to);
}

void GScr_MySQL_SelectDB()
{
	CHECK_PARAMS(1, "Usage: SQL_SelectDB(<name>)");
	CHECK_MYSQL_INSTANCE(mysql_handler.handle);

	if (mysql_select_db(mysql_handler.handle, Plugin_Scr_GetString(0)) == 0)
		Plugin_Scr_AddBool(qtrue);
	else
	{
		Plugin_Scr_Error(fmt("SQL_SelectDB(): Changing DBs failed: '%s'", mysql_error(mysql_handler.handle)));
		Plugin_Scr_AddBool(qfalse);
	}
}

void GScr_MySQL_FetchFields()
{
	CHECK_PARAMS(1, "Usage: SQL_FetchFields(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	MYSQL_RES *res = mysql->result ? mysql->result : mysql->resultStmt;
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
	CHECK_PARAMS(1, "Usage: SQL_FetchRow(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Scr_MySQL_FetchQueryRow(mysql, qfalse);
	else if (mysql->stmt)
		Scr_MySQL_FetchStatementRow(mysql, qfalse);
}

void GScr_MySQL_FetchRows()
{
	CHECK_PARAMS(1, "Usage: SQL_FetchRows(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Scr_MySQL_FetchQueryRows(mysql, qfalse);
	else if (mysql->stmt)
		Scr_MySQL_FetchStatementRows(mysql, qfalse);
}

void GScr_MySQL_FetchRowDict()
{
	CHECK_PARAMS(1, "Usage: SQL_FetchRowDict(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Scr_MySQL_FetchQueryRow(mysql, qtrue);
	else if (mysql->stmt)
		Scr_MySQL_FetchStatementRow(mysql, qtrue);
}

void GScr_MySQL_FetchRowsDict()
{
	CHECK_PARAMS(1, "Usage: SQL_FetchRowsDict(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Scr_MySQL_FetchQueryRows(mysql, qtrue);
	else if (mysql->stmt)
		Scr_MySQL_FetchStatementRows(mysql, qtrue);
}

void GScr_MySQL_NumRows()
{
	CHECK_PARAMS(1, "Usage: SQL_NumRows(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Plugin_Scr_AddInt(mysql_num_rows(mysql->result));
	else if (mysql->stmt)
		Plugin_Scr_AddInt(mysql_stmt_num_rows(mysql->stmt));
}

void GScr_MySQL_NumFields()
{
	CHECK_PARAMS(1, "Usage: SQL_NumFields(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->result)
		Plugin_Scr_AddInt(mysql_num_fields(mysql->result));
	else if (mysql->stmt)
		Plugin_Scr_AddInt(mysql_stmt_field_count(mysql->stmt));
}

void GScr_MySQL_AffectedRows()
{
	CHECK_PARAMS(1, "Usage: SQL_AffectedRows(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	if (mysql->stmt)
	{
		Plugin_Scr_AddInt(mysql_stmt_affected_rows(mysql->stmt));
		return;
	}
	Plugin_Scr_AddInt(mysql_affected_rows(mysql->handle));
}

void GScr_MySQL_Query()
{
	CHECK_PARAMS(1, "Usage: SQL_Query(<query string>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)calloc(1, sizeof(MYSQL_REQUEST));
	mysql->handle = mysql_handler.handle;
	strcpy(mysql->query, Plugin_Scr_GetString(0));

	CHECK_MYSQL_WORKING();
	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	MySQL_Free_Result(mysql);

	mysql->worker = Plugin_AsyncWorker(asyncHandler, mysql, &MySQL_Query, NULL);

	MySQL_Working(qtrue);
	Plugin_Scr_AddInt((int)mysql);
}

void GScr_MySQL_Connect()
{
	CHECK_PARAMS(4, "Usage: SQL_Connect(<host>, <port>, <user>, <password>)");

	if (mysql_handler.handle)
	{
		mysql_close(mysql_handler.handle);
		mysql_handler.handle = NULL;
	}

	mysql_handler.handle = mysql_init(mysql_handler.handle);
	if (!mysql_handler.handle)
	{
		Plugin_Scr_Error("SQL_Connect(): MySQL failed to initialize");
		Plugin_Scr_AddBool(qfalse);
		return;
	}

	// Auto reconnection
	qboolean reconnect = qtrue;
	mysql_options(mysql_handler.handle, MYSQL_OPT_RECONNECT, &reconnect);

	if (!mysql_real_connect(mysql_handler.handle,	/* MYSQL structure to use */
		Plugin_Scr_GetString(0),  					/* server hostname or IP address */
		Plugin_Scr_GetString(2),  					/* handle user */
		Plugin_Scr_GetString(3),  					/* password */
		NULL,  										/* default database to use, NULL for none */
		Plugin_Scr_GetInt(1),     					/* port number, 0 for default */
		NULL,  										/* socket file or named pipe name */
		0 											/* connection flags */
	))
	{
		// Close previous connection
		Plugin_Scr_Error("SQL_Connect(): Connection failed");
		MySQL_Free();
		Plugin_Scr_AddBool(qfalse);
	}
	else
	{
		Plugin_Printf("SQL_Connect(): Connected MySQL Server: %s\n", mysql_get_server_info(mysql_handler.handle));
		Plugin_Scr_AddBool(qtrue);
	}
}

void GScr_MySQL_Close()
{
	CHECK_PARAMS(0, "Usage: SQL_Close()");

	MySQL_Free();
	Plugin_Scr_AddBool(qtrue);
}

void GScr_MySQL_Free()
{
	CHECK_PARAMS(1, "Usage: SQL_Free(<request>)");

	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)Plugin_Scr_GetInt(0);

	CHECK_MYSQL_REQUEST(mysql);

	free(mysql);

	MySQL_Working(qfalse);
	Plugin_Scr_AddBool(qtrue);
}

void Scr_MySQL_FetchStatementRows(MYSQL_REQUEST* mysql, qboolean stringIndexed)
{
	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);
	CHECK_MYSQL_STMT(mysql->stmt);

	Plugin_Scr_MakeArray();
	mysql_stmt_data_seek(mysql->stmt, 0);

	while (Scr_MySQL_FetchStatementRow(mysql, stringIndexed))
		Plugin_Scr_AddArray();
}

qboolean Scr_MySQL_FetchStatementRow(MYSQL_REQUEST* mysql, qboolean stringIndexed)
{
	if (mysql->stmt == NULL || mysql_stmt_fetch(mysql->stmt))
		return qfalse;

	mysql_field_seek(mysql->resultStmt, 0);
	Plugin_Scr_MakeArray();

	for (int i = 0; i < mysql->bindsResultLength; i++)
	{
		// Get the field name
		MYSQL_FIELD* field = mysql_fetch_field(mysql->resultStmt);
		if (!field)
		{
			Plugin_Scr_AddUndefined();
			Plugin_Scr_AddArray();
			Plugin_Scr_Error("SQL_FetchRowsDict(): Error while fetching fields.");
			return qfalse;
		}

		// Add the row value
		if (mysql->bindsResult[i].is_null_value)
			Plugin_Scr_AddUndefined();
		else
		{
			switch (MySQL_TypeToGSC(mysql->bindsResult[i].buffer_type))
			{
			case VAR_STRING:
				Plugin_Scr_AddString((const char*)mysql->bindsResult[i].buffer);
				break;
			case VAR_INTEGER:
				Plugin_Scr_AddInt(*(int*)mysql->bindsResult[i].buffer);
				break;
			case VAR_FLOAT:
				Plugin_Scr_AddFloat(*(float*)mysql->bindsResult[i].buffer);
				break;
			}
		}

		// Add the value to an array
		if (Plugin_CGSC_SupportIndexedString() && stringIndexed)
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
		else
			Plugin_Scr_AddArray();
	}
	return qtrue;
}

void Scr_MySQL_FetchQueryRows(MYSQL_REQUEST* mysql, qboolean stringIndexed)
{
	CHECK_MYSQL_REQUEST(mysql);
	CHECK_MYSQL_INSTANCE(mysql->handle);

	Plugin_Scr_MakeArray();
	mysql_data_seek(mysql->result, 0);

	while (Scr_MySQL_FetchQueryRow(mysql, stringIndexed))
		Plugin_Scr_AddArray();
}

qboolean Scr_MySQL_FetchQueryRow(MYSQL_REQUEST* mysql, qboolean stringIndexed)
{
	MYSQL_ROW row = mysql_fetch_row(mysql->result);
	unsigned int num_fields = mysql_num_fields(mysql->result);
	if (row == NULL)
		return qfalse;

	Plugin_Scr_MakeArray();
	mysql_field_seek(mysql->result, 0);

	for (int i = 0; i < num_fields; i++)
	{
		// Get the field name
		MYSQL_FIELD* field = mysql_fetch_field(mysql->result);
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
		if (Plugin_CGSC_SupportIndexedString() && stringIndexed)
			Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(field->name));
		else
			Plugin_Scr_AddArray();
	}
	return qtrue;
}

void MySQL_PrepareBindBuffer(MYSQL_BIND* b, void* value, int valueLength, enum_field_types type)
{
	memset(b, 0, sizeof(MYSQL_BIND));
	b->buffer_type = type;

	switch (MySQL_TypeToGSC(b->buffer_type))
	{
	case VAR_STRING:
	{
		char* str = (char*)malloc(sizeof(char) * valueLength + 1);
		*str = '\0';

		if (value)
			strcpy(str, value);
		b->buffer = str;
		b->buffer_length = valueLength;
	}
	break;
	case VAR_INTEGER:
	{
		int* number = (int*)malloc(sizeof(int));
		*number = 0;

		if (value)
			*number = *(int*)value;
		b->buffer = number;
	}
	break;
	case VAR_FLOAT:
	{
		float* number = (float*)malloc(sizeof(float));
		*number = 0;

		if (value)
			*number = *(float*)value;
		b->buffer = number;
	}
	break;
	}
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

void MySQL_Working(qboolean state)
{
	mysql_handler.working = state;
}

void MySQL_Query(uv_work_t* req)
{
	async_worker* worker = (async_worker*)req->data;
	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)worker->data;

	if (mysql_query(mysql->handle, mysql->query))
	{
		Sys_PrintF("SQL_Query(): Query failed\n");
		Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
		return;
	}

	mysql->result = mysql_store_result(mysql->handle);
	Plugin_AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
}

void MySQL_Execute(uv_work_t* req)
{
	async_worker* worker = (async_worker*)req->data;
	MYSQL_REQUEST* mysql = (MYSQL_REQUEST*)worker->data;

	// Bind params
	if (mysql->bindsLength && mysql_stmt_bind_param(mysql->stmt, mysql->binds))
	{
		Sys_PrintF("SQL_Execute(): Bind statement failed\n");
		Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
		return;
	}

	// Bind results
	if (mysql->bindsResultLength && mysql_stmt_bind_result(mysql->stmt, mysql->bindsResult))
	{
		Sys_PrintF("SQL_Execute(): Bind result statement failed\n");
		Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
		return;
	}

	// Execute statement
	if (mysql_stmt_execute(mysql->stmt))
	{
		Sys_PrintF("SQL_Execute(): Execute statement failed\n");
		Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
		return;
	}

	// Result
	if (mysql_stmt_store_result(mysql->stmt))
	{
		Sys_PrintF("SQL_Execute(): Store result failed\n");
		Plugin_AsyncWorkerDone(req, ASYNC_FAILURE);
		return;
	}
	mysql->resultStmt = mysql_stmt_result_metadata(mysql->stmt);
	Plugin_AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
}

void MySQL_Free_Statement(MYSQL_REQUEST *mysql)
{
	if (mysql->stmt)
	{
		mysql_stmt_free_result(mysql->stmt);
		mysql_stmt_close(mysql->stmt);
		mysql->stmt = NULL;
	}
}

void MySQL_Free_Result(MYSQL_REQUEST* mysql)
{
	if (mysql->resultStmt)
	{
		mysql_free_result(mysql->resultStmt);
		mysql->resultStmt = NULL;
	}
	if (mysql->result)
	{
		mysql_free_result(mysql->result);
		mysql->result = NULL;
	}
	if (mysql->binds)
	{
		for (int i = 0; i < mysql->bindsLength; i++)
			free(mysql->binds[i].buffer);

		free(mysql->binds);
		mysql->binds = NULL;
		mysql->bindsLength = 0;
	}
	if (mysql->bindsResult)
	{
		for (int i = 0; i < mysql->bindsResultLength; i++)
			free(mysql->bindsResult[i].buffer);

		free(mysql->bindsResult);
		mysql->bindsResult = NULL;
		mysql->bindsResultLength = 0;
	}
}

void MySQL_Free()
{
	if (mysql_handler.handle)
	{
		mysql_close(mysql_handler.handle);
		mysql_handler.handle = NULL;
	}
}
