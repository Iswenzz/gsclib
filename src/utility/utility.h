#pragma once
#include "../../dependencies/cgsc.h"

void ComPrintf();

uint32_t GetFlagsFromGSCArray(VariableValue **array, int array_size);
qboolean HasFlag(int var, int flag);
qboolean IsFlag(int var, int flag);
