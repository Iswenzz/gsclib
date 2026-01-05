#include "Async.hpp"

namespace gsclib
{
	void Async::Initialize(size_t threadCount)
	{
		if (Running)
			return;

		Running = true;
		Workers.reserve(threadCount);

		for (size_t i = 0; i < threadCount; i++)
			Workers.emplace_back(&Async::WorkerThread);
	}

	void Async::Shutdown()
	{
		if (!Running)
			return;

		Running = false;
		Condition.notify_all();

		for (auto &worker : Workers)
		{
			if (worker.joinable())
				worker.join();
		}
		Workers.clear();

		std::scoped_lock lock(QueueMutex);
		while (!Tasks.empty())
			Tasks.pop();
	}

	std::shared_ptr<AsyncTask> Async::Submit(std::function<void(AsyncTask &)> work)
	{
		auto task = std::make_shared<AsyncTask>();
		{
			std::scoped_lock lock(QueueMutex);
			Tasks.push({ task, std::move(work) });
		}
		Condition.notify_one();
		return task;
	}

	void Async::WorkerThread()
	{
		while (Running)
		{
			std::pair<std::shared_ptr<AsyncTask>, std::function<void(AsyncTask &)>> taskPair;
			{
				std::unique_lock lock(QueueMutex);
				Condition.wait(lock, [] { return !Tasks.empty() || !Running; });

				if (!Running && Tasks.empty())
					return;

				taskPair = std::move(Tasks.front());
				Tasks.pop();
			}
			auto &task = taskPair.first;
			auto &work = taskPair.second;
			task->Status = AsyncStatus::Running;

			try
			{
				work(*task);
				if (task->Status == AsyncStatus::Running)
					task->Status = AsyncStatus::Successful;
			}
			catch (const std::exception &e)
			{
				task->Error = e.what();
				task->Status = AsyncStatus::Failure;
			}
		}
	}
}
