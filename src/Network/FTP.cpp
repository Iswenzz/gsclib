#include "FTP.hpp"

namespace gsclib
{
	FtpConnection::FtpConnection()
	{
		Easy = curl_easy_init();
		Multi = curl_multi_init();

		if (Easy && Multi)
			curl_multi_add_handle(Multi, Easy);
	}

	FtpConnection::~FtpConnection()
	{
		if (Multi && Easy)
			curl_multi_remove_handle(Multi, Easy);
		if (Multi)
			curl_multi_cleanup(Multi);
		if (Easy)
			curl_easy_cleanup(Easy);
	}

	FtpRequest::FtpRequest()
	{
		Easy = curl_easy_init();
		Multi = curl_multi_init();

		if (Easy && Multi)
			curl_multi_add_handle(Multi, Easy);
	}

	FtpRequest::~FtpRequest()
	{
		if (Headers)
			curl_slist_free_all(Headers);
		if (Multi && Easy)
			curl_multi_remove_handle(Multi, Easy);
		if (Multi)
			curl_multi_cleanup(Multi);
		if (Easy)
			curl_easy_cleanup(Easy);
	}

	size_t Ftp::WriteCallback(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		auto* file = static_cast<std::ofstream*>(userdata);
		size_t totalSize = size * nmemb;
		file->write(static_cast<char*>(ptr), totalSize);
		return file->good() ? totalSize : 0;
	}

	size_t Ftp::ReadCallback(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		auto* file = static_cast<std::ifstream*>(userdata);
		file->read(static_cast<char*>(ptr), size * nmemb);
		return static_cast<size_t>(file->gcount());
	}

	void Ftp::Initialize()
	{
		CHECK_PARAMS(0, "Usage: FTP_Init()\n");

		if (!Connection)
		{
			Plugin_Scr_Error("FTP Connection not found.\n");
			return;
		}
		auto request = new FtpRequest();
		auto task = Async::Create(request);
		Plugin_Scr_AddInt(reinterpret_cast<uintptr_t>(task.get()));
	}

