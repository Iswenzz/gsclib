#include "data/regex.h"
#include "data/zip.h"

#include "linq/delegates.h"
#include "linq/enumerables.h"
#include "linq/predicates.h"

#include "net/curl.h"
#include "net/ftp.h"
#include "net/http.h"
#include "net/mysql.h"

#include "sys/system.h"

#include "utils/convert.h"
#include "utils/math.h"
#include "utils/player.h"
#include "utils/stringutils.h"
#include "utils/utils.h"

#define FUNCTION(name, function) Plugin_ScrReplaceFunction(name, function)
#define METHOD(name, function) Plugin_ScrReplaceMethod(name, function)

/// <summary>
/// Init gsclib library.
/// </summary>
void GScr_GSCLIB_Init()
{
	Plugin_Printf("[GSCLIB] Initialize\n");

	AsyncHandlerRestart();
	ShutdownCriticalSections();

	MySQL_Working(qfalse);
	HTTP_Working(qfalse);
	FTP_Working(qfalse);
	CURL_Working(qfalse);
}

/// <summary>
/// Plugin initialization.
/// </summary>
/// <returns></returns>
PCL int OnInit()
{
	curl_handler.code = curl_global_init(CURL_GLOBAL_ALL);
	mysql_handler.code = mysql_library_init(0, NULL, NULL);

	// gsclib
	FUNCTION("gsclib_init", &GScr_GSCLIB_Init);

	// data/file
	FUNCTION("file_create", &GScr_FILE_Create);
	FUNCTION("file_open", &GScr_FILE_Open);
	FUNCTION("file_close", &GScr_FILE_Close);
	FUNCTION("file_exists", &GScr_FILE_Exists);
	FUNCTION("file_readline", &GScr_FILE_ReadLine);
	FUNCTION("file_writeline", &GScr_FILE_WriteLine);
	FUNCTION("file_readlines", &GScr_FILE_ReadLines);
	FUNCTION("file_writelines", &GScr_FILE_WriteLines);
	FUNCTION("file_read", &GScr_FILE_Read);
	FUNCTION("file_write", &GScr_FILE_Write);
	FUNCTION("file_seek", &GScr_FILE_Seek);
	FUNCTION("file_delete", &GScr_FILE_Delete);
	FUNCTION("file_mkdir", &GScr_FILE_MkDir);
	FUNCTION("file_rmdir", &GScr_FILE_RmDir);
	FUNCTION("file_readdir", &GScr_FILE_ReadDir);

	// data/regex
	FUNCTION("regexmatch", &GScr_RegexMatch);
	FUNCTION("regexsplit", &GScr_RegexSplit);
	FUNCTION("regexreplace", &GScr_RegexReplace);

	// data/zip
	FUNCTION("zip_add", &GScr_ZIP_Add);
	FUNCTION("zip_rename", &GScr_ZIP_Rename);
	FUNCTION("zip_delete", &GScr_ZIP_Delete);
	FUNCTION("zip_open", &GScr_ZIP_Open);
	FUNCTION("zip_close", &GScr_ZIP_Close);

	// linq/delegates
	FUNCTION("select", &GScr_LINQ_Select);
	FUNCTION("foreach", &GScr_LINQ_Foreach);
	FUNCTION("aggregate", &GScr_LINQ_Aggregate);

	// linq/predicates
	FUNCTION("all", &GScr_LINQ_All);
	FUNCTION("where", &GScr_LINQ_Where);
	FUNCTION("any", &GScr_LINQ_Any);
	FUNCTION("last", &GScr_LINQ_Last);
	FUNCTION("first", &GScr_LINQ_First);
	FUNCTION("count", &GScr_LINQ_Count);

	// linq/enumerables
	FUNCTION("getmin", &GScr_LINQ_Min);
	FUNCTION("getmax", &GScr_LINQ_Max);
	FUNCTION("cast", &GScr_LINQ_Cast);
	FUNCTION("oftype", &GScr_LINQ_OfType);
	FUNCTION("sort", &GScr_LINQ_Sort);
	FUNCTION("average", &GScr_LINQ_Average);
	FUNCTION("sum", &GScr_LINQ_Sum);
	FUNCTION("range", &GScr_LINQ_Range);
	FUNCTION("repeat", &GScr_LINQ_Repeat);
	FUNCTION("reverse", &GScr_LINQ_Reverse);
	FUNCTION("concat", &GScr_LINQ_Concat);
	FUNCTION("chunk", &GScr_LINQ_Chunk);
	FUNCTION("contains", &GScr_LINQ_Contains);
	FUNCTION("indexof", &GScr_LINQ_IndexOf);
	FUNCTION("remove", &GScr_LINQ_Remove);
	FUNCTION("removeat", &GScr_LINQ_RemoveAt);

	// net/curl
	FUNCTION("curl_version", &GScr_CURL_Version);
	FUNCTION("curl_init", &GScr_CURL_Init);
	FUNCTION("curl_addheader", &GScr_CURL_AddHeader);
	FUNCTION("curl_headercleanup", &GScr_CURL_HeaderCleanup);
	FUNCTION("curl_optcleanup", &GScr_CURL_OptCleanup);
	FUNCTION("curl_addopt", &GScr_CURL_AddOpt);
	FUNCTION("curl_free", &GScr_CURL_Free);

	// net/http
	FUNCTION("http_init", &GScr_HTTP_Init);
	FUNCTION("http_post", &GScr_HTTP_Post);
	FUNCTION("http_postfile", &GScr_HTTP_PostFile);
	FUNCTION("http_get", &GScr_HTTP_Get);
	FUNCTION("http_getfile", &GScr_HTTP_GetFile);
	FUNCTION("http_response", &GScr_HTTP_Response);
	FUNCTION("http_free", &GScr_HTTP_Free);

	// net/ftp
	FUNCTION("sftp_connect", &GScr_SFTP_Connect);
	FUNCTION("ftp_connect", &GScr_FTP_Connect);
	FUNCTION("ftp_init", &GScr_FTP_Init);
	FUNCTION("ftp_close", &GScr_FTP_Close);
	FUNCTION("ftp_shell", &GScr_FTP_Shell);
	FUNCTION("ftp_postfile", &GScr_FTP_PostFile);
	FUNCTION("ftp_getfile", &GScr_FTP_GetFile);
	FUNCTION("ftp_free", &GScr_FTP_Free);

	// net/mysql
	FUNCTION("sql_prepare", &GScr_MySQL_Prepare);
	FUNCTION("sql_bindparam", &GScr_MySQL_BindParam);
	FUNCTION("sql_bindresult", &GScr_MySQL_BindResult);
	FUNCTION("sql_execute", &GScr_MySQL_Execute);
	FUNCTION("sql_escapestring", &GScr_MySQL_EscapeString);
	FUNCTION("sql_hexstring", &GScr_MySQL_HexString);
	FUNCTION("sql_selectdb", &GScr_MySQL_SelectDB);
	FUNCTION("sql_query", &GScr_MySQL_Query);
	FUNCTION("sql_numrows", &GScr_MySQL_NumRows);
	FUNCTION("sql_numfields", &GScr_MySQL_NumFields);
	FUNCTION("sql_affectedrows", &GScr_MySQL_AffectedRows);
	FUNCTION("sql_fetchrowsdict", &GScr_MySQL_FetchRowsDict);
	FUNCTION("sql_fetchrows", &GScr_MySQL_FetchRows);
	FUNCTION("sql_fetchrowdict", &GScr_MySQL_FetchRowDict);
	FUNCTION("sql_fetchrow", &GScr_MySQL_FetchRow);
	FUNCTION("sql_fetchfields", &GScr_MySQL_FetchFields);
	FUNCTION("sql_listdb", &GScr_MySQL_ListDB);
	FUNCTION("sql_listtables", &GScr_MySQL_ListTables);
	FUNCTION("sql_version", &GScr_MySQL_Version);
	FUNCTION("sql_connect", &GScr_MySQL_Connect);
	FUNCTION("sql_close", &GScr_MySQL_Close);
	FUNCTION("sql_free", &GScr_MySQL_Free);

	// sys/system
	FUNCTION("system", &GScr_System);
	FUNCTION("sysprint", &GScr_SysPrint);
	FUNCTION("sysprintln", &GScr_SysPrintLn);
	FUNCTION("comprint", &GScr_ComPrint);
	FUNCTION("comprintln", &GScr_ComPrintLn);
	FUNCTION("getsystime", &GScr_GetSysTime);
	FUNCTION("criticalsection", &GScr_CriticalSection);
	FUNCTION("criticalsections", &GScr_CriticalSections);
	FUNCTION("entercriticalsection", &GScr_EnterCriticalSection);
	FUNCTION("leavecriticalsection", &GScr_LeaveCriticalSection);
	FUNCTION("asyncstatus", &GScr_AsyncStatus);
	FUNCTION("iswindows", &GScr_IsWindows);
	FUNCTION("islinux", &GScr_IsLinux);
	FUNCTION("cod4x_version", &GScr_CoD4X_Version);
	FUNCTION("cgsc_version", &GScr_CGSC_Version);
	FUNCTION("gsclib_version", &GScr_GSCLIB_Version);
	FUNCTION("exit", &GScr_Exit);

	// utils/utils
	FUNCTION("gettype", &GScr_GetType);
	FUNCTION("ternary", &GScr_Ternary);
	FUNCTION("ifundef", &GScr_IfUndef);

	// utils/convert
	FUNCTION("tostring", &GScr_ToString);
	FUNCTION("toint", &GScr_ToInt);
	FUNCTION("tofloat", &GScr_ToFloat);

	// utils/stringutils
	FUNCTION("isnullorempty", &GScr_IsNullOrEmpty);
	FUNCTION("isstringalpha", &GScr_IsStringAlpha);
	FUNCTION("isstringfloat", &GScr_IsStringFloat);
	FUNCTION("isstringint", &GScr_IsStringInt);
	FUNCTION("torgb", &GScr_ToRGB);
	FUNCTION("hextorgb", &GScr_HexToRGB);
	FUNCTION("fmt", &GScr_Fmt);
	FUNCTION("trim", &GScr_Trim);
	FUNCTION("startswith", &GScr_StartsWith);
	FUNCTION("endswith", &GScr_EndsWith);
	FUNCTION("strjoin", &GScr_StrJoin);
	FUNCTION("replace", &GScr_Replace);
	FUNCTION("pathjoin", &GScr_PathJoin);

	// utils/math
	FUNCTION("fmod", &GScr_fmod);
	FUNCTION("tan1", &GScr_tan1);
	FUNCTION("atan1", &GScr_atan1);
	FUNCTION("atan2", &GScr_atan2);
	FUNCTION("cos1", &GScr_cos1);
	FUNCTION("acos1", &GScr_acos1);
	FUNCTION("sin1", &GScr_sin1);
	FUNCTION("asin1", &GScr_asin1);

	// utils/player
	METHOD("getip", &GScr_GetIP);
	METHOD("getforwardmove", &GScr_GetForwardMove);
	METHOD("getrightmove", &GScr_GetRightMove);
	METHOD("getjumporigin", &GScr_GetJumpOrigin);
	METHOD("pmflags", &GScr_PmFlags);
	METHOD("setpmflags", &GScr_SetPmFlags);
	METHOD("pmtime", &GScr_PmTime);
	METHOD("setpmtime", &GScr_SetPmTime);
	METHOD("pmtype", &GScr_PmType);
	METHOD("weaponflags", &GScr_WeaponFlags);

	return 0;
}

