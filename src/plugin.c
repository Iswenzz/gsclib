#include <curl/curl.h>

#include "linq/enumerable.h"
#include "linq/predicate.h"
#include "linq/delegate.h"

#include "data/mysql.h"
#include "data/regex.h"

#include "utility/util.h"
#include "utility/stringutil.h"
#include "utility/convert.h"

#include "net/curl.h"
#include "net/https.h"
#include "net/ftp.h"

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

PCL int OnInit()
{
	curl_library_init_code = curl_global_init(CURL_GLOBAL_ALL); 	// initialize curl library
	mysql_library_init_code = mysql_library_init(0, NULL, NULL); 	// initialize mysql library

	// net/curl.h
	Plugin_ScrAddFunction("curl_version", 		&GScr_CURL_Version);
	Plugin_ScrAddFunction("curl_setheader", 	&GScr_CURL_SetHeader);
	Plugin_ScrAddFunction("curl_headercleanup", &GScr_CURL_HeaderCleanup);
	Plugin_ScrAddFunction("curl_optcleanup", 	&GScr_CURL_OptCleanup);
	Plugin_ScrAddFunction("curl_addopt", 		&GScr_CURL_AddOpt);

	// net/https.h
	Plugin_ScrAddFunction("https_postfile", 	&GScr_HTTPS_PostFile);
	Plugin_ScrAddFunction("https_poststring", 	&GScr_HTTPS_PostString);
	Plugin_ScrAddFunction("https_getfile", 		&GScr_HTTPS_GetFile);
	Plugin_ScrAddFunction("https_getstring", 	&GScr_HTTPS_GetString);

	// net/ftp.h
	Plugin_ScrAddFunction("sftp_connect", 		&GScr_SFTP_Connect);
	Plugin_ScrAddFunction("ftp_connect", 		&GScr_FTP_Connect);
	Plugin_ScrAddFunction("ftp_close", 			&GScr_FTP_Close);
	Plugin_ScrAddFunction("ftp_shell", 			&GScr_FTP_Shell);
	Plugin_ScrAddFunction("ftp_postfile", 		&GScr_FTP_PostFile);
	Plugin_ScrAddFunction("ftp_getfile", 		&GScr_FTP_GetFile);

	// data/mysql.h
	Plugin_ScrAddFunction("sql_prepare", 		&GScr_MySQL_Prepare);
	Plugin_ScrAddFunction("sql_bindparam", 		&GScr_MySQL_BindParam);
	Plugin_ScrAddFunction("sql_bindresult", 	&GScr_MySQL_BindResult);
	Plugin_ScrAddFunction("sql_execute", 		&GScr_MySQL_Execute);

	Plugin_ScrAddFunction("sql_escapestring", 	&GScr_MySQL_EscapeString);
	Plugin_ScrAddFunction("sql_hexstring", 		&GScr_MySQL_HexString);
	Plugin_ScrAddFunction("sql_selectdb", 		&GScr_MySQL_SelectDB);
	Plugin_ScrAddFunction("sql_query", 			&GScr_MySQL_Query);
	Plugin_ScrAddFunction("sql_numrows", 		&GScr_MySQL_NumRows);
	Plugin_ScrAddFunction("sql_numfields", 		&GScr_MySQL_NumFields);
	Plugin_ScrAddFunction("sql_affectedrows",	&GScr_MySQL_AffectedRows);
	Plugin_ScrAddFunction("sql_fetchrowsdict", 	&GScr_MySQL_FetchRowsDict);
	Plugin_ScrAddFunction("sql_fetchrows", 		&GScr_MySQL_FetchRows);
	Plugin_ScrAddFunction("sql_fetchrowdict", 	&GScr_MySQL_FetchRowDict);
	Plugin_ScrAddFunction("sql_fetchrow", 		&GScr_MySQL_FetchRow);
	Plugin_ScrAddFunction("sql_fetchfields", 	&GScr_MySQL_FetchFields);
	Plugin_ScrAddFunction("sql_listdb", 		&GScr_MySQL_ListDB);
	Plugin_ScrAddFunction("sql_listtables", 	&GScr_MySQL_ListTables);
	Plugin_ScrAddFunction("sql_version", 		&GScr_MySQL_Version);
	Plugin_ScrAddFunction("sql_connect", 		&GScr_MySQL_Connect);
	Plugin_ScrAddFunction("sql_close", 			&GScr_MySQL_Close);

	// data/regex.h
	Plugin_ScrAddFunction("regexmatch", 		&GScr_RegexMatch);
	Plugin_ScrAddFunction("regexsplit", 		&GScr_RegexSplit);
	Plugin_ScrAddFunction("regexreplace", 		&GScr_RegexReplace);

	// utility/util.h
	Plugin_ScrAddFunction("comprintf", 			&GScr_ComPrintf);
	Plugin_ScrAddFunction("gettype", 			&GScr_GetType);
	Plugin_ScrAddFunction("ternary", 			&GScr_Ternary);
	Plugin_ScrAddFunction("ifundef", 			&GScr_IfUndef);

	// utitlity/convert.h
	Plugin_ScrAddFunction("tostring", 			&GScr_ToString);
	Plugin_ScrAddFunction("toint", 				&GScr_ToInt);
	Plugin_ScrAddFunction("tofloat", 			&GScr_ToFloat);

	// utitlity/stringutil.h
	Plugin_ScrAddFunction("isnullorempty",		&GScr_IsNullOrEmpty);
	Plugin_ScrAddFunction("isstringalpha", 		&GScr_IsStringAlpha);
	Plugin_ScrAddFunction("isstringfloat", 		&GScr_IsStringFloat);
	Plugin_ScrAddFunction("isstringint", 		&GScr_IsStringInt);
	Plugin_ScrAddFunction("toupper", 			&GScr_ToUpper);
	Plugin_ScrAddFunction("torgb", 				&GScr_ToRGB);
	Plugin_ScrAddFunction("hextorgb", 			&GScr_HexToRGB);

	// linq/delegate
	Plugin_ScrAddFunction("select", 			&GScr_LINQ_Select);

	// linq/predicate
	Plugin_ScrAddFunction("all", 				&GScr_LINQ_All);
	Plugin_ScrAddFunction("where", 				&GScr_LINQ_Where);
	Plugin_ScrAddFunction("any", 				&GScr_LINQ_Any);
	Plugin_ScrAddFunction("last",				&GScr_LINQ_Last);
	Plugin_ScrAddFunction("first", 				&GScr_LINQ_First);
	Plugin_ScrAddFunction("count", 				&GScr_LINQ_Count);

	// linq/enumerable
	Plugin_ScrAddFunction("getmin", 			&GScr_LINQ_Min);
	Plugin_ScrAddFunction("getmax", 			&GScr_LINQ_Max);
	Plugin_ScrAddFunction("cast", 				&GScr_LINQ_Cast);
	Plugin_ScrAddFunction("oftype", 			&GScr_LINQ_OfType);
	Plugin_ScrAddFunction("sort", 				&GScr_LINQ_Sort);
	Plugin_ScrAddFunction("average",			&GScr_LINQ_Average);
	Plugin_ScrAddFunction("sum", 				&GScr_LINQ_Sum);
	Plugin_ScrAddFunction("range",				&GScr_LINQ_Range);
	Plugin_ScrAddFunction("repeat",				&GScr_LINQ_Repeat);
	Plugin_ScrAddFunction("reverse", 			&GScr_LINQ_Reverse);

	return 0;
}

PCL void OnTerminate()
{
	curl_global_cleanup(); 	// free curl library
	mysql_library_end(); 	// free mysql library
}

/**
 * @brief Callback used to obtain information about the plugin
 * Memory pointed by info is allocated by the server binary.
 */
PCL void OnInfoRequest(pluginInfo_t *info)
{ 
	// =====  MANDATORY FIELDS  =====
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR; // Requested handler version

	// =====  OPTIONAL  FIELDS  =====
	info->pluginVersion.major = 1;
	info->pluginVersion.minor = 1;
	strncpy(info->fullName, "gsclib", sizeof(info->fullName));
	strncpy(info->shortDescription, "gsclib acts as a standard library extension for the Call of Duty 4 scripting language.", sizeof(info->shortDescription));
	strncpy(info->longDescription, "gsclib acts as a standard library extension for the Call of Duty 4 scripting language. The features this library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expresison (RegEx) support, Language Integrated Query (Linq) support, a MySQL connector for databases, casting/type conversion and other type utilities, and much more. More detailed information on each feature can be found in the documentation section.", sizeof(info->longDescription));
}
