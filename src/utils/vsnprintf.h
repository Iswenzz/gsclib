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

#ifndef UPTRDIFF_T
	#define UPTRDIFF_T PTRDIFF_T
#endif

#ifndef SSIZE_T
	#define SSIZE_T size_t
#endif

#ifndef ERANGE
	#define ERANGE E2BIG
#endif

#ifndef EOVERFLOW
	#define EOVERFLOW ERANGE
#endif

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
	} while (0)

#ifndef errno
extern int errno;
#endif

int Scr_vsnprintf(char* str, size_t size, const char* format, VariableValueArray args);

void fmtstr(char* str, size_t* len, size_t size, const char* value, int width, int precision, int flags);
void fmtint(char* str, size_t* len, size_t size, INTMAX_T value, int base, int width, int precision, int flags);
void fmtflt(char* str, size_t* len, size_t size, LDOUBLE fvalue, int width, int precision, int flags, int* overflow);
void printsep(char* str, size_t* len, size_t size);

int getnumsep(int digits);
int getexponent(LDOUBLE value);
int convert(UINTMAX_T value, char* buf, size_t size, int base, int caps);

UINTMAX_T cast(LDOUBLE value);
UINTMAX_T myround(LDOUBLE value);
LDOUBLE mypow10(int exponent);
