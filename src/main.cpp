#include "Base.hpp"

#include "Game/Player.hpp"
#include "IO/File.hpp"
#include "IO/Zip.hpp"
#include "Network/FTP.hpp"
#include "Network/HTTP.hpp"
#include "Network/MySQL.hpp"
#include "System/System.hpp"
#include "Utils/Linq.hpp"
#include "Utils/Math.hpp"
#include "Utils/Print.hpp"
#include "Utils/Regex.hpp"
#include "Utils/Utils.hpp"

using namespace gsclib;

PCL int OnInit()
{
	curl_global_init(CURL_GLOBAL_ALL);

	// Game/Player
	Plugin_ScrAddMethod("getip", &Player::GetIP);
	Plugin_ScrAddMethod("getforwardmove", &Player::GetForwardMove);
	Plugin_ScrAddMethod("getrightmove", &Player::GetRightMove);
	Plugin_ScrAddMethod("getjumporigin", &Player::GetJumpOrigin);
	Plugin_ScrAddMethod("pmflags", &Player::PmFlags);
	Plugin_ScrAddMethod("setpmflags", &Player::SetPmFlags);
	Plugin_ScrAddMethod("pmtime", &Player::PmTime);
	Plugin_ScrAddMethod("setpmtime", &Player::SetPmTime);
	Plugin_ScrAddMethod("pmtype", &Player::PmType);
	Plugin_ScrAddMethod("weaponflags", &Player::WeaponFlags);

	// IO/File
	Plugin_ScrAddFunction("file_create", &File::Create);
	Plugin_ScrAddFunction("file_open", &File::Open);
	Plugin_ScrAddFunction("file_close", &File::Close);
	Plugin_ScrAddFunction("file_exists", &File::Exists);
	Plugin_ScrAddFunction("file_readline", &File::ReadLine);
	Plugin_ScrAddFunction("file_writeline", &File::WriteLine);
	Plugin_ScrAddFunction("file_readlines", &File::ReadLines);
	Plugin_ScrAddFunction("file_writelines", &File::WriteLines);
	Plugin_ScrAddFunction("file_read", &File::Read);
	Plugin_ScrAddFunction("file_write", &File::Write);
	Plugin_ScrAddFunction("file_seek", &File::Seek);
	Plugin_ScrAddFunction("file_delete", &File::Delete);
	Plugin_ScrAddFunction("file_mkdir", &File::MkDir);
	Plugin_ScrAddFunction("file_rmdir", &File::RmDir);
	Plugin_ScrAddFunction("file_readdir", &File::ReadDir);

	// IO/Zip
	Plugin_ScrAddFunction("zip_add", &Zip::Add);
	Plugin_ScrAddFunction("zip_rename", &Zip::Rename);
	Plugin_ScrAddFunction("zip_delete", &Zip::Delete);
	Plugin_ScrAddFunction("zip_open", &Zip::Open);
	Plugin_ScrAddFunction("zip_close", &Zip::Close);

	// Network/FTP
	Plugin_ScrAddFunction("ftp_init", &Ftp::Initialize);
	Plugin_ScrAddFunction("ftp_free", &Ftp::Free);
	Plugin_ScrAddFunction("sftp_connect", &Ftp::SftpConnect);
	Plugin_ScrAddFunction("ftp_connect", &Ftp::Connect);
	Plugin_ScrAddFunction("ftp_close", &Ftp::Close);
	Plugin_ScrAddFunction("ftp_shell", &Ftp::Shell);
	Plugin_ScrAddFunction("ftp_postfile", &Ftp::PostFile);
	Plugin_ScrAddFunction("ftp_getfile", &Ftp::GetFile);
	Plugin_ScrAddFunction("ftp_addheader", &Ftp::AddHeader);
	Plugin_ScrAddFunction("ftp_addopt", &Ftp::AddOpt);
	Plugin_ScrAddFunction("ftp_headercleanup", &Ftp::HeaderCleanup);
	Plugin_ScrAddFunction("ftp_optcleanup", &Ftp::OptCleanup);

	// Network/HTTP
	Plugin_ScrAddFunction("http_init", &Http::Initialize);
	Plugin_ScrAddFunction("http_free", &Http::Free);
	Plugin_ScrAddFunction("http_post", &Http::Post);
	Plugin_ScrAddFunction("http_postfile", &Http::PostFile);
	Plugin_ScrAddFunction("http_get", &Http::Get);
	Plugin_ScrAddFunction("http_getfile", &Http::GetFile);
	Plugin_ScrAddFunction("http_response", &Http::GetResponse);
	Plugin_ScrAddFunction("http_addheader", &Http::AddHeader);
	Plugin_ScrAddFunction("http_addopt", &Http::AddOpt);
	Plugin_ScrAddFunction("http_headercleanup", &Http::HeaderCleanup);
	Plugin_ScrAddFunction("http_optcleanup", &Http::OptCleanup);

	// Network/MySQL
	Plugin_ScrAddFunction("sql_prepare", &MySql::Prepare);
	Plugin_ScrAddFunction("sql_bindparam", &MySql::BindParam);
	Plugin_ScrAddFunction("sql_execute", &MySql::Execute);
	Plugin_ScrAddFunction("sql_escapestring", &MySql::EscapeString);
	Plugin_ScrAddFunction("sql_hexstring", &MySql::HexString);
	Plugin_ScrAddFunction("sql_selectdb", &MySql::SelectDB);
	Plugin_ScrAddFunction("sql_query", &MySql::Query);
	Plugin_ScrAddFunction("sql_numrows", &MySql::NumRows);
	Plugin_ScrAddFunction("sql_numfields", &MySql::NumFields);
	Plugin_ScrAddFunction("sql_affectedrows", &MySql::AffectedRows);
	Plugin_ScrAddFunction("sql_fetchrowsdict", &MySql::FetchRowsDict);
	Plugin_ScrAddFunction("sql_fetchrows", &MySql::FetchRows);
	Plugin_ScrAddFunction("sql_fetchrowdict", &MySql::FetchRowDict);
	Plugin_ScrAddFunction("sql_fetchrow", &MySql::FetchRow);
	Plugin_ScrAddFunction("sql_fetchfields", &MySql::FetchFields);
	Plugin_ScrAddFunction("sql_listdb", &MySql::ListDB);
	Plugin_ScrAddFunction("sql_listtables", &MySql::ListTables);
	Plugin_ScrAddFunction("sql_version", &MySql::Version);
	Plugin_ScrAddFunction("sql_connect", &MySql::Connect);
	Plugin_ScrAddFunction("sql_close", &MySql::Close);
	Plugin_ScrAddFunction("sql_free", &MySql::Free);

	// System/System
	Plugin_ScrAddFunction("gsclib_init", &System::Initialize);
	Plugin_ScrAddFunction("system", &System::Execute);
	Plugin_ScrAddFunction("getsystime", &System::GetSysTime);
	Plugin_ScrAddFunction("criticalsection", &System::CriticalSectionCreate);
	Plugin_ScrAddFunction("criticalsections", &System::CriticalSectionList);
	Plugin_ScrAddFunction("entercriticalsection", &System::EnterCriticalSection);
	Plugin_ScrAddFunction("leavecriticalsection", &System::LeaveCriticalSection);
	Plugin_ScrAddFunction("asyncstatus", &System::AsyncStatus);
	Plugin_ScrAddFunction("asynccancel", &System::AsyncCancel);
	Plugin_ScrAddFunction("iswindows", &System::IsWindows);
	Plugin_ScrAddFunction("islinux", &System::IsLinux);
	Plugin_ScrAddFunction("cod4x_version", &System::CoD4XVersion);
	Plugin_ScrAddFunction("gsclib_version", &System::GSCLIBVersion);
	Plugin_ScrAddFunction("exit", &System::Exit);

	// Utils/Linq
	Plugin_ScrAddFunction("select", &Linq::Select);
	Plugin_ScrAddFunction("foreach", &Linq::Foreach);
	Plugin_ScrAddFunction("aggregate", &Linq::Aggregate);
	Plugin_ScrAddFunction("all", &Linq::All);
	Plugin_ScrAddFunction("where", &Linq::Where);
	Plugin_ScrAddFunction("any", &Linq::Any);
	Plugin_ScrAddFunction("last", &Linq::Last);
	Plugin_ScrAddFunction("first", &Linq::First);
	Plugin_ScrAddFunction("count", &Linq::Count);
	Plugin_ScrAddFunction("getmin", &Linq::Min);
	Plugin_ScrAddFunction("getmax", &Linq::Max);
	Plugin_ScrAddFunction("cast", &Linq::Cast);
	Plugin_ScrAddFunction("oftype", &Linq::OfType);
	Plugin_ScrAddFunction("sort", &Linq::Sort);
	Plugin_ScrAddFunction("average", &Linq::Average);
	Plugin_ScrAddFunction("sum", &Linq::Sum);
	Plugin_ScrAddFunction("range", &Linq::Range);
	Plugin_ScrAddFunction("repeat", &Linq::Repeat);
	Plugin_ScrAddFunction("reverse", &Linq::Reverse);
	Plugin_ScrAddFunction("concat", &Linq::Concat);
	Plugin_ScrAddFunction("chunk", &Linq::Chunk);
	Plugin_ScrAddFunction("contains", &Linq::Contains);
	Plugin_ScrAddFunction("indexof", &Linq::IndexOf);
	Plugin_ScrAddFunction("remove", &Linq::Remove);
	Plugin_ScrAddFunction("removeat", &Linq::RemoveAt);

	// Utils/Math
	Plugin_ScrAddFunction("fmod", &Math::Fmod);
	Plugin_ScrAddFunction("tan1", &Math::Tan);
	Plugin_ScrAddFunction("atan1", &Math::Atan);
	Plugin_ScrAddFunction("atan2", &Math::Atan2);
	Plugin_ScrAddFunction("cos1", &Math::Cos);
	Plugin_ScrAddFunction("acos1", &Math::Acos);
	Plugin_ScrAddFunction("sin1", &Math::Sin);
	Plugin_ScrAddFunction("asin1", &Math::Asin);

	// Utils/Regex
	Plugin_ScrAddFunction("regexmatch", &Regex::Match);
	Plugin_ScrAddFunction("regexsplit", &Regex::Split);
	Plugin_ScrAddFunction("regexreplace", &Regex::Replace);

	// Utils/Utils
	Plugin_ScrAddFunction("tostring", &Utils::ToString);
	Plugin_ScrAddFunction("toint", &Utils::ToInt);
	Plugin_ScrAddFunction("tofloat", &Utils::ToFloat);
	Plugin_ScrAddFunction("gettype", &Utils::GetType);
	Plugin_ScrAddFunction("ternary", &Utils::Ternary);
	Plugin_ScrAddFunction("ifundef", &Utils::IfUndef);
	Plugin_ScrAddFunction("sysprint", &Utils::SysPrint);
	Plugin_ScrAddFunction("sysprintln", &Utils::SysPrintLn);
	Plugin_ScrAddFunction("comprint", &Utils::ComPrint);
	Plugin_ScrAddFunction("comprintln", &Utils::ComPrintLn);
	Plugin_ScrAddFunction("isnullorempty", &Utils::IsNullOrEmpty);
	Plugin_ScrAddFunction("isstringalpha", &Utils::IsStringAlpha);
	Plugin_ScrAddFunction("isstringfloat", &Utils::IsStringFloat);
	Plugin_ScrAddFunction("isstringint", &Utils::IsStringInt);
	Plugin_ScrAddFunction("torgb", &Utils::ToRGB);
	Plugin_ScrAddFunction("hextorgb", &Utils::HexToRGB);
	Plugin_ScrAddFunction("fmt", &Utils::Fmt);
	Plugin_ScrAddFunction("trim", &Utils::Trim);
	Plugin_ScrAddFunction("startswith", &Utils::StartsWith);
	Plugin_ScrAddFunction("endswith", &Utils::EndsWith);
	Plugin_ScrAddFunction("strjoin", &Utils::StrJoin);
	Plugin_ScrAddFunction("replace", &Utils::Replace);
	Plugin_ScrAddFunction("pathjoin", &Utils::PathJoin);

	return 0;
}

PCL void OnTerminate()
{
	Async::Shutdown();

	curl_global_cleanup();
}

PCL void OnInfoRequest(pluginInfo_t* info)
{
	info->handlerVersion.major = PLUGIN_HANDLER_VERSION_MAJOR;
	info->handlerVersion.minor = PLUGIN_HANDLER_VERSION_MINOR;

	info->pluginVersion.major = GSCLIB_VERSION_MAJOR;
	info->pluginVersion.minor = GSCLIB_VERSION_MINOR;

	std::strncpy(info->fullName, "gsclib", sizeof(info->fullName));

	std::strncpy(info->shortDescription,
		"gsclib acts as a standard library extension for the Call of Duty 4 scripting language.",
		sizeof(info->shortDescription));

	std::strncpy(info->longDescription,
		"gsclib acts as a standard library extension for the Call of Duty 4 scripting language. The features this "
		"library provides consists of an FTP/FTPS/SFTP client, an HTTP/HTTPS client, Regular Expression (RegEx) "
		"support, Language Integrated Query (Linq) support, a MySQL/MariaDB connector for databases, casting/type "
		"conversion and other type utilities, and much more. More detailed information on each feature can be found "
		"in the documentation section.",
		sizeof(info->longDescription));
}
