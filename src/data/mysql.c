#include "mysql.h"
#include <cgsc.h>
#include <my_global.h>
#include <mysql.h>

static MYSQL *mysql = NULL;

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
	if (mysql == NULL)
	{
		Plugin_Scr_Error("No MySQL connection found.");
		return;
	}

	MYSQL_RES *result = mysql_list_dbs(mysql, "%");
	if (!result)
	{
		char buffer[1024];
		snprintf(buffer, sizeof(buffer), "SQL_ListDB(): Couldn't get db list: %s", mysql_error(mysql));
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

void GScr_MySQL_Connect()
{
	if (Plugin_Scr_GetNumParam() != 4)
	{
		Plugin_Scr_Error("Usage: SQL_Connect(<host>, <port>, <user>, <password>)");
		return;
	}

	// Close previous connection
	if (mysql != NULL)
	{
		mysql_close(mysql);
		mysql_library_end();
		mysql = NULL;
	}

	// Initialize mysql lib
	if (mysql_library_init(0, NULL, NULL)) 
	{
		Plugin_Scr_Error("SQL_Connect(): Could not initialize MySQL client library.");
		return;
	}

	mysql = mysql_init(mysql);
	if (!mysql)
	{
		Plugin_Scr_Error("SQL_Connect(): MySQL failed to initialize.");
		mysql_library_end();
		return;
	}

	if (!mysql_real_connect(mysql, 	/* MYSQL structure to use */
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
		if (mysql != NULL)
		{
			mysql_close(mysql);
			mysql_library_end();
			mysql = NULL;
		}
	}
	else
		Plugin_Printf("SQL_Connect(): Connected MySQL Server: %s\n", mysql_get_server_info(mysql));
}

void GScr_MySQL_Close()
{
	if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQL_Close()");
		return;
	}

	// Close previous connection
	if (mysql != NULL)
	{
		mysql_close(mysql);
		mysql_library_end();
		mysql = NULL;
	}
	Plugin_Printf("SQL_Close(): Successfully closed MySQL connection.\n");
}
