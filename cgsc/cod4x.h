#pragma once
#define COD4X

#ifndef PLUGIN_HANDLER_VERSION_MAJOR
	#include <plugin_declarations.h>
#endif

#define CHECK_UNSUPPORTED(condition)                                                              \
	if (CGSC_UnsupportedMessage(condition, "CGSC: This feature is unsupported in this version.")) \
	{                                                                                             \
		Scr_AddUndefined();                                                                       \
		return;                                                                                   \
	}

#include <q_shared.h>
#include <scr_vm.h>
#include <scr_vm_functions.h>
#include <version.h>

#undef ASSERT
