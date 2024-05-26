// $Id: snprintf.c,v 1.9 2008/01/20 14:02:00 holger Exp $

/**
 * Copyright (c) 1995 Patrick Powell.
 *
 * This code is based on code written by Patrick Powell <papowell@astart.com>.
 * It may be used for any purpose as long as this notice remains intact on all
 * source code distributions.
 */

/**
 * Copyright (c) 2008 Holger Weiss.
 *
 * This version of the code is maintained by Holger Weiss <holger@jhweiss.de>.
 * My changes to the code may freely be used, modified and/or redistributed for
 * any purpose.  It would be nice if additions and fixes to this file (including
 * trivial code cleanups) would be sent back in order to let me include them in
 * the version available at <http://www.jhweiss.de/software/snprintf.html>.
 * However, this is not a requirement for using or redistributing (possibly
 * modified) versions of this file, nor is leaving this notice intact mandatory.
 */
#pragma once

#include <CGSC/cgsc.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <locale.h>
#include <stddef.h>
#include <stdint.h>

#ifndef ULONG_MAX
	#ifdef UINT_MAX
		#define ULONG_MAX UINT_MAX
	#else
		#define ULONG_MAX INT_MAX
	#endif
#endif

#ifdef ULLONG
	#undef ULLONG
#endif
#define ULLONG uint64_t
#ifndef ULLONG_MAX
	#define ULLONG_MAX ULONG_MAX
#endif

#ifdef UINTMAX_T
	#undef UINTMAX_T
#endif
#define UINTMAX_T uintmax_t
#ifndef UINTMAX_MAX
	#define UINTMAX_MAX ULLONG_MAX
#endif

#define LDOUBLE long double
#define LLONG int64_t
#define INTMAX_T intmax_t
#define UINTPTR_T uintptr_t
#define PTRDIFF_T ptrdiff_t

/**
 * We need an unsigned integer type corresponding to ptrdiff_t (cf. C99: 7.19.6.1, 7).  
 * However, we'll simply use PTRDIFF_T and convert it to an unsigned type if necessary. 
 * This should work just fine in practice.
 */
#ifndef UPTRDIFF_T
	#define UPTRDIFF_T PTRDIFF_T
#endif

/**
 * We need a signed integer type corresponding to size_t (cf. C99: 7.19.6.1, 7).
 * However, we'll simply use size_t and convert it to a signed type if
 * necessary. This should work just fine in practice.
 */
#ifndef SSIZE_T
	#define SSIZE_T size_t
#endif

#ifndef ERANGE
	#define ERANGE E2BIG
#endif

#ifndef EOVERFLOW
	#define EOVERFLOW ERANGE
#endif

/**
 * Buffer size to hold the octal string representation of UINT128_MAX without
 * nul-termination ("3777777777777777777777777777777777777777777").
 */
#ifdef MAX_CONVERT_LENGTH
	#undef MAX_CONVERT_LENGTH
#endif
#define MAX_CONVERT_LENGTH 43

// Format read states
#define PRINT_S_DEFAULT 0
#define PRINT_S_FLAGS 1
#define PRINT_S_WIDTH 2
#define PRINT_S_DOT 3
#define PRINT_S_PRECISION 4
#define PRINT_S_MOD 5
#define PRINT_S_CONV 6

// Format flags
#define PRINT_F_MINUS (1 << 0)
#define PRINT_F_PLUS (1 << 1)
#define PRINT_F_SPACE (1 << 2)
#define PRINT_F_NUM (1 << 3)
#define PRINT_F_ZERO (1 << 4)
#define PRINT_F_QUOTE (1 << 5)
#define PRINT_F_UP (1 << 6)
#define PRINT_F_UNSIGNED (1 << 7)
#define PRINT_F_TYPE_G (1 << 8)
#define PRINT_F_TYPE_E (1 << 9)

// Conversion flag
#define PRINT_C_CHAR 1
#define PRINT_C_SHORT 2
#define PRINT_C_LONG 3
#define PRINT_C_LLONG 4
#define PRINT_C_LDOUBLE 5
#define PRINT_C_SIZE 6
#define PRINT_C_PTRDIFF 7
#define PRINT_C_INTMAX 8

#ifndef MAX
	#define MAX(x, y) ((x >= y) ? x : y)
