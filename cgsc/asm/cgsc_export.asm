; Plugin exports
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

; Rename function
%macro ralias 2
	SECTION .text
		%ifdef Win32
			EXPORT %1
		%endif
		global %1
		%1: jmp dword [p%2]

	SECTION .rodata
		extern %2
		p%2 dd %2
%endmacro

; Rename
ralias Plugin_Scr_GetFunction, Scr_GetFunc

; Plugin export
pexport Scr_ReturnResult
pexport Scr_AddFunc
pexport Scr_AddPointerArray
pexport Scr_AddVariable
pexport Scr_CallFunction
pexport Scr_CallMethod
pexport Scr_CreateArray
pexport Scr_ExecThreadResult
pexport Scr_FreeArray
pexport Scr_GetThreadReturn
pexport Scr_GetObjectType
pexport Scr_GetArray
pexport Scr_GetArrayFlags
pexport Scr_GetTop
pexport Sys_GetCommonVersion
pexport Scr_SelectParamOrDefault
pexport Scr_SelectParam
pexport Scr_SetParamGeneric
pexport CGSC_Version
pexport CGSC_Unsupported
pexport CGSC_UnsupportedMessage
pexport CGSC_SupportIndexedString
pexport AsyncInit
pexport AsyncLoopCreate
pexport AsyncLoopRun
pexport AsyncLoopStop
pexport AsyncLoopFree
pexport AsyncWorker
pexport AsyncWorkerData
pexport AsyncWorkerDone
pexport AsyncWorkerCancel
pexport AsyncWorkerFree
pexport AsyncShutdown
