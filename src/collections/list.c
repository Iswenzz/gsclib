#include "../../dependencies/cgsc.h"
#include <stdlib.h>

typedef struct
{
	uint32_t size;
	VariableValue **array;
} List;

void LIST_new()
{
	if (Plugin_Scr_GetNumParam() != 0)
    {
		Plugin_Scr_Error("Usage: ListNew()");
		return;
    }
	List *list = (List *)malloc(sizeof(List));
	list->array = (VariableValue **)malloc(sizeof(VariableValue *));
	list->size = 0;
	Plugin_Scr_AddInt((uint32_t)list);
}

void LIST_add()
{
	if (Plugin_Scr_GetNumParam() != 2)
    {
		Plugin_Scr_Error("Usage: ListAdd(<list>, <item>)");
		return;
    }
	const uint32_t list_addr = Plugin_Scr_GetInt(0);
	VariableValue *item = Plugin_Scr_SelectParam(1);

	List *list = (List *)list_addr;
	list->size++;
	list->array = (VariableValue **)realloc(list->array, list->size * sizeof(VariableValue *));
	list->array[list->size - 1] = Plugin_Scr_AllocVariable(item);
}

void LIST_get()
{
    if (Plugin_Scr_GetNumParam() != 2)
    {
        Plugin_Scr_Error("Usage: ListGet(<list>, <index>)");
        return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);
    const int index = Plugin_Scr_GetInt(1);

    List *list = (List *)list_addr;

    if(list->size < index) Plugin_Scr_AddUndefined();
    else Plugin_Scr_AddVariable(list->array[index]);
}

void LIST_length()
{
    if (Plugin_Scr_GetNumParam() != 1)
    {
        Plugin_Scr_Error("Usage: ListGet(<list>)");
        return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);

    List *list = (List *)list_addr;
    Plugin_Scr_AddInt(list->size);
}

void LIST_insert()
{
    if (Plugin_Scr_GetNumParam() != 3)
    {
        Plugin_Scr_Error("Usage: ListGet(<list>, <item>, <index>)");
        return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);
    VariableValue *item = Plugin_Scr_SelectParam(1);
    const int index = Plugin_Scr_GetInt(2);

    List *list = (List *)list_addr;
    List *newlist = (List *)malloc((list->size + 1) * sizeof(VariableValue *));
    for(int i = 0; i<list->size; i++)
    {
        if(i < index)
            newlist->array[i] = Plugin_Scr_AllocVariable(list->array[i]);
        else if (i == index)
            newlist->array[i] = Plugin_Scr_AllocVariable(item);
        else if (i > index)
            newlist->array[i+1] = Plugin_Scr_AllocVariable(list->array[i]);
    }
}

void LIST_remove()
{
    if (Plugin_Scr_GetNumParam() != 2)
    {
            Plugin_Scr_Error("Usage: ListGet(<list>, <item>)");
            return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);
    VariableValue *item = Plugin_Scr_SelectParam(1);

    List *list = (List *)list_addr;
    for(int i=0; i<list->size; i++)
    {
        if(list->array[i] == item)
        {
            free(list->array[i]);
            list->array[i] = (void *)0;
            list->size--;
        }
    }
}
