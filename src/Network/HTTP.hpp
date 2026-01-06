#pragma once
#include "Base.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <curl/curl.h>

namespace gsclib
{
	struct HttpRequest
	{
		CURL* Easy = nullptr;
		CURLM* Multi = nullptr;
		curl_slist* Headers = nullptr;
		std::string Response;
		std::string Filepath;
		std::string Data;
		std::vector<std::string> HeaderList;
		std::vector<std::pair<CURLoption, VariableValue>> Opts;

		HttpRequest();
		~HttpRequest();
	};

	class Http
	{
	public:
		static void Initialize();
		static void Free();
		static void Get();
		static void GetFile();
		static void Post();
		static void PostFile();
		static void GetResponse();
		static void AddHeader();
		static void AddOpt();
		static void HeaderCleanup();
		static void OptCleanup();

	private:
		static void ApplyHeaders(HttpRequest* request);
		static void ApplyOpts(HttpRequest* request);
		static void Execute(AsyncTask* task);
		static void ExecuteFileDownload(AsyncTask* task);
		static size_t WriteCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
		static size_t WriteFileCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
	};
}
