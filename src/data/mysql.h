#pragma once
#include <mysql.h>

typedef struct 
{
    MYSQL *mysql;
    MYSQL_RES *result;
} MYSQL_INSTANCE;

void GScr_MySQL_Version();
void GScr_MySQL_Connect();
void GScr_MySQL_Close();
void GScr_MySQL_SelectDB();
void GScr_MySQL_ListDB();
void GScr_MySQL_Query();
void GScr_MySQL_NumRows();
void GScr_MySQL_NumFields();
void GScr_MySQL_FetchRow();
void GScr_MySQL_FetchRows();