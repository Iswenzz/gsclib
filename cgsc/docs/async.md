# Async

**CGSC** is using libuv for asynchronous operations, libuv is a cross-platform library for asynchronous I/O based on event loops. It was primarily developed for use in Node.js, but it is also used in other projects.

libuv provides a number of features that are useful for building scalable networked applications, including:

* An event loop, which allows you to register callbacks for various types of I/O events (e.g., reading from a socket, writing to a file) and schedule them to be executed asynchronously.
* A thread pool, which allows you to offload time-consuming tasks to a pool of worker threads, allowing the event loop to remain responsive.
* File system and network I/O functions, which are implemented in a platform-agnostic way and can be used to build portable applications.
* Other utility functions, such as timers, signals, and process management.

## Example

```c
void WorkerCallback(uv_work_t* req)
{
	// Get the async worker and the worker data
	async_worker* worker = (async_worker *)req->data;
	some_data_t* data = (some_data_t *)worker->data;

	// Or only get the data if needed.
	some_data_t* data = (some_data_t *)AsyncWorkerData(req);

	qboolean running = qfalse;
	do
	{
		// Do some work
		int error = some_polling_query(data->result, &running);

		// Error handling
		if (error)
		{
			AsyncWorkerDone(req, ASYNC_FAILURE);
			return;
		}
	}
	while (running && worker->status != ASYNC_CANCEL);

	AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
}

int main()
{
	async_handler *handler = AsyncInit();

	some_data_t *data = (some_data_t *)malloc(sizeof(some_data_t));
	data->foo = 1;
	data->bar = 2;

	async_worker* worker = AsyncWorker(handler, data, WorkerCallback);

	return AsyncLoopRun(handler->loop);
}
```

### ``AsyncInit()``
Initialize the async handler.
The async handler can be freed with AsyncShutdown().

```c
async_handler* handler = AsyncInit();
AsyncShutdown(handler);
```
<hr>

### ``AsyncLoopCreate()``
Create an async loop.
The loop can be freed with AsyncLoopFree().

```c
uv_loop_t* loop = AsyncLoopCreate();
AsyncLoopFree(loop);
```
<hr>

### ``AsyncLoopRun(uv_loop_t* loop)``
Run the async loop.

```c
AsyncLoopRun(loop);
```
<hr>

### ``AsyncLoopStop(uv_loop_t* loop)``
Stop the async loop.

```c
AsyncLoopStop(loop);
```
<hr>

### ``AsyncLoopFree(uv_loop_t* loop)``
Free and stop the async loop.

```c
AsyncLoopFree(loop);
```
<hr>

### ``AsyncWorker(async_handler* handler, void* data, uv_work_cb callback, uv_after_work_cb afterCallback)``
Create a new async worker.
handler - The async handler.
data - The data.
callback - The async loop.
afterCallback - The after callback.

```c
some_data_t *data = (some_data_t *)malloc(sizeof(some_data_t));
data->foo = 1;
data->bar = 2;

async_worker* worker = AsyncWorker(handler, data, WorkerCallback, NULL);
```
<hr>

### ``AsyncWorkerData(uv_work_t* req)``
Get the worker data from a uv_work_t.
req - The worker.

```c
some_data_t *data = (some_data_t *)AsyncWorkerData(req);
```
<hr>

### ``AsyncWorkerDone(uv_work_t* req, async_status status)``
Set the worker status and stop running.
req - The worker.
status - The worker done status.

```c
AsyncWorkerDone(req, ASYNC_SUCCESSFUL);
```
<hr>

### ``AsyncWorkerCancel(async_worker* worker)``
Cancel a worker.
req - The worker.

```c
AsyncWorkerCancel(worker);
```
<hr>

### ``AsyncWorkerFree(async_worker* worker)``
Free a worker.
req - The worker.

```c
AsyncWorkerFree(worker);
```
<hr>

### ``AsyncShutdown(async_handler* handler)``
Shutdown the async handler by canceling any pending requests and waiting for all threads to complete.
handler - The async handler.

```c
AsyncShutdown(handler);
```
<hr>
