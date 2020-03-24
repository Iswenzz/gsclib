#pragma once
#include "../../dependencies/cgsc.h"

typedef struct
{
	uint32_t length;
	VariableValue **items;
} List;

void GScr_LIST_new();
void GScr_LIST_add();
void GScr_LIST_remove();
void GScr_LIST_insert();
void GScr_LIST_length();
void GScr_LIST_get();