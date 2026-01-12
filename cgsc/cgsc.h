#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _WIN32
	#define NOGDI
	#include <winsock2.h>
	#include <mswsock.h>
	#include <windows.h>
#endif

#ifdef COD4X18UPDATE
	#include "cod4x.h"
#else
	#include "plugin.h"
#endif

#ifdef PLUGIN_HANDLER_VERSION_MAJOR
	#define CGSC(version) PLUGIN_HANDLER_VERSION_MAJOR >= version
	#define CGSCH PLUGIN_HANDLER_VERSION_MAJOR
	#define CGSCL PLUGIN_HANDLER_VERSION_MINOR
	#define CGSC_EQ(version) CGSCH == version

	#if PLUGIN_HANDLER_VERSION_MAJOR >= 4
		#include "versions/cgsc4.h"
	#elif PLUGIN_HANDLER_VERSION_MAJOR >= 3
		#include "versions/cgsc3.h"
	#endif
#endif

#ifdef SYS_COMMONVERSION
	#define COD4X(version) SYS_COMMONVERSION
#endif

#ifdef __cplusplus
	#define CPP_EXTERN extern "C++"
#else
	#define CPP_EXTERN
#endif

#define EXPORT(type, definition) \
	type definition;             \
	type Plugin_##definition

#define CLASS_NUM_COUNT sizeof(gScrClassMap) / sizeof(gScrClassMap[0])
#define DEBUG_REFCOUNT_SIZE 65536
#define MAX_ARRAYINDEX 0x800000
#define MAX_LOCAL_CENTITIES 1536
#define OBJECT_STACK 0x18001u
#define SL_MAX_STRING_INDEX 0x10000
#define SCR_GET_ENTITY_FROM_ENTCLIENT(entcl) (entcl & UNK_ENTNUM_MASK)
#define UNK_ENTNUM_MASK 0x3FFF

#define VAR_ARRAYINDEXSTART 0x800000
#define VAR_STAT_MASK 0x60
#define VAR_STAT_FREE 0
#define VAR_STAT_MOVABLE 32
#define VAR_STAT_HEAD 64
#define VAR_STAT_EXTERNAL 96
#define VAR_MASK 0x1F
#define VAR_NAME_HIGH_MASK 0xFFFFFF00
#define VAR_NAME_BITS 8
#define VAR_TYPE(var) (var->w.type & VAR_MASK)

#define VARIABLELIST_CHILD_BEGIN 0x8002
#define VARIABLELIST_PARENT_BEGIN 0x1
#define VARIABLELIST_CHILD_SIZE 0xFFFE
#define VARIABLELIST_PARENT_SIZE 0x8000

#define IsObject(var) ((var->w.type & VAR_MASK) >= VAR_THREAD)
#define IsObjectVal(var) ((var->type & VAR_MASK) >= VAR_THREAD)

	// clang-format off
enum GSCTypeFlag
{
	FLAG_UNDEFINED = 1,
	FLAG_BEGIN_REF = 2,
	FLAG_POINTER = 4,
	FLAG_STRING = 8,
	FLAG_ISTRING = 16,
	FLAG_VECTOR = 32,
	FLAG_END_REF = 64,
	FLAG_FLOAT = 128,
	FLAG_INTEGER = 256,
	FLAG_CODEPOS = 512,
	FLAG_PRECODEPOS = 1024,
	FLAG_FUNCTION = 2048,
	FLAG_STACK = 4096,
	FLAG_ANIMATION = 8192,
	FLAG_DEVELOPER_CODEPOS = 16384,
	FLAG_INCLUDE_CODEPOS = 32768,
	FLAG_THREAD = 65536,
	FLAG_NOTIFY_THREAD = 131072,
	FLAG_TIME_THREAD = 262144,
	FLAG_CHILD_THREAD = 524288,
	FLAG_OBJECT = 1048576,
	FLAG_DEAD_ENTITY = 2097152,
	FLAG_ENTITY = 4194304,
	FLAG_ARRAY = 8388608,
	FLAG_DEAD_THREAD = 16777216,
	FLAG_COUNT = 33554432,
	FLAG_THREAD_LIST = 67108864,
	FLAG_ENDON_LIST = 134217728
};

struct scrStringDebugGlob_t
{
	volatile int refCount[DEBUG_REFCOUNT_SIZE];
	volatile int totalRefCount;
	int ignoreLeaks;
};

struct __attribute__((aligned(64))) scrVarGlob_t
{
	VariableValueInternal* variableList;
};

typedef struct
{
	uint32_t length;
	VariableValue* items;
} VariableValueArray;
	// clang-format on

#include "extensions/functions.h"
#include "extensions/variables.h"
#include "sys/async.h"
#include "sys/compatibility.h"
#include "utils/utils.h"

#ifdef __cplusplus
}
#endif
