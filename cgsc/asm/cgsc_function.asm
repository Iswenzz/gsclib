; Imports
    extern Sys_Milliseconds
    extern Scr_IsInOpcodeMemory
    extern AddRefToObject
    extern AllocThread
    extern VM_Execute
    extern RemoveRefToValue
    extern gScrVarPub
    extern gScrVmGlob
    extern gScrVmPub

; Exports
    global Scr_ExecThreadResult

SECTION .text

; Scr_ExecThreadResult(int threadId, unsigned int argsCount)
Scr_ExecThreadResult:
	push ebp
	mov ebp, esp
	push esi
	push ebx
	sub esp, 0x10
	mov esi, gScrVarPub
	mov ebx, [esi+0x48]
	add ebx, [ebp+0x8]
	mov eax, [gScrVmPub+0x8]
	test eax, eax
	jnz Scr_ExecThreadResult_10
	call Sys_Milliseconds
	mov [gScrVmGlob+0x18], eax
Scr_ExecThreadResult_10:
	mov [esp], ebx
	call Scr_IsInOpcodeMemory
	mov eax, [esi+0x20]
	mov [esp], eax
	call AddRefToObject
	mov eax, [esi+0x20]
	mov [esp], eax
	call AllocThread
	mov ecx, [ebp+0xc]
	mov edx, ebx
	call VM_Execute
	mov ebx, eax
	mov edx, [gScrVmPub+0x10]
	mov eax, [edx]
	mov [esp+0x4], eax
	mov eax, [edx+0x4]
	mov [esp], eax
	call RemoveRefToValue
	mov eax, [gScrVmPub+0x10]
	sub dword [gScrVmPub+0x10], 0x8
	sub dword [gScrVmPub+0x18], 0x1
	movzx ebx, bx
	mov eax, ebx
	add esp, 0x10
	pop ebx
	pop esi
	pop ebp
	ret
	add [eax], al
