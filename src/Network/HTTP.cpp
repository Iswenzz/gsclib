#include "Http.hpp"

namespace gsclib
{
	HttpRequest::HttpRequest()
	{
		Easy = curl_easy_init();
		Multi = curl_multi_init();

		if (Easy && Multi)
			curl_multi_add_handle(Multi, Easy);
	}

	HttpRequest::~HttpRequest()
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

	size_t Http::WriteCallback(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		auto* response = static_cast<std::string*>(userdata);
		size_t totalSize = size * nmemb;
		response->append(static_cast<char*>(ptr), totalSize);
		return totalSize;
	}

	size_t Http::WriteFileCallback(void* ptr, size_t size, size_t nmemb, void* userdata)
	{
		auto* file = static_cast<std::ofstream*>(userdata);
		size_t totalSize = size * nmemb;
		file->write(static_cast<char*>(ptr), totalSize);
		return file->good() ? totalSize : 0;
	}

	void Http::Initialize()
	{
		CHECK_PARAMS(0, "Usage: HTTP_Init()\n");

		auto* request = new HttpRequest();
		Working = true;
		Plugin_Scr_AddInt(reinterpret_cast<int>(request));
	}

	void Http::Free()
	{
		CHECK_PARAMS(1, "Usage: HTTP_Free(<request>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		if (request->Task && request->Task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("HTTP request is running.\n");
			return;
		}
		delete request;
		Working = false;
		Plugin_Scr_AddBool(qtrue);
	}