	void Ftp::Free()
	{
		CHECK_PARAMS(1, "Usage: FTP_Free(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("FTP request is running.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		delete request;
		task->Data = nullptr;
		Plugin_Scr_AddBool(qtrue);
	}

	void Ftp::Connect()
	{
		CHECK_PARAMS(4, "Usage: FTP_Connect(<hostname>, <username>, <password>, <port>)\n");

		bool success = DoConnect("ftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1), Plugin_Scr_GetString(2),
			static_cast<unsigned short>(Plugin_Scr_GetInt(3)));

		Plugin_Scr_AddBool(success ? qtrue : qfalse);
	}

	void Ftp::SftpConnect()
	{
		CHECK_PARAMS(4, "Usage: SFTP_Connect(<hostname>, <username>, <password>, <port>)\n");

		bool success = DoConnect("sftp", Plugin_Scr_GetString(0), Plugin_Scr_GetString(1), Plugin_Scr_GetString(2),
			static_cast<unsigned short>(Plugin_Scr_GetInt(3)));

		Plugin_Scr_AddBool(success ? qtrue : qfalse);
	}

	bool Ftp::DoConnect(const std::string& protocol, const std::string& hostname, const std::string& username,
		const std::string& password, unsigned short port)
	{
		Connection.reset();
		Connection = std::make_unique<FtpConnection>();
		Connection->Url = std::format("{}://{}@{}/", protocol, username, hostname);
		Connection->Password = password;
		Connection->Port = port;

		return Connection->Easy != nullptr;
	}

	void Ftp::Close()
	{
		CHECK_PARAMS(0, "Usage: FTP_Close()\n");

		if (Connection)
		{
			Connection.reset();
			Plugin_Scr_AddBool(qtrue);
			return;
		}
		Plugin_Scr_AddBool(qfalse);
	}

	void Ftp::Shell()
	{
		CHECK_PARAMS(1, "Usage: FTP_Shell(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("FTP request is running.\n");
			return;
		}
		if (!Connection)
		{
			Plugin_Scr_Error("FTP Connection not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();

		ApplyHeaders(request, CURLOPT_QUOTE);
		curl_easy_setopt(request->Easy, CURLOPT_URL, Connection->Url.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PASSWORD, Connection->Password.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PORT, static_cast<long>(Connection->Port));
		curl_easy_setopt(request->Easy, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		ApplyOpts(request);

		task->Status = AsyncStatus::Running;
		Async::Submit([task] { Execute(task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Ftp::PostFile()
	{
		CHECK_PARAMS(3, "Usage: FTP_PostFile(<request>, <filepath>, <uploadtopath>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		const char* filepath = Plugin_Scr_GetString(1);
		const char* uploadPath = Plugin_Scr_GetString(2);

		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("FTP request is running.\n");
			return;
		}
		if (!Connection)
		{
			Plugin_Scr_Error("FTP Connection not found.\n");
			return;
		}
		std::ifstream testFile(filepath, std::ios::binary | std::ios::ate);

		if (!testFile.is_open())
		{
			Plugin_Scr_Error(std::format("Couldn't open {} {}\n", filepath, std::strerror(errno)).c_str());
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		auto fileSize = testFile.tellg();
		testFile.close();

		auto request = task->GetData<FtpRequest>();
		request->Filepath = filepath;
		std::string url = Connection->Url + uploadPath;

		ApplyHeaders(request, CURLOPT_POSTQUOTE);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PASSWORD, Connection->Password.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PORT, static_cast<long>(Connection->Port));
		curl_easy_setopt(request->Easy, CURLOPT_UPLOAD, 1L);
		curl_easy_setopt(request->Easy, CURLOPT_INFILESIZE_LARGE, static_cast<curl_off_t>(fileSize));
		curl_easy_setopt(request->Easy, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		ApplyOpts(request);

		task->Status = AsyncStatus::Running;

		Async::Submit([task] { ExecutePostFile(task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Ftp::GetFile()
	{
		CHECK_PARAMS(3, "Usage: FTP_GetFile(<request>, <savefilepath>, <downloadfilepath>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		const char* downloadPath = Plugin_Scr_GetString(2);

		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		if (task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("FTP request is running.\n");
			return;
		}
		if (!Connection)
		{
			Plugin_Scr_Error("FTP Connection not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		request->Filepath = Plugin_Scr_GetString(1);
		std::string url = Connection->Url + downloadPath;

		ApplyHeaders(request, CURLOPT_PREQUOTE);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PASSWORD, Connection->Password.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_PORT, static_cast<long>(Connection->Port));
		curl_easy_setopt(request->Easy, CURLOPT_SSH_AUTH_TYPES, CURLSSH_AUTH_PASSWORD);
		ApplyOpts(request);

		task->Status = AsyncStatus::Running;

		Async::Submit([task] { ExecuteGetFile(task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Ftp::AddHeader()
	{
		CHECK_PARAMS(2, "Usage: FTP_AddHeader(<request>, <header>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		request->HeaderList.push_back(Plugin_Scr_GetString(1));
	}

	void Ftp::AddOpt()
	{
		CHECK_PARAMS(3, "Usage: FTP_AddOpt(<request>, <opt>, <value>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		auto opt = static_cast<CURLoption>(Plugin_Scr_GetInt(1));
		VariableValue param = *Plugin_Scr_SelectParam(2);
		request->Opts.push_back({ opt, param });
	}

	void Ftp::HeaderCleanup()
	{
		CHECK_PARAMS(1, "Usage: FTP_HeaderCleanup(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		request->HeaderList.clear();
		if (request->Headers)
		{
			curl_slist_free_all(request->Headers);
			request->Headers = nullptr;
		}
	}

	void Ftp::OptCleanup()
	{
		CHECK_PARAMS(1, "Usage: FTP_OptCleanup(<request>)\n");

		auto task = reinterpret_cast<AsyncTask*>(Plugin_Scr_GetInt(0));
		if (!task)
		{
			Plugin_Scr_Error("FTP request not found.\n");
			return;
		}
		auto request = task->GetData<FtpRequest>();
		request->Opts.clear();
	}

	void Ftp::ApplyHeaders(FtpRequest* request, CURLoption headerType)
	{
		if (!request || request->HeaderList.empty())
			return;

		for (const auto& header : request->HeaderList)
			request->Headers = curl_slist_append(request->Headers, header.c_str());

		curl_easy_setopt(request->Easy, headerType, request->Headers);
	}

	void Ftp::ApplyOpts(FtpRequest* request)
	{
		if (!request)
			return;

		for (const auto& [opt, param] : request->Opts)
		{
			switch (param.type)
			{
			case VAR_INTEGER:
				curl_easy_setopt(request->Easy, opt, static_cast<long>(param.u.intValue));
				break;
			case VAR_FLOAT:
				curl_easy_setopt(request->Easy, opt, static_cast<long>(param.u.floatValue));
				break;
			case VAR_ISTRING:
			case VAR_STRING:
				curl_easy_setopt(request->Easy, opt, Plugin_SL_ConvertToString(param.u.stringValue));
				break;
			}
		}
	}

	void Ftp::Execute(AsyncTask* task)
	{
		auto request = task->GetData<FtpRequest>();
		int running = 0;

		do
		{
			CURLMcode mc = curl_multi_perform(request->Multi, &running);
			if (mc != CURLM_OK)
			{
				task->Error = curl_multi_strerror(mc);
				task->Status = AsyncStatus::Failure;
				Plugin_Printf("^1%s\n", task->Error.c_str());
				return;
			}
			if (task->IsCancelled())
			{
				task->Status = AsyncStatus::Cancelled;
				return;
			}
			if (running > 0)
				curl_multi_wait(request->Multi, nullptr, 0, 100, nullptr);
		} while (running > 0);

		int msgsleft;
		CURLMsg* msg;
		while ((msg = curl_multi_info_read(request->Multi, &msgsleft)))
		{
			if (msg->msg == CURLMSG_DONE && msg->data.result != CURLE_OK)
			{
				task->Error = curl_easy_strerror(msg->data.result);
				task->Status = AsyncStatus::Failure;
				Plugin_Printf("^1%s\n", task->Error.c_str());
			}
		}
		task->Status = AsyncStatus::Successful;
	}

	void Ftp::ExecuteGetFile(AsyncTask* task)
	{
		auto request = task->GetData<FtpRequest>();
		std::ofstream file(request->Filepath, std::ios::binary);
		int running = 0;

		if (!file.is_open())
		{
			task->Error = "Failed to open file for writing";
			task->Status = AsyncStatus::Failure;
			Plugin_Printf("^1%s\n", task->Error.c_str());
			return;
		}
		curl_easy_setopt(request->Easy, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEDATA, &file);

		do
		{
			CURLMcode mc = curl_multi_perform(request->Multi, &running);
			if (mc != CURLM_OK)
			{
				task->Error = curl_multi_strerror(mc);
				task->Status = AsyncStatus::Failure;
				file.close();
				Plugin_Printf("^1%s\n", task->Error.c_str());
				return;
			}
			if (task->IsCancelled())
			{
				task->Status = AsyncStatus::Cancelled;
				file.close();
				return;
			}
			if (running > 0)
				curl_multi_wait(request->Multi, nullptr, 0, 100, nullptr);
		} while (running > 0);
		file.close();

		int msgsleft;
		CURLMsg* msg;
		while ((msg = curl_multi_info_read(request->Multi, &msgsleft)))
		{
			if (msg->msg == CURLMSG_DONE && msg->data.result != CURLE_OK)
			{
				task->Error = curl_easy_strerror(msg->data.result);
				task->Status = AsyncStatus::Failure;
				Plugin_Printf("^1%s\n", task->Error.c_str());
			}
		}
		task->Status = AsyncStatus::Successful;
	}

	void Ftp::ExecutePostFile(AsyncTask* task)
	{
		auto request = task->GetData<FtpRequest>();
		std::ifstream file(request->Filepath, std::ios::binary);
		int running = 0;

		if (!file.is_open())
		{
			task->Error = "Failed to open file for reading";
			task->Status = AsyncStatus::Failure;
			Plugin_Printf("^1%s\n", task->Error.c_str());
			return;
		}
		curl_easy_setopt(request->Easy, CURLOPT_READFUNCTION, ReadCallback);
		curl_easy_setopt(request->Easy, CURLOPT_READDATA, &file);

		do
		{
			CURLMcode mc = curl_multi_perform(request->Multi, &running);
			if (mc != CURLM_OK)
			{
				task->Error = curl_multi_strerror(mc);
				task->Status = AsyncStatus::Failure;
				file.close();
				Plugin_Printf("^1%s\n", task->Error.c_str());
				return;
			}
			if (task->IsCancelled())
			{
				task->Status = AsyncStatus::Cancelled;
				file.close();
				return;
			}
			if (running > 0)
				curl_multi_wait(request->Multi, nullptr, 0, 100, nullptr);
		} while (running > 0);
		file.close();

		int msgsleft;
		CURLMsg* msg;
		while ((msg = curl_multi_info_read(request->Multi, &msgsleft)))
		{
			if (msg->msg == CURLMSG_DONE && msg->data.result != CURLE_OK)
			{
				task->Error = curl_easy_strerror(msg->data.result);
				task->Status = AsyncStatus::Failure;
				Plugin_Printf("^1%s\n", task->Error.c_str());
			}
		}
		task->Status = AsyncStatus::Successful;
	}
}
