#include "list.h"
#include <stdlib.h>

void GScr_LIST_new()
{
	if (Plugin_Scr_GetNumParam() != 0)
    {
		Plugin_Scr_Error("Usage: ListNew()");
		return;
    }
	List *list = (List *)malloc(sizeof(List));
	list->items = (VariableValue **)malloc(sizeof(VariableValue *));
	list->length = 0;
	Plugin_Scr_AddInt((uint32_t)list);
}

void GScr_LIST_add()
{
	if (Plugin_Scr_GetNumParam() != 2)
    {
		Plugin_Scr_Error("Usage: ListAdd(<list>, <item>)");
		return;
    }
	const uint32_t list_addr = Plugin_Scr_GetInt(0);
	VariableValue *item = Plugin_Scr_SelectParam(1);

	List *list = (List *)list_addr;
	list->length++;
	list->items = (VariableValue **)realloc(list->items, list->length * sizeof(VariableValue *));
	list->items[list->length - 1] = Plugin_Scr_AllocVariable(item);
}

void GScr_LIST_get()
{
    if (Plugin_Scr_GetNumParam() != 2)
    {
        Plugin_Scr_Error("Usage: ListGet(<list>, <index>)");
        return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);
    const int index = Plugin_Scr_GetInt(1);

    List *list = (List *)list_addr;

    if(list->length < index) Plugin_Scr_AddUndefined();
    else Plugin_Scr_AddVariable(list->items[index]);
}

void GScr_LIST_length()
{
    if (Plugin_Scr_GetNumParam() != 1)
    {
        Plugin_Scr_Error("Usage: ListGet(<list>)");
        return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);

    List *list = (List *)list_addr;
    Plugin_Scr_AddInt(list->length);
}

void GScr_LIST_insert()
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
    List *newlist = (List *)malloc((list->length + 1) * sizeof(VariableValue *));
    for(int i = 0; i<list->length; i++)
    {
        if(i < index)
            newlist->items[i] = Plugin_Scr_AllocVariable(list->items[i]);
        else if (i == index)
            newlist->items[i] = Plugin_Scr_AllocVariable(item);
        else if (i > index)
            newlist->items[i+1] = Plugin_Scr_AllocVariable(list->items[i]);
    }
}

void GScr_LIST_remove()
{
    if (Plugin_Scr_GetNumParam() != 2)
    {
            Plugin_Scr_Error("Usage: ListGet(<list>, <item>)");
            return;
    }
    const uint32_t list_addr = Plugin_Scr_GetInt(0);
    VariableValue *item = Plugin_Scr_SelectParam(1);

    List *list = (List *)list_addr;
    for(int i=0; i<list->length; i++)
    {
        if(list->items[i] == item)
        {
            free(list->items[i]);
            list->items[i] = (void *)0;
            list->length--;
        }
    }
}
