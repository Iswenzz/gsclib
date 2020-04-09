#include "mysql.h"
#include <cgsc.h>
#include <my_global.h>
#include <mysql.h>

void GScr_MySQL_Version()
{
    if (Plugin_Scr_GetNumParam() != 0)
	{
		Plugin_Scr_Error("Usage: SQLVersion()");
		return;
	}
    Plugin_Scr_AddString(mysql_get_client_info());
}
