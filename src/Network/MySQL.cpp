#include "MySql.hpp"

namespace gsclib
{
	void MySql::Version()
	{
		CHECK_PARAMS(0, "Usage: SQL_Version()\n");

		if (!Driver)
			Driver = sql::mariadb::get_driver_instance();

		Plugin_Scr_AddString(std::format("{}.{}", Driver->getMajorVersion(), Driver->getMinorVersion()).c_str());
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

			Plugin_Printf("Connected to MariaDB Server\n");
			Plugin_Scr_AddBool(qtrue);
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("Connection failed: {}\n", e.what()).c_str());
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
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
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
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
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
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
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
			request->PreparedStatement.reset(Connection->prepareStatement(request->Query));
			Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(task.get()));
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
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
		if (!request->PreparedStatement)
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
				request->PreparedStatement->setString(paramIndex, value);
				request->Params.push_back(value);
				break;
			}
			case VAR_INTEGER:
				request->PreparedStatement->setInt(paramIndex, variable->u.intValue);
				request->Params.push_back(variable->u.intValue);
				break;
			case VAR_FLOAT:
				request->PreparedStatement->setFloat(paramIndex, variable->u.floatValue);
				request->Params.push_back(variable->u.floatValue);
				break;
			default:
				request->PreparedStatement->setNull(paramIndex, 0);
				request->Params.push_back(std::monostate{});
				break;
			}
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
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
		auto request = task->GetData<MySqlRequest>();
		if (!request->PreparedStatement)
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
		Plugin_Scr_AddInt(request ? static_cast<int>(request->AffectedCount) : 0);
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
			Plugin_Scr_Error("MySQL result not found.\n");
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
			int columnType = meta->getColumnType(i);

			if (request->Result->isNull(i))
			{
				Plugin_Scr_AddUndefined();
				continue;
			}
			switch (columnType)
			{
			case sql::DataType::TINYINT:
			case sql::DataType::SMALLINT:
			case sql::DataType::INTEGER:
			case sql::DataType::BIGINT:
				Plugin_Scr_AddInt(request->Result->getInt(i));
				break;
			case sql::DataType::FLOAT:
			case sql::DataType::DOUBLE:
			case sql::DataType::DECIMAL:
			case sql::DataType::NUMERIC:
				Plugin_Scr_AddFloat(request->Result->getFloat(i));
				break;
			default:
				Plugin_Scr_AddString(request->Result->getString(i).c_str());
				break;
			}
			if (stringIndexed)
				Plugin_Scr_AddArrayStringIndexed(Plugin_Scr_AllocString(meta->getColumnName(i).c_str()));
			else
				Plugin_Scr_AddArray();
		}
		return true;
	}

	void MySql::FetchQueryRows(MySqlRequest* request, bool stringIndexed)
	{
		Plugin_Scr_MakeArray();
		if (!request->Result)
			return;

		try
		{
			request->Result->beforeFirst();
			while (FetchQueryRow(request, stringIndexed))
				Plugin_Scr_AddArray();
		}
		catch (sql::SQLException& e)
		{
			Plugin_Scr_Error(std::format("{}\n", e.what()).c_str());
		}
	}

	void MySql::ExecuteQuery(AsyncTask* task)
	{
		auto request = task->GetData<MySqlRequest>();

		try
		{
			request->QueryStatement.reset(request->Connection->createStatement());
			bool hasResultSet = request->QueryStatement->execute(request->Query);

			if (hasResultSet)
			{
				request->Result.reset(request->QueryStatement->getResultSet());
				request->AffectedCount = 0;
			}
			else
			{
				request->Result.reset();
				request->AffectedCount = request->QueryStatement->getUpdateCount();
			}
			task->Status = AsyncStatus::Successful;
		}
		catch (sql::SQLException& e)
		{
			task->Error = e.what();
			task->Status = AsyncStatus::Failure;
			Plugin_Printf("%s\n", task->Error.c_str());
		}
	}

	void MySql::ExecuteStatement(AsyncTask* task)
	{
		auto request = task->GetData<MySqlRequest>();

		try
		{
			bool hasResultSet = request->PreparedStatement->execute();

			if (hasResultSet)
			{
				request->Result.reset(request->PreparedStatement->getResultSet());
				request->AffectedCount = 0;
			}
			else
			{
				request->Result.reset();
				request->AffectedCount = request->PreparedStatement->getUpdateCount();
			}
			task->Status = AsyncStatus::Successful;
		}
		catch (sql::SQLException& e)
		{
			task->Error = e.what();
			task->Status = AsyncStatus::Failure;
			Plugin_Printf("%s\n", task->Error.c_str());
		}
	}
}
