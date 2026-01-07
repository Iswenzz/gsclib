#pragma once
#include "Base.hpp"

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <curl/curl.h>

namespace gsclib
{
	struct FtpConnection
	{
		CURL* Easy = nullptr;
		CURLM* Multi = nullptr;
		std::string Url;
		std::string Password;
		unsigned short Port = 21;

		FtpConnection();
		~FtpConnection();
	};

	struct FtpRequest
	{
		CURL* Easy = nullptr;
		CURLM* Multi = nullptr;
		curl_slist* Headers = nullptr;
		std::string Filepath;
		std::string Response;
		std::vector<std::string> HeaderList;
		std::vector<std::pair<CURLoption, VariableValue>> Opts;

		FtpRequest();
		~FtpRequest();
	};

	class Ftp
	{
	public:
		static void Initialize();
		static void Free();
		static void Connect();
		static void SftpConnect();
		static void Close();
		static void Shell();
		static void PostFile();
		static void GetFile();
		static void AddHeader();
		static void AddOpt();
		static void HeaderCleanup();
		static void OptCleanup();

	private:
		static inline std::unique_ptr<FtpConnection> Connection;

		static bool DoConnect(const std::string& protocol, const std::string& hostname, const std::string& username,
			const std::string& password, unsigned short port);
		static void ApplyHeaders(FtpRequest* request, CURLoption headerType);
		static void ApplyOpts(FtpRequest* request);
		static void Execute(AsyncTask* task);
		static void ExecuteGetFile(AsyncTask* task);
		static void ExecutePostFile(AsyncTask* task);
		static size_t WriteCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
		static size_t ReadCallback(void* ptr, size_t size, size_t nmemb, void* userdata);
	};
}