#endif
#ifndef CHARTOINT
	#define CHARTOINT(ch) (ch - '0')
#endif
#ifndef ISDIGIT
	#define ISDIGIT(ch) ('0' <= (unsigned char)ch && (unsigned char)ch <= '9')
#endif
#ifndef ISNAN
	#define ISNAN(x) (x != x)
#endif
#ifndef ISINF
	#define ISINF(x) (x != 0.0 && x + x == x)
#endif

#ifdef OUTCHAR
	#undef OUTCHAR
#endif
#define OUTCHAR(str, len, size, ch) \
	do                              \
	{                               \
		if (len + 1 < size)         \
			str[len] = ch;          \
		(len)++;                    \
	} while (/* CONSTCOND */ 0)

#ifndef errno
extern int errno;
#endif

/// <summary>
/// Format a string from GSC variables.
/// </summary>
/// <param name="str">The buffer string.</param>
/// <param name="size">The buffer size.</param>
/// <param name="format">The format string.</param>
/// <param name="args">The GSC variables array.</param>
/// <returns></returns>
int Scr_vsnprintf(char* str, size_t size, const char* format, VariableValueArray args);

/// <summary>
/// Format strings.
/// </summary>
/// <param name="str">The string buffer.</param>
/// <param name="len">The string position.</param>
/// <param name="size">The string size.</param>
/// <param name="value">The string value.</param>
/// <param name="width">The string width.</param>
/// <param name="precision">The string precision.</param>
/// <param name="flags">The string flags.</param>
void fmtstr(char* str, size_t* len, size_t size, const char* value, int width, int precision, int flags);

/// <summary>
/// Format ints.
/// </summary>
/// <param name="str">The string buffer.</param>
/// <param name="len">The string position.</param>
/// <param name="size">The string size.</param>
/// <param name="value">The int value.</param>
/// <param name="base">The int base format.</param>
/// <param name="width">The int width.</param>
/// <param name="precision">The int precision.</param>
/// <param name="flags">The int flags.</param>
void fmtint(char* str, size_t* len, size_t size, INTMAX_T value, int base, int width, int precision, int flags);

/// <summary>
/// Format floats.
/// </summary>
/// <param name="str">The string buffer.</param>
/// <param name="len">The string position.</param>
/// <param name="size">The string size.</param>
/// <param name="fvalue">The float value.</param>
/// <param name="width">The float width.</param>
/// <param name="precision">The float precision.</param>
/// <param name="flags">The float flags.</param>
/// <param name="overflow">The overflow out value.</param>
void fmtflt(char* str, size_t* len, size_t size, LDOUBLE fvalue, int width, int precision, int flags, int* overflow);

/// <summary>
/// Print the separators.
/// </summary>
/// <param name="str">The string buffer.</param>
/// <param name="len">The string position.</param>
/// <param name="size">The string size.</param>
void printsep(char* str, size_t* len, size_t size);

/// <summary>
/// Get number of separators.
/// </summary>
/// <param name="digits">The digit to get.</param>
/// <returns></returns>
int getnumsep(int digits);

/// <summary>
/// Get the exponent.
/// </summary>
/// <param name="value">The value.</param>
/// <returns></returns>
int getexponent(LDOUBLE value);

/// <summary>
/// Converts an integer to a specific base.
/// </summary>
/// <param name="value">The integer value.</param>
/// <param name="buf">The string buffer.</param>
/// <param name="size">The string size.</param>
/// <param name="base">The base to use.</param>
/// <param name="caps">Check caps letters.</param>
/// <returns></returns>
int convert(UINTMAX_T value, char* buf, size_t size, int base, int caps);

/// <summary>
/// Cast a long double to integer.
/// </summary>
/// <param name="value">The value to cast.</param>
/// <returns></returns>
UINTMAX_T cast(LDOUBLE value);

/// <summary>
/// Round x to the nearest integer.
/// </summary>
/// <param name="value">The value to round.</param>
/// <returns></returns>
UINTMAX_T myround(LDOUBLE value);

/// <summary>
/// The value of 10 raised to the power x.
/// </summary>
/// <param name="exponent">The exponent power.</param>
/// <returns></returns>
LDOUBLE mypow10(int exponent);