	void Http::Get()
	{
		CHECK_PARAMS(2, "Usage: HTTP_Get(<request>, <url>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		if (request->Task && request->Task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("HTTP request is running.\n");
			return;
		}
		const char* url = Plugin_Scr_GetString(1);
		request->Response.clear();

		ApplyHeaders(request);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url);
		curl_easy_setopt(request->Easy, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(request->Easy, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEDATA, &request->Response);
		ApplyOpts(request);

		request->Task = Async::Submit([request](AsyncTask& task) { Execute(request, task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Http::GetFile()
	{
		CHECK_PARAMS(3, "Usage: HTTP_GetFile(<request>, <filepath>, <url>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		if (request->Task && request->Task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("HTTP request is running.\n");
			return;
		}
		request->Filepath = Plugin_Scr_GetString(1);
		const char* url = Plugin_Scr_GetString(2);

		ApplyHeaders(request);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url);
		curl_easy_setopt(request->Easy, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(request->Easy, CURLOPT_NOPROGRESS, 1L);
		ApplyOpts(request);

		request->Task = Async::Submit([request](AsyncTask& task) { ExecuteFileDownload(request, task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Http::Post()
	{
		CHECK_PARAMS(3, "Usage: HTTP_Post(<request>, <data>, <url>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		if (request->Task && request->Task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("HTTP request is running.\n");
			return;
		}
		request->PostData = Plugin_Scr_GetString(1);
		const char* url = Plugin_Scr_GetString(2);
		request->Response.clear();

		ApplyHeaders(request);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url);
		curl_easy_setopt(request->Easy, CURLOPT_POSTFIELDS, request->PostData.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(request->Easy, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEDATA, &request->Response);
		ApplyOpts(request);

		request->Task = Async::Submit([request](AsyncTask& task) { Execute(request, task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Http::PostFile()
	{
		CHECK_PARAMS(3, "Usage: HTTP_PostFile(<request>, <filepath>, <url>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		if (request->Task && request->Task->Status == AsyncStatus::Running)
		{
			Plugin_Scr_Error("HTTP request is running.\n");
			return;
		}
		const char* filepath = Plugin_Scr_GetString(1);
		const char* url = Plugin_Scr_GetString(2);

		std::ifstream file(filepath, std::ios::binary | std::ios::ate);
		if (!file.is_open())
		{
			Plugin_Printf("File not found.\n");
			Plugin_Scr_AddBool(qfalse);
			return;
		}
		auto size = file.tellg();
		file.seekg(0, std::ios::beg);

		request->PostData.resize(static_cast<size_t>(size));
		file.read(request->PostData.data(), size);
		file.close();

		request->Response.clear();

		ApplyHeaders(request);
		curl_easy_setopt(request->Easy, CURLOPT_URL, url);
		curl_easy_setopt(request->Easy, CURLOPT_POSTFIELDSIZE, static_cast<long>(size));
		curl_easy_setopt(request->Easy, CURLOPT_POSTFIELDS, request->PostData.c_str());
		curl_easy_setopt(request->Easy, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(request->Easy, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEDATA, &request->Response);
		ApplyOpts(request);

		request->Task = Async::Submit([request](AsyncTask& task) { Execute(request, task); });

		Plugin_Scr_AddBool(qtrue);
	}

	void Http::GetResponse()
	{
		CHECK_PARAMS(1, "Usage: HTTP_Response(<request>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		Plugin_Scr_AddString(request->Response.c_str());
	}

	void Http::AddHeader()
	{
		CHECK_PARAMS(2, "Usage: HTTP_AddHeader(<request>, <header>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		request->HeaderList.push_back(Plugin_Scr_GetString(1));
	}

	void Http::AddOpt()
	{
		CHECK_PARAMS(3, "Usage: HTTP_AddOpt(<request>, <opt>, <value>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		auto opt = static_cast<CURLoption>(Plugin_Scr_GetInt(1));
		VariableValue param = *Plugin_Scr_SelectParam(2);
		request->Opts.push_back({ opt, param });
	}

	void Http::HeaderCleanup()
	{
		CHECK_PARAMS(1, "Usage: HTTP_HeaderCleanup(<request>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		request->HeaderList.clear();
		if (request->Headers)
		{
			curl_slist_free_all(request->Headers);
			request->Headers = nullptr;
		}
	}

	void Http::OptCleanup()
	{
		CHECK_PARAMS(1, "Usage: HTTP_OptCleanup(<request>)\n");

		auto* request = reinterpret_cast<HttpRequest*>(Plugin_Scr_GetInt(0));
		if (!request)
		{
			Plugin_Scr_Error("HTTP request not found.\n");
			return;
		}
		request->Opts.clear();
	}

	void Http::ApplyHeaders(HttpRequest* request)
	{
		if (!request || request->HeaderList.empty())
			return;

		for (const auto& header : request->HeaderList)
			request->Headers = curl_slist_append(request->Headers, header.c_str());

		curl_easy_setopt(request->Easy, CURLOPT_HTTPHEADER, request->Headers);
	}

	void Http::ApplyOpts(HttpRequest* request)
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

	void Http::Execute(HttpRequest* request, AsyncTask& task)
	{
		int running = 0;

		do
		{
			CURLMcode mc = curl_multi_perform(request->Multi, &running);
			if (mc != CURLM_OK)
			{
				task.Error = curl_multi_strerror(mc);
				task.Status = AsyncStatus::Failure;
				return;
			}
			if (task.IsCancelled())
			{
				task.Status = AsyncStatus::Cancelled;
				return;
			}
			if (running > 0)
				curl_multi_wait(request->Multi, nullptr, 0, 100, nullptr);
		} while (running > 0);

		task.Status = AsyncStatus::Successful;
	}

	void Http::ExecuteFileDownload(HttpRequest* request, AsyncTask& task)
	{
		std::ofstream file(request->Filepath, std::ios::binary);

		if (!file.is_open())
		{
			task.Error = "Failed to open file for writing";
			task.Status = AsyncStatus::Failure;
			return;
		}
		curl_easy_setopt(request->Easy, CURLOPT_WRITEFUNCTION, WriteFileCallback);
		curl_easy_setopt(request->Easy, CURLOPT_WRITEDATA, &file);
		int running = 0;

		do
		{
			CURLMcode mc = curl_multi_perform(request->Multi, &running);
			if (mc != CURLM_OK)
			{
				task.Error = curl_multi_strerror(mc);
				task.Status = AsyncStatus::Failure;
				file.close();
				return;
			}
			if (task.IsCancelled())
			{
				task.Status = AsyncStatus::Cancelled;
				file.close();
				return;
			}
			if (running > 0)
				curl_multi_wait(request->Multi, nullptr, 0, 100, nullptr);
		} while (running > 0);

		file.close();
		task.Status = AsyncStatus::Successful;
	}
}
