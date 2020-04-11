#include "linq/enumerable.h"
#include "linq/predicate.h"
#include "linq/delegate.h"

#include "data/mysql.h"
#include "data/regex.h"

#include "utility/util.h"
#include "utility/stringutil.h"
#include "utility/convert.h"

#ifndef PLUGIN_INCLUDES
#include "../../pinc.h"
#endif

PCL int OnInit()
{
	// data/mysql.h
	Plugin_ScrAddFunction("sql_escapestring", 	&GScr_MySQL_EscapeString);
	Plugin_ScrAddFunction("sql_hexstring", 		&GScr_MySQL_HexString);
	Plugin_ScrAddFunction("sql_selectdb", 		&GScr_MySQL_SelectDB);
	Plugin_ScrAddFunction("sql_query", 			&GScr_MySQL_Query);
	Plugin_ScrAddFunction("sql_numrows", 		&GScr_MySQL_NumRows);
	Plugin_ScrAddFunction("sql_numfields", 		&GScr_MySQL_NumFields);
	Plugin_ScrAddFunction("sql_affectedrows",	&GScr_MySQL_AffectedRows);
	Plugin_ScrAddFunction("sql_fetchrows", 		&GScr_MySQL_FetchRows);
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
	Plugin_ScrAddFunction("min", 				&GScr_LINQ_Min);
	Plugin_ScrAddFunction("max", 				&GScr_LINQ_Max);
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

// Function used to obtain information about the plugin
// Memory pointed by info is allocated by the server binary
PCL void OnInfoRequest(pluginInfo_t *info)
{ 
	// =====  MANDATORY FIELDS  =====
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR; // Requested handler version

	// =====  OPTIONAL  FIELDS  =====
	info->pluginVersion.major = 1;
	info->pluginVersion.minor = 0;
	strncpy(info->fullName, "gsclib", sizeof(info->fullName));
	strncpy(info->shortDescription, "", sizeof(info->shortDescription));
	strncpy(info->longDescription, "", sizeof(info->longDescription));
}
