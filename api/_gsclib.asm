%macro pexport 1
	SECTION .text
		%ifdef Win32
			EXPORT Plugin_%1
		%endif
		global Plugin_%1
		Plugin_%1: jmp dword [p%1]

	SECTION .rodata
		extern %1
		p%1 dd %1
%endmacro

pexport Scr_CreateArray
pexport Scr_FreeArray
pexport Scr_GetArray
pexport Scr_AddVariable
pexport Scr_AddPointerArray
pexport Scr_AddFunc
pexport Scr_ExecThreadResult
pexport Scr_GetThreadResult
pexport Scr_GetTop
pexport Scr_SelectParam
pexport Scr_GetArrayFlags
pexport Scr_GetObjectType
