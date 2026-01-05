#pragma once
#include "Base.hpp"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

namespace gsclib
{
	enum class AsyncStatus
	{
		Pending = 0,
		Running = 1,
		Successful = 2,
		Failure = -1,
		Cancelled = -2
	};

	struct AsyncTask
	{
		std::atomic<AsyncStatus> Status{ AsyncStatus::Pending };
		std::string Result;
		std::string Error;

		bool IsCancelled() const
		{
			return Status.load() == AsyncStatus::Cancelled;
		}

		void Cancel()
		{
			Status = AsyncStatus::Cancelled;
		}
	};

	class Async
	{
	public:
		static void Initialize(size_t threadCount = 4);
		static void Shutdown();
		static std::shared_ptr<AsyncTask> Submit(std::function<void(AsyncTask &)> work);

	private:
		static inline std::vector<std::thread> Workers;
		static inline std::queue<std::pair<std::shared_ptr<AsyncTask>, std::function<void(AsyncTask &)>>> Tasks;
		static inline std::mutex QueueMutex;
		static inline std::condition_variable Condition;
		static inline std::atomic<bool> Running{ false };

		static void WorkerThread();
	};
}
