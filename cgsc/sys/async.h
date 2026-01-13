#pragma once
#include "CGSC/cgsc.h"

#include <uv.h>

typedef enum
{
	ASYNC_NULL,
	ASYNC_PENDING,
	ASYNC_SUCCESSFUL,
	ASYNC_FAILURE,
	ASYNC_CANCEL
} async_status;

typedef struct async_worker_s
{
	async_status status;
	uv_work_t *req;
	uv_loop_t *loop;
	uv_thread_t thread;
	qboolean running;
	void *data;
	struct async_worker_s *next;
} async_worker;

typedef struct
{
	async_worker *workers;
	uv_loop_t *loop;
} async_handler;

EXPORT(async_handler *, AsyncInit());
EXPORT(uv_loop_t *, AsyncLoopCreate());
EXPORT(int, AsyncLoopRun(uv_loop_t *loop));
EXPORT(void, AsyncLoopStop(uv_loop_t *loop));
EXPORT(void, AsyncLoopFree(uv_loop_t *loop));
EXPORT(async_worker *,
	AsyncWorker(async_handler *handler, void *data, uv_work_cb callback, uv_after_work_cb afterCallback));
EXPORT(void *, AsyncWorkerData(uv_work_t *req));
EXPORT(void, AsyncWorkerDone(uv_work_t *req, async_status status));
EXPORT(void, AsyncWorkerCancel(async_worker *worker));
EXPORT(void, AsyncWorkerFree(async_worker *worker));
EXPORT(void, AsyncShutdown(async_handler *handler));
