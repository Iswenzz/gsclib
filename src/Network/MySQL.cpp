#include "MySql.hpp"

namespace gsclib
{
	void MySql::Version()
	{
		CHECK_PARAMS(0, "Usage: SQL_Version()\n");

		if (!Driver)
			Driver = sql::mariadb::get_driver_instance();

		Plugin_Scr_AddString(Driver->getName().c_str());
	}

	void MySql::Connect()
	{
		CHECK_PARAMS(4, "Usage: SQL_Connect(<host>, <port>, <user>, <password>)\n");

		const char* host = Plugin_Scr_GetString(0);
		int port = Plugin_Scr_GetInt(1);
		const char* user = Plugin_Scr_GetString(2);
		const char* password = Plugin_Scr_GetString(3);

		try
		{
			if (Connection)
				Connection.reset();

			if (!Driver)
				Driver = sql::mariadb::get_driver_instance();

			sql::SQLString url = std::format("jdbc:mariadb://{}:{}", host, port);
			sql::Properties properties({ { "user", user }, { "password", password } });
			properties["autoReconnect"] = "true";

			Connection.reset(Driver->connect(url, properties));

			Plugin_Printf("SQL_Connect(): Connected to MariaDB Server\n");
			Plugin_Scr_AddBool(qtrue);
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_Connect(): Connection failed: {}\n", e.what()).c_str());
			Plugin_Scr_AddBool(qfalse);
		}
	}

	void MySql::Close()
	{
		CHECK_PARAMS(0, "Usage: SQL_Close()\n");

		if (Connection)
		{
			Connection->close();
			Connection.reset();
		}
		Plugin_Scr_AddBool(qtrue);
	}

