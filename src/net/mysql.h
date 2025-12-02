#pragma once
#include "sys/system.h"

#include <CGSC/cgsc.h>
#include <mysql.h>

#define MYSQL_CHECK_ERROR(x, msg) \
	if (x)                        \
	{                             \
		Plugin_Scr_Error(msg);    \
		return;                   \
	}

#define CHECK_MYSQL_REQUEST(mysql)                         \
	MYSQL_CHECK_ERROR(!mysql, "MySQL request not found."); \
	MYSQL_CHECK_ERROR(mysql->worker && mysql->worker->status == ASYNC_PENDING, "MySQL request is pending.");

#define CHECK_MYSQL_WORKING() MYSQL_CHECK_ERROR(mysql_handler.working, "MySQL is processing another request.");

#define CHECK_MYSQL_INSTANCE(handle) MYSQL_CHECK_ERROR(!handle, "MySQL connection not found.");

#define CHECK_MYSQL_STMT(stmt) MYSQL_CHECK_ERROR(!stmt, "MySQL statement not found.");

typedef struct
{
	int code;
	MYSQL* handle;
	qboolean working;
} MYSQL_HANDLER;

typedef struct
{
	async_worker* worker;
	MYSQL* handle;
	MYSQL_RES* result;
	MYSQL_RES* resultStmt;
	MYSQL_STMT* stmt;
	MYSQL_BIND* binds;
	MYSQL_BIND* bindsResult;
	char query[1024];
	int bindsLength;
	int bindsResultLength;
} MYSQL_REQUEST;

extern MYSQL_HANDLER mysql_handler;

void GScr_MySQL_Prepare();
void GScr_MySQL_BindParam();
void GScr_MySQL_BindResult();
void GScr_MySQL_Execute();
void GScr_MySQL_Version();
void GScr_MySQL_Connect();
void GScr_MySQL_AffectedRows();
void GScr_MySQL_Close();
void GScr_MySQL_SelectDB();
void GScr_MySQL_ListDB();
void GScr_MySQL_ListTables();
void GScr_MySQL_Query();
void GScr_MySQL_NumRows();
void GScr_MySQL_NumFields();
void GScr_MySQL_FetchRow();
void GScr_MySQL_FetchRows();
void GScr_MySQL_FetchRowDict();
void GScr_MySQL_FetchRowsDict();
void GScr_MySQL_FetchFields();
void GScr_MySQL_EscapeString();
void GScr_MySQL_HexString();
void GScr_MySQL_Free();

qboolean Scr_MySQL_FetchQueryRow(MYSQL_REQUEST* mysql, qboolean stringIndexed);
void Scr_MySQL_FetchQueryRows(MYSQL_REQUEST* mysql, qboolean stringIndexed);
qboolean Scr_MySQL_FetchStatementRow(MYSQL_REQUEST* mysql, qboolean stringIndexed);
void Scr_MySQL_FetchStatementRows(MYSQL_REQUEST* mysql, qboolean stringIndexed);

void MySQL_Free();
void MySQL_Free_Result(MYSQL_REQUEST* mysql);
void MySQL_Free_Statement(MYSQL_REQUEST* mysql);
int MySQL_TypeToGSC(enum enum_field_types type);
void MySQL_PrepareBindBuffer(MYSQL_BIND* b, void* value, int valueLength, enum enum_field_types type);
void MySQL_Working(qboolean state);
void MySQL_Query(uv_work_t* req);
void MySQL_Execute(uv_work_t* req);
