#include "mysql.h"
#include <cgsc.h>
#include <my_global.h>

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

void GScr_MySQL_ListDB()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_ListDB()");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}

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

void GScr_MySQL_SelectDB()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_SelectDB(<name>)");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}

	if (mysql_select_db(instance.mysql, Plugin_Scr_GetString(0))) 
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_SelectDB(): Changing DBs failed: '%s'", mysql_error(instance.mysql));
		Plugin_Scr_Error(buffer);
    } 
}

void GScr_MySQL_FetchRow()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_FetchRows()");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}
	if (instance.result == NULL)
	{
		Plugin_Scr_Error("MySQL Query is empty");
		return;
	}
	MYSQL_ROW row = mysql_fetch_row(instance.result);
	unsigned int num_fields = mysql_num_fields(instance.result);

	if (row != NULL)
	{
		Plugin_Scr_MakeArray();
		mysql_field_seek(instance.result, 0);
		for (int i = 0; i < num_fields; i++) 
		{
			MYSQL_FIELD *field = mysql_fetch_field(instance.result);
			if (field == NULL)
			{
				Plugin_Scr_AddUndefined();
				Plugin_Scr_AddArray();
				Plugin_Scr_Error("SQL_FetchRows(): Error while fetching fields.");
				return;
			}
			if (row[i] == NULL)
				Plugin_Scr_AddUndefined();
			else
				Plugin_Scr_AddString(row[i]);

			Plugin_Scr_AddArray();
			// Plugin_Scr_AddArrayKeys(Plugin_Scr_AllocString(field->name)); // Plugin_Scr_AddArrayKeys is broken in the latest cod4x version.
		}
		mysql_free_result(instance.result);
	}
	else
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_FetchRows(): Couldn't fetch row.");
		Plugin_Scr_Error(buffer);
	}
}

void GScr_MySQL_NumRows()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumRows()");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}
	if (instance.result == NULL)
	{
		Plugin_Scr_Error("MySQL Query is empty");
		return;
	}
	Plugin_Scr_AddInt(mysql_num_rows(instance.result));
}

void GScr_MySQL_NumFields()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_NumFields()");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}
	if (instance.result == NULL)
	{
		Plugin_Scr_Error("MySQL Query is empty");
		return;
	}
	Plugin_Scr_AddInt(mysql_num_fields(instance.result));
}

void GScr_MySQL_Query()
{
	if (Plugin_Scr_GetNumParam() != 1)
	{
		Plugin_Scr_Error("Usage: SQL_Query(<query string>)");
		return;
	}
	if (instance.mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found");
		return;
	}

	if (mysql_query(instance.mysql, Plugin_Scr_GetString(0))) 
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_Query(): Query failed: %s\n", mysql_error(instance.mysql));
		Plugin_PrintError(buffer);
	} 
	else 
	{
		instance.result = mysql_store_result(instance.mysql);
		if (!instance.result) 
		{
			char buffer[1024];
			snprintf(buffer, sizeof(buffer), "SQL_Query(): Couldn't get results set: %s\n", mysql_error(instance.mysql));
			Plugin_PrintError(buffer);
		}
	}
}

void GScr_MySQL_Connect()
{
	if (Plugin_Scr_GetNumParam() != 4)
	{
		Plugin_Scr_Error("Usage: SQL_Connect(<host>, <port>, <user>, <password>)");
		return;
	}

	// Close previous connection
	if (instance.mysql != NULL)
	{
		mysql_close(instance.mysql);
		mysql_library_end();
		instance.mysql = NULL;
	}

	// Initialize mysql lib
	if (mysql_library_init(0, NULL, NULL)) 
	{
		Plugin_Scr_Error("SQL_Connect(): Could not initialize MySQL client library");
		return;
	}

	instance.mysql = mysql_init(instance.mysql);
	if (!instance.mysql)
	{
		Plugin_Scr_Error("SQL_Connect(): MySQL failed to initialize");
		mysql_library_end();
		return;
	}

	if (!mysql_real_connect(instance.mysql, 	/* MYSQL structure to use */
		Plugin_Scr_GetString(0),  	/* server hostname or IP address */ 
		Plugin_Scr_GetString(2),  	/* mysql user */
		Plugin_Scr_GetString(3),  	/* password */
		NULL,  						/* default database to use, NULL for none */
		Plugin_Scr_GetInt(1),     	/* port number, 0 for default */
		NULL,  						/* socket file or named pipe name */
		0 							/* connection flags */ ))
	{
		// Close previous connection
		Plugin_Scr_Error("SQL_Connect(): Connection failed");
		if (instance.mysql != NULL)
		{
			mysql_close(instance.mysql);
			mysql_library_end();
			instance.mysql = NULL;
		}
	}
	else
		Plugin_Printf("SQL_Connect(): Connected MySQL Server: %s\n", mysql_get_server_info(instance.mysql));
}

void GScr_MySQL_Close()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Close()");
		return;
	}

	// Close previous connection
	if (instance.mysql != NULL)
	{
		mysql_close(instance.mysql);
		mysql_library_end();
		instance.mysql = NULL;
	}
	Plugin_Printf("SQL_Close(): Successfully closed MySQL connection.\n");
}
