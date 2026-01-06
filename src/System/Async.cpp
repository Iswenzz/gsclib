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

		for (auto& worker : Workers)
		{
			if (worker.joinable())
				worker.join();
		}
		Workers.clear();

		std::scoped_lock lock(QueueMutex);
		while (!Tasks.empty())
			Tasks.pop();

		ActiveTasks.clear();
	}

	std::shared_ptr<AsyncTask> Async::Create(void* data)
	{
		auto task = std::make_shared<AsyncTask>();
		task->Data = data;
		task->Status = AsyncStatus::Pending;
		{
			std::scoped_lock lock(QueueMutex);
			ActiveTasks.push_back(task);
		}
		return task;
	}

	void Async::Submit(std::function<void()> work)
	{
		{
			std::scoped_lock lock(QueueMutex);
			Tasks.push(std::move(work));
		}
		Condition.notify_one();
	}

	void Async::WorkerThread()
	{
		while (Running)
		{
			std::function<void()> work;
			{
				std::unique_lock lock(QueueMutex);
				Condition.wait(lock, [] { return !Tasks.empty() || !Running; });

				if (!Running && Tasks.empty())
					return;

				work = std::move(Tasks.front());
				Tasks.pop();
			}
			try
			{
				work();
			}
			catch (const std::exception& e)
			{
				Plugin_Printf("Async exception: %s\n", e.what());
			}
		}
	}
}
