#pragma once
#include "Base.hpp"

#include <conncpp.hpp>
#include <variant>

namespace gsclib
{
	using SqlValue = std::variant<std::monostate, int, float, std::string>;

	struct MySqlRequest
	{
		sql::Connection* Connection = nullptr;
		std::unique_ptr<sql::PreparedStatement> Statement;
		std::unique_ptr<sql::ResultSet> Result;
		std::string Query;
		std::vector<SqlValue> Params;

		MySqlRequest() = default;
		~MySqlRequest() = default;
	};

	class MySql
	{
	public:
		static void Version();
		static void Connect();
		static void Close();
		static void SelectDB();
		static void ListDB();
		static void ListTables();
		static void EscapeString();
		static void HexString();
		static void Query();
		static void Prepare();
		static void BindParam();
		static void Execute();
		static void NumRows();
		static void NumFields();
		static void AffectedRows();
		static void FetchRow();
		static void FetchRows();
		static void FetchRowDict();
		static void FetchRowsDict();
		static void FetchFields();
		static void Free();

	private:
		static inline std::unique_ptr<sql::Connection> Connection;
		static inline sql::Driver* Driver = nullptr;

		static bool FetchQueryRow(MySqlRequest* request, bool stringIndexed);
		static void FetchQueryRows(MySqlRequest* request, bool stringIndexed);
		static void ExecuteQuery(AsyncTask* task);
		static void ExecuteStatement(AsyncTask* task);
	};
}