	void MySql::SelectDB()
	{
		CHECK_PARAMS(1, "Usage: SQL_SelectDB(<database>)\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		try
		{
			Connection->setSchema(Plugin_Scr_GetString(0));
			Plugin_Scr_AddBool(qtrue);
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_SelectDB(): {}\n", e.what()).c_str());
			Plugin_Scr_AddBool(qfalse);
		}
	}

	void MySql::ListDB()
	{
		CHECK_PARAMS(0, "Usage: SQL_ListDB()\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		try
		{
			std::unique_ptr<sql::Statement> stmt(Connection->createStatement());
			std::unique_ptr<sql::ResultSet> result(stmt->executeQuery("SHOW DATABASES"));

			Plugin_Scr_MakeArray();
			while (result->next())
			{
				Plugin_Scr_AddString(result->getString(1).c_str());
				Plugin_Scr_AddArray();
			}
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_ListDB(): {}\n", e.what()).c_str());
		}
	}

	void MySql::ListTables()
	{
		CHECK_PARAMS(0, "Usage: SQL_ListTables()\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		try
		{
			std::unique_ptr<sql::Statement> stmt(Connection->createStatement());
			std::unique_ptr<sql::ResultSet> result(stmt->executeQuery("SHOW TABLES"));

			Plugin_Scr_MakeArray();
			while (result->next())
			{
				Plugin_Scr_AddString(result->getString(1).c_str());
				Plugin_Scr_AddArray();
			}
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_ListTables(): {}\n", e.what()).c_str());
		}
	}

	void MySql::EscapeString()
	{
		CHECK_PARAMS(1, "Usage: SQL_EscapeString(<string>)\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		const char* input = Plugin_Scr_GetString(0);
		std::string escaped;
		escaped.reserve(std::string_view(input).size() * 2);

		for (const char* p = input; *p; ++p)
		{
			switch (*p)
			{
			case '\'':
				escaped += "\\'";
				break;
			case '"':
				escaped += "\\\"";
				break;
			case '\\':
				escaped += "\\\\";
				break;
			case '\0':
				escaped += "\\0";
				break;
			case '\n':
				escaped += "\\n";
				break;
			case '\r':
				escaped += "\\r";
				break;
			case '\x1a':
				escaped += "\\Z";
				break;
			default:
				escaped += *p;
				break;
			}
		}
		Plugin_Scr_AddString(escaped.c_str());
	}

	void MySql::HexString()
	{
		CHECK_PARAMS(1, "Usage: SQL_HexString(<string>)\n");

		const char* input = Plugin_Scr_GetString(0);
		std::string hex;
		hex.reserve(std::string_view(input).size() * 2);

		for (const char* p = input; *p; ++p)
			hex += std::format("{:02X}", static_cast<unsigned char>(*p));

		Plugin_Scr_AddString(hex.c_str());
	}

	void MySql::Query()
	{
		CHECK_PARAMS(1, "Usage: SQL_Query(<query>)\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		auto request = new MySqlRequest();
		auto task = Async::Create(request);
		request->Connection = Connection.get();
		request->Query = Plugin_Scr_GetString(0);

		task->Status = AsyncStatus::Running;
		Async::Submit([task] { ExecuteQuery(task.get()); });

		Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(task.get()));
	}

	void MySql::Prepare()
	{
		CHECK_PARAMS(1, "Usage: SQL_Prepare(<query>)\n");

		if (!Connection)
		{
			Plugin_Scr_Error("MySQL connection not found.\n");
			return;
		}
		auto request = new MySqlRequest();
		auto task = Async::Create(request);
		request->Connection = Connection.get();
		request->Query = Plugin_Scr_GetString(0);

		try
		{
			request->Statement.reset(Connection->prepareStatement(request->Query));
			Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(task.get()));
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_Prepare(): {}\n", e.what()).c_str());
			Plugin_Scr_AddBool(qfalse);
			delete request;
			task->Data = nullptr;
		}
	}

	void MySql::BindParam()
	{
		CHECK_PARAMS(3, "Usage: SQL_BindParam(<request>, <value>, <type>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		VariableValue* variable = Plugin_Scr_SelectParam(1);

		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		if (!request->Statement)
		{
			Plugin_Scr_Error("MySQL statement not found.\n");
			return;
		}
		int paramIndex = static_cast<int>(request->Params.size()) + 1;

		try
		{
			switch (variable->type)
			{
			case VAR_STRING:
			case VAR_ISTRING:
			{
				std::string value = Plugin_SL_ConvertToString(variable->u.stringValue);
				request->Statement->setString(paramIndex, value);
				request->Params.push_back(value);
				break;
			}
			case VAR_INTEGER:
				request->Statement->setInt(paramIndex, variable->u.intValue);
				request->Params.push_back(variable->u.intValue);
				break;
			case VAR_FLOAT:
				request->Statement->setFloat(paramIndex, variable->u.floatValue);
				request->Params.push_back(variable->u.floatValue);
				break;
			default:
				request->Statement->setNull(paramIndex, 0);
				request->Params.push_back(std::monostate{});
				break;
			}
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("SQL_BindParam(): {}\n", e.what()).c_str());
		}
	}

	void MySql::Execute()
	{
		CHECK_PARAMS(1, "Usage: SQL_Execute(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Pending)
		{
			Plugin_Scr_Error("MySQL request is pending.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		if (!request->Statement)
		{
			Plugin_Scr_Error("MySQL statement not found.\n");
			return;
		}
		task->Status = AsyncStatus::Running;
		Async::Submit([task] { ExecuteStatement(task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void MySql::NumRows()
	{
		CHECK_PARAMS(1, "Usage: SQL_NumRows(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		Plugin_Scr_AddInt(request->Result ? static_cast<int>(request->Result->rowsCount()) : 0);
	}

	void MySql::NumFields()
	{
		CHECK_PARAMS(1, "Usage: SQL_NumFields(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		if (request->Result)
		{
			sql::ResultSetMetaData* meta = request->Result->getMetaData();
			Plugin_Scr_AddInt(static_cast<int>(meta->getColumnCount()));
		}
		else
			Plugin_Scr_AddInt(0);
	}

	void MySql::AffectedRows()
	{
		CHECK_PARAMS(1, "Usage: SQL_AffectedRows(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		Plugin_Scr_AddInt(request->Statement ? static_cast<int>(request->Statement->getUpdateCount()) : 0);
	}

	void MySql::FetchRow()
	{
		CHECK_PARAMS(1, "Usage: SQL_FetchRow(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		FetchQueryRow(request, false);
	}

	void MySql::FetchRows()
	{
		CHECK_PARAMS(1, "Usage: SQL_FetchRows(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		FetchQueryRows(request, false);
	}

	void MySql::FetchRowDict()
	{
		CHECK_PARAMS(1, "Usage: SQL_FetchRowDict(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		FetchQueryRow(request, true);
	}

	void MySql::FetchRowsDict()
	{
		CHECK_PARAMS(1, "Usage: SQL_FetchRowsDict(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		FetchQueryRows(request, true);
	}

	void MySql::FetchFields()
	{
		CHECK_PARAMS(1, "Usage: SQL_FetchFields(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		if (!request->Result)
		{
			Plugin_Scr_AddUndefined();
			Plugin_Scr_Error("SQL_FetchFields(): MySQL result not found.\n");
			return;
		}
		sql::ResultSetMetaData* meta = request->Result->getMetaData();
		unsigned int numFields = meta->getColumnCount();

		Plugin_Scr_MakeArray();
		for (unsigned int i = 1; i <= numFields; i++)
		{
			Plugin_Scr_AddString(meta->getColumnName(i).c_str());
			Plugin_Scr_AddArray();
		}
	}

	void MySql::Free()
	{
		CHECK_PARAMS(1, "Usage: SQL_Free(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("MySQL request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Pending)
		{
			Plugin_Scr_Error("MySQL request is pending.\n");
			return;
		}
		auto request = task->GetData<MySqlRequest>();
		delete request;
		task->Data = nullptr;
		Plugin_Scr_AddBool(qtrue);
	}

	bool MySql::FetchQueryRow(MySqlRequest* request, bool stringIndexed)
	{
		if (!request->Result || !request->Result->next())
			return false;

		sql::ResultSetMetaData* meta = request->Result->getMetaData();
		unsigned int numFields = meta->getColumnCount();

		Plugin_Scr_MakeArray();
		for (unsigned int i = 1; i <= numFields; i++)
		{
			if (request->Result->isNull(i))
				Plugin_Scr_AddUndefined();
			else
				Plugin_Scr_AddString(request->Result->getString(i).c_str());

			if (stringIndexed)
				Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(meta->getColumnName(i).c_str()));
			else
				Plugin_Scr_AddArray();
		}
		return true;
	}

	void MySql::FetchQueryRows(MySqlRequest* request, bool stringIndexed)
	{
		if (!request->Result)
		{
			Plugin_Scr_MakeArray();
			return;
		}
		Plugin_Scr_MakeArray();
		request->Result->beforeFirst();

		while (FetchQueryRow(request, stringIndexed))
			Plugin_Scr_AddArray();
	}

	void MySql::ExecuteQuery(AsyncTask* task)
	{
		auto request = task->GetData<MySqlRequest>();

		try
		{
			std::unique_ptr<sql::Statement> stmt(request->Connection->createStatement());
			request->Result.reset(stmt->executeQuery(request->Query));
			task->Status = AsyncStatus::Successful;
		}
		catch (sql::SQLException& e)
		{
			task->Error = e.what();
			task->Status = AsyncStatus::Failure;
		}
	}

	void MySql::ExecuteStatement(AsyncTask* task)
	{
		auto request = task->GetData<MySqlRequest>();

		try
		{
			request->Result.reset(request->Statement->executeQuery());
			task->Status = AsyncStatus::Successful;
		}
		catch (sql::SQLException& e)
		{
			task->Error = e.what();
			task->Status = AsyncStatus::Failure;
		}
	}
}
