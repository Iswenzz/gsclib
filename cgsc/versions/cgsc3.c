#include "cgsc3.h"

#include <assert.h>

#if CGSC_EQ(3)

struct scrVmGlob_t
{
	VariableValue eval_stack[2];
	const char *dialog_error_message;
	int loading;
	int starttime;
	unsigned int localVarsStack[2048];
};

qboolean Scr_IsInOpcodeMemory(const char *pos)
{
	return qfalse;
}
unsigned int __cdecl AllocThread(unsigned int self)
{
	return 0;
}
void VM_Execute(unsigned a, char const *b, unsigned c) { }
void Scr_AddFunc(const char *codePosValue) { }
void AddRefToObject(unsigned int id) { }
void RemoveRefToObject(unsigned int id) { }

__attribute__((unused)) scrVmPub_t gScrVmPub = { 0 };
__attribute__((unused)) struct scrVmGlob_t gScrVmGlob = { 0 };
__attribute__((unused)) scrVarPub_t gScrVarPub;

unsigned int Scr_GetObjectType(unsigned int id)
{
	assert((IGScrVarGlob[VARIABLELIST_PARENT_BEGIN + id].w.status & VAR_STAT_MASK) != VAR_STAT_FREE);
	return VAR_TYPE((&IGScrVarGlob[id + VARIABLELIST_PARENT_BEGIN]));
}

int GetArraySize(int id)
{
	VariableValueInternal *entryValue;
	assert(id != 0);

	entryValue = &IGScrVarGlob[id + VARIABLELIST_PARENT_BEGIN];
	assert(VAR_TYPE(entryValue) == VAR_ARRAY);
	return entryValue->u.o.u.size;
}

#endif
