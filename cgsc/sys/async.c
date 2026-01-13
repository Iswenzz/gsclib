#include "async.h"

async_handler* AsyncInit()
{
	async_handler* handler = (async_handler*)malloc(sizeof(async_handler));
	handler->workers = (async_worker*)calloc(1, sizeof(async_worker));
	handler->loop = uv_default_loop();
	return handler;
}

uv_loop_t* AsyncLoopCreate()
{
	uv_loop_t* loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
	uv_loop_init(loop);
	return loop;
}

int AsyncLoopRun(uv_loop_t* loop)
{
	return uv_run(loop, UV_RUN_DEFAULT);
}

void AsyncLoopStop(uv_loop_t* loop)
{
	if (!loop || !uv_loop_alive(loop))
		return;

	uv_stop(loop);
}

void AsyncLoopFree(uv_loop_t* loop)
{
	if (!loop)
		return;
	AsyncLoopStop(loop);
	uv_loop_close(loop);
}

async_worker* AsyncWorker(async_handler* handler, void* data, uv_work_cb callback, uv_after_work_cb afterCallback)
{
	if (!handler)
		return NULL;

	uv_work_t* req = (uv_work_t*)malloc(sizeof(uv_work_t));
	async_worker* worker = (async_worker*)malloc(sizeof(async_worker));

	worker->status = ASYNC_PENDING;
	worker->req = req;
	worker->loop = handler->loop;
	worker->thread = 0;
	worker->data = data;
	worker->running = qtrue;
	worker->next = handler->workers->next;

	handler->workers->next = worker;
	req->data = worker;

	uv_queue_work(worker->loop, req, callback, afterCallback);

	return worker;
}

void* AsyncWorkerData(uv_work_t* req)
{
	async_worker* worker = (async_worker*)req->data;
	return worker->data;
}

void AsyncWorkerDone(uv_work_t* req, async_status status)
{
	async_worker* worker = (async_worker*)req->data;
	worker->status = status;
	worker->running = qfalse;
}

void AsyncWorkerCancel(async_worker* worker)
{
	if (!worker)
		return;
	worker->status = ASYNC_CANCEL;
}

void AsyncWorkerFree(async_worker* worker)
{
	if (!worker)
		return;
	if (worker->req)
	{
		free(worker->req);
		worker->req = NULL;
	}
}

void AsyncShutdown(async_handler* handler)
{
	if (!handler)
		return;

	async_worker* worker = handler->workers->next;
	while (worker)
	{
		AsyncLoopStop(worker->loop);
		AsyncWorkerCancel(worker);
		worker = worker->next;
	}

	worker = handler->workers->next;
	while (worker)
	{
		while (worker->running)
			uv_sleep(50);

		async_worker* prev = worker;
		worker = worker->next;
		free(prev);
	}
	if (handler->workers)
		free(handler->workers);
	free(handler);
	handler = NULL;
}
