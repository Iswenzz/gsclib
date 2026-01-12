#pragma once
#define PLUGIN

#ifndef PLUGIN_INCLUDES
	#include <pinc.h>
#endif

#ifdef PLUGIN
	#define Com_Printf Plugin_Printf
	#define Scr_Error Plugin_Scr_Error
	#define Scr_AddUndefined Plugin_Scr_AddUndefined
	#define Sys_GetCommonVersion Plugin_Sys_GetCommonVersion
#endif

#define CHECK_PARAMS(count, message)       \
	if (Plugin_Scr_GetNumParam() != count) \
	{                                      \
		Plugin_Scr_Error(message);         \
		return;                            \
	}

#define CHECK_UNSUPPORTED(condition)                                                                     \
	if (Plugin_CGSC_UnsupportedMessage(condition, "CGSC: This feature is unsupported in this version.")) \
	{                                                                                                    \
		Plugin_Scr_AddUndefined();                                                                       \
		return;                                                                                          \
	}

struct VariableStackBuffer
{
	const char *pos;
	uint16_t size;
	uint16_t bufLen;
	uint16_t localId;
	char time;
	char buf[1];
};

union VariableUnion
{
	int intValue;
	float floatValue;
	unsigned int stringValue;
	const float *vectorValue;
	const char *codePosValue;
	unsigned int pointerValue;
	struct VariableStackBuffer *stackValue;
	unsigned int entityOffset;
};

typedef struct
{
	union VariableUnion u;
	int type;
} VariableValue;

union ObjectInfo_u
{
	uint16_t size;
	uint16_t entnum;
	uint16_t nextEntId;
	uint16_t self;
};

struct ObjectInfo
{
	uint16_t refCount;
	union ObjectInfo_u u;
};

union VariableValueInternal_u
{
	uint16_t next;
	union VariableUnion u;
	struct ObjectInfo o;
};

union VariableValueInternal_w
{
	unsigned int status;
	unsigned int type;
	unsigned int name;
	unsigned int classnum;
	unsigned int notifyName;
	unsigned int waitTime;
	unsigned int parentLocalId;
};

union VariableValueInternal_v
{
	uint16_t next;
	uint16_t index;
};

union Variable_u
{
	uint16_t prev;
	uint16_t prevSibling;
};

struct Variable
{
	uint16_t id;
	union Variable_u u;
};

typedef struct
{
	struct Variable hash;
	union VariableValueInternal_u u;
	union VariableValueInternal_w w;
	union VariableValueInternal_v v;
	uint16_t nextSibling;
} VariableValueInternal;

enum $0E0E04F36A22A28F2C0A7A22DC12DAE9
{
	VAR_UNDEFINED = 0x0,
	VAR_BEGIN_REF = 0x1,
	VAR_POINTER = 0x1,
	VAR_STRING = 0x2,
	VAR_ISTRING = 0x3,
	VAR_VECTOR = 0x4,
	VAR_END_REF = 0x5,
	VAR_FLOAT = 0x5,
	VAR_INTEGER = 0x6,
	VAR_CODEPOS = 0x7,
	VAR_PRECODEPOS = 0x8,
	VAR_FUNCTION = 0x9,
	VAR_STACK = 0xA,
	VAR_ANIMATION = 0xB,
	VAR_DEVELOPER_CODEPOS = 0xC,
	VAR_INCLUDE_CODEPOS = 0xD,
	VAR_THREAD = 0xE,
	VAR_NOTIFY_THREAD = 0xF,
	VAR_TIME_THREAD = 0x10,
	VAR_CHILD_THREAD = 0x11,
	VAR_OBJECT = 0x12,
	VAR_DEAD_ENTITY = 0x13,
	VAR_ENTITY = 0x14,
	VAR_ARRAY = 0x15,
	VAR_DEAD_THREAD = 0x16,
	VAR_COUNT = 0x17,
	VAR_THREAD_LIST = 0x18,
	VAR_ENDON_LIST = 0x19
};

int Plugin_Scr_GetFunction(unsigned int paramnum);