/// <summary>
/// Plugin shutdown.
/// </summary>
/// <returns></returns>
PCL void OnTerminate()
{
	AsyncHandlerShutdown();
	ShutdownCriticalSections();

	curl_global_cleanup();
	mysql_library_end();
}

/// <summary>
/// Callback used to obtain information about the plugin.
/// </summary>
/// <param name="info">Memory pointed by info is allocated by the server binary.</param>
/// <returns></returns>
PCL void OnInfoRequest(pluginInfo_t *info)
{
	// ===== MANDATORY FIELDS =====
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

	// ===== OPTIONAL FIELDS =====
	info->pluginVersion.major = GSCLIB_VERSION_MAJOR;
	info->pluginVersion.minor = GSCLIB_VERSION_MINOR;
	strncpy(info->fullName, "gsclib", sizeof(info->fullName));
	strncpy(info->shortDescription,
		"gsclib acts as a standard library extension for the Call of Duty 4 scripting language.",
		sizeof(info->shortDescription));
	strncpy(info->longDescription,
		"gsclib acts as a standard library extension for the Call of Duty 4 scripting language. The features this "
		"library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expresison (RegEx) "
		"support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion "
		"and other type utilities, and much more. More detailed information on each feature can be found in the "
		"documentation section.",
		sizeof(info->longDescription));
}
