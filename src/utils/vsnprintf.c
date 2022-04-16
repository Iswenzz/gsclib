#include "vsnprintf.h"

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int Scr_vsnprintf(char* str, size_t size, const char* format, VariableValue* args)
{
	LDOUBLE fvalue;
	INTMAX_T value;
	unsigned char cvalue;
	const char* strvalue;
	size_t len = 0;
	int overflow = 0;
	int base = 0;
	int cflags = 0;
	int flags = 0;
	int width = 0;
	int precision = -1;
	int state = PRINT_S_DEFAULT;
	char ch = *format++;

	/**
	 * C99 says: "If `n' is zero, nothing is written, and `s' may be a null
	 * pointer." (7.19.6.5, 2)  We're forgiving and allow a NULL pointer
	 * even if a size larger than zero was specified.  At least NetBSD's
	 * snprintf(3) does the same, as well as other versions of this file.
	 * (Though some of these versions will write to a non-NULL buffer even
	 * if a size of zero was specified, which violates the standard.)
	 */
	if (str == NULL && size != 0)
		size = 0;

	while (ch != '\0')
	{
		switch (state)
		{
		case PRINT_S_DEFAULT:
			if (ch == '%')
				state = PRINT_S_FLAGS;
			else
				OUTCHAR(str, len, size, ch);
			ch = *format++;
			break;
		case PRINT_S_FLAGS:
			switch (ch) 
			{
			case '-':
				flags |= PRINT_F_MINUS;
				ch = *format++;
				break;
			case '+':
				flags |= PRINT_F_PLUS;
				ch = *format++;
				break;
			case ' ':
				flags |= PRINT_F_SPACE;
				ch = *format++;
				break;
			case '#':
				flags |= PRINT_F_NUM;
				ch = *format++;
				break;
			case '0':
				flags |= PRINT_F_ZERO;
				ch = *format++;
				break;
			case '\'':
				flags |= PRINT_F_QUOTE;
				ch = *format++;
				break;
			default:
				state = PRINT_S_WIDTH;
				break;
			}
			break;
		case PRINT_S_WIDTH:
			if (ISDIGIT(ch)) 
			{
				ch = CHARTOINT(ch);
				if (width > (INT_MAX - ch) / 10) 
				{
					overflow = 1;
					goto out;
				}
				width = 10 * width + ch;
				ch = *format++;
			}
			else if (ch == '*') 
			{
				/**
				 * C99 says: "A negative field width argument is
				 * taken as a `-' flag followed by a positive
				 * field width." (7.19.6.1, 5)
				 */
				if ((width = (*(args++)).u.intValue) < 0) 
				{
					flags |= PRINT_F_MINUS;
					width = -width;
				}
				ch = *format++;
				state = PRINT_S_DOT;
			}
			else
				state = PRINT_S_DOT;
			break;
		case PRINT_S_DOT:
			if (ch == '.') 
			{
				state = PRINT_S_PRECISION;
				ch = *format++;
			}
			else
				state = PRINT_S_MOD;
			break;
		case PRINT_S_PRECISION:
			if (precision == -1)
				precision = 0;
			if (ISDIGIT(ch)) 
			{
				ch = CHARTOINT(ch);
				if (precision > (INT_MAX - ch) / 10) 
				{
					overflow = 1;
					goto out;
				}
				precision = 10 * precision + ch;
				ch = *format++;
			}
			else if (ch == '*') 
			{
				/**
				 * C99 says: "A negative precision argument is
				 * taken as if the precision were omitted."
				 * (7.19.6.1, 5)
				 */
				if ((precision = (*(args++)).u.intValue) < 0)
					precision = -1;
				ch = *format++;
				state = PRINT_S_MOD;
			}
			else
				state = PRINT_S_MOD;
			break;
		case PRINT_S_MOD:
			switch (ch) 
			{
			case 'h':
				ch = *format++;
				if (ch == 'h') 
				{
					ch = *format++;
					cflags = PRINT_C_CHAR;
				}
				else
					cflags = PRINT_C_SHORT;
				break;
			case 'l':
				ch = *format++;
				if (ch == 'l') 
				{
					ch = *format++;
					cflags = PRINT_C_LLONG;
				}
				else
					cflags = PRINT_C_LONG;
				break;
			case 'L':
				cflags = PRINT_C_LDOUBLE;
				ch = *format++;
				break;
			case 'j':
				cflags = PRINT_C_INTMAX;
				ch = *format++;
				break;
			case 't':
				cflags = PRINT_C_PTRDIFF;
				ch = *format++;
				break;
			case 'z':
				cflags = PRINT_C_SIZE;
				ch = *format++;
				break;
			}
			state = PRINT_S_CONV;
			break;
		case PRINT_S_CONV:
			switch (ch) 
			{
			case 'd':
			case 'i':
				switch (cflags) 
				{
				case PRINT_C_CHAR:
					value = Plugin_SL_ConvertToString((*(args++)).u.stringValue)[0];
					break;
				case PRINT_C_SHORT:
				case PRINT_C_LONG:
				case PRINT_C_LLONG:
				case PRINT_C_SIZE:
				case PRINT_C_INTMAX:
				case PRINT_C_PTRDIFF:
				default:
					value = (*(args++)).u.intValue;
					break;
				}
				fmtint(str, &len, size, value, 10, width, precision, flags);
				break;
			case 'X':
				flags |= PRINT_F_UP;
				// FALLTHROUGH
			case 'x':
				base = 16;
				// FALLTHROUGH
			case 'o':
				if (base == 0)
					base = 8;
				// FALLTHROUGH
			case 'u':
				if (base == 0)
					base = 10;
				flags |= PRINT_F_UNSIGNED;
				switch (cflags) 
				{
				case PRINT_C_CHAR:
					value = Plugin_SL_ConvertToString((*(args++)).u.stringValue)[0];
					break;
				case PRINT_C_SHORT:
				case PRINT_C_LONG:
				case PRINT_C_LLONG:
				case PRINT_C_SIZE:
				case PRINT_C_INTMAX:
				case PRINT_C_PTRDIFF:
				default:
					value = (*(args++)).u.intValue;
					break;
				}
				fmtint(str, &len, size, value, base, width, precision, flags);
				break;
			case 'A':
				/* Not yet supported, we'll use "%F". */
				// FALLTHROUGH
			case 'F':
				flags |= PRINT_F_UP;
			case 'a':
				/* Not yet supported, we'll use "%f". */
				// FALLTHROUGH
			case 'f':
				if (cflags == PRINT_C_LDOUBLE)
					fvalue = (*(args++)).u.floatValue;
				else
					fvalue = (*(args++)).u.floatValue;
				fmtflt(str, &len, size, fvalue, width, precision, flags, &overflow);
				if (overflow)
					goto out;
				break;
			case 'E':
				flags |= PRINT_F_UP;
				// FALLTHROUGH
			case 'e':
				flags |= PRINT_F_TYPE_E;
				if (cflags == PRINT_C_LDOUBLE)
					fvalue = (*(args++)).u.floatValue;
				else
					fvalue = (*(args++)).u.floatValue;
				fmtflt(str, &len, size, fvalue, width, precision, flags, &overflow);
				if (overflow)
					goto out;
				break;
			case 'G':
				flags |= PRINT_F_UP;
				// FALLTHROUGH
			case 'g':
				flags |= PRINT_F_TYPE_G;
				if (cflags == PRINT_C_LDOUBLE)
					fvalue = (*(args++)).u.floatValue;
				else
					fvalue = (*(args++)).u.floatValue;
				/**
				 * If the precision is zero, it is treated as
				 * one (cf. C99: 7.19.6.1, 8).
				 */
				if (precision == 0)
					precision = 1;
				fmtflt(str, &len, size, fvalue, width, precision, flags, &overflow);
				if (overflow)
					goto out;
				break;
			case 'c':
				cvalue = Plugin_SL_ConvertToString((*(args++)).u.stringValue)[0];
				OUTCHAR(str, len, size, cvalue);
				break;
			case 's':
				strvalue = Plugin_SL_ConvertToString((*(args++)).u.stringValue);
				fmtstr(str, &len, size, strvalue, width, precision, flags);
				break;
			case 'p':
				/**
				 * C99 says: "The value of the pointer is
				 * converted to a sequence of printing
				 * characters, in an implementation-defined
				 * manner." (C99: 7.19.6.1, 8)
				 */
				if ((strvalue = (const char *)(*(args++)).u.pointerValue) == NULL)
				{
					/**
					 * We use the glibc format.  BSD prints
					 * "0x0", SysV "0".
					 */
					fmtstr(str, &len, size, "(nil)", width, -1, flags);
				}
				else 
				{
					/**
					 * We use the BSD/glibc format. SysV
					 * omits the "0x" prefix (which we emit
					 * using the PRINT_F_NUM flag).
					 */
					flags |= PRINT_F_NUM;
					flags |= PRINT_F_UNSIGNED;
					fmtint(str, &len, size, (UINTPTR_T)strvalue, 16, width, precision, flags);
				}
				break;
			case '%':	// Print a "%" character verbatim
				OUTCHAR(str, len, size, ch);
				break;
			default:	// Skip other characters
				break;
			}
			ch = *format++;
			state = PRINT_S_DEFAULT;
			base = cflags = flags = width = 0;
			precision = -1;
			break;
		}
	}
out:
	if (len < size)
		str[len] = '\0';
	else if (size > 0)
		str[size - 1] = '\0';

	if (overflow || len >= INT_MAX) 
	{
		errno = overflow ? EOVERFLOW : ERANGE;
		return -1;
	}
	return (int)len;
}

void fmtstr(char* str, size_t* len, size_t size, const char* value, 
	int width, int precision, int flags)
{
	int padlen, strln;
	int noprecision = (precision == -1);

	if (value == NULL)
		value = "(null)";

	// If a precision was specified, don't read the string past it
	for (strln = 0; value[strln] != '\0' &&
		(noprecision || strln < precision); strln++)
		continue;

	if ((padlen = width - strln) < 0)
		padlen = 0;
	if (flags & PRINT_F_MINUS)
		padlen = -padlen;

	while (padlen > 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		padlen--;
	}
	while (*value != '\0' && (noprecision || precision-- > 0)) 
	{
		OUTCHAR(str, *len, size, *value);
		value++;
	}
	while (padlen < 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		padlen++;
	}
}

void fmtint(char* str, size_t* len, size_t size, INTMAX_T value, int base, 
	int width, int precision, int flags)
{
	UINTMAX_T uvalue;
	char iconvert[MAX_CONVERT_LENGTH];
	char sign = 0;
	char hexprefix = 0;
	int spadlen = 0;
	int zpadlen = 0;
	int pos;
	int separators = (flags & PRINT_F_QUOTE);
	int noprecision = (precision == -1);

	if (flags & PRINT_F_UNSIGNED)
		uvalue = value;
	else 
	{
		uvalue = (value >= 0) ? value : -value;
		if (value < 0)
			sign = '-';
		else if (flags & PRINT_F_PLUS)
			sign = '+';
		else if (flags & PRINT_F_SPACE)
			sign = ' ';
	}

	pos = convert(uvalue, iconvert, sizeof(iconvert), base, flags & PRINT_F_UP);
	if (flags & PRINT_F_NUM && uvalue != 0) 
	{
		/**
		 * C99 says: "The result is converted to an `alternative form'.
		 * For `o' conversion, it increases the precision, if and only
		 * if necessary, to force the first digit of the result to be a
		 * zero (if the value and precision are both 0, a single 0 is
		 * printed).  For `x' (or `X') conversion, a nonzero result has
		 * `0x' (or `0X') prefixed to it." (7.19.6.1, 6)
		 */
		switch (base) 
		{
		case 8:
			if (precision <= pos)
				precision = pos + 1;
			break;
		case 16:
			hexprefix = (flags & PRINT_F_UP) ? 'X' : 'x';
			break;
		}
	}
	if (separators)
		separators = getnumsep(pos);

	zpadlen = precision - pos - separators;
	spadlen = width                         // Minimum field width
		- separators                        // Number of separators
		- MAX(precision, pos)               // Number of integer digits
		- ((sign != 0) ? 1 : 0)             // Will we print a sign ?
		- ((hexprefix != 0) ? 2 : 0);       // Will we print a prefix ?

	if (zpadlen < 0)
		zpadlen = 0;
	if (spadlen < 0)
		spadlen = 0;

	/**
	 * C99 says: "If the `0' and `-' flags both appear, the `0' flag is
	 * ignored.  For `d', `i', `o', `u', `x', and `X' conversions, if a
	 * precision is specified, the `0' flag is ignored." (7.19.6.1, 6)
	 */
	if (flags & PRINT_F_MINUS)
		spadlen = -spadlen;
	else if (flags & PRINT_F_ZERO && noprecision) 
	{
		zpadlen += spadlen;
		spadlen = 0;
	}
	while (spadlen > 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		spadlen--;
	}
	if (sign != 0)
		OUTCHAR(str, *len, size, sign);
	if (hexprefix != 0) 
	{
		OUTCHAR(str, *len, size, '0');
		OUTCHAR(str, *len, size, hexprefix);
	}
	while (zpadlen > 0) 
	{
		OUTCHAR(str, *len, size, '0');
		zpadlen--;
	}
	while (pos > 0) 
	{
		pos--;
		OUTCHAR(str, *len, size, iconvert[pos]);
		if (separators > 0 && pos > 0 && pos % 3 == 0)
			printsep(str, len, size);
	}
	while (spadlen < 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		spadlen++;
	}
}

void fmtflt(char* str, size_t* len, size_t size, LDOUBLE fvalue, int width,
	int precision, int flags, int* overflow)
{
	LDOUBLE ufvalue;
	UINTMAX_T intpart;
	UINTMAX_T fracpart;
	UINTMAX_T mask;
	const char* infnan = NULL;
	char iconvert[MAX_CONVERT_LENGTH];
	char fconvert[MAX_CONVERT_LENGTH];
	char econvert[4];
	char esign = 0;
	char sign = 0;
	int leadfraczeros = 0;
	int exponent = 0;
	int emitpoint = 0;
	int omitzeros = 0;
	int omitcount = 0;
	int padlen = 0;
	int epos = 0;
	int fpos = 0;
	int ipos = 0;
	int separators = (flags & PRINT_F_QUOTE);
	int estyle = (flags & PRINT_F_TYPE_E);
#if HAVE_LOCALECONV && HAVE_LCONV_DECIMAL_POINT
	struct lconv* lc = localeconv();
#endif

	/**
	 * AIX' man page says the default is 0, but C99 and at least Solaris'
	 * and NetBSD's man pages say the default is 6, and sprintf(3) on AIX
	 * defaults to 6.
	 */
	if (precision == -1)
		precision = 6;

	if (fvalue < 0.0)
		sign = '-';
	else if (flags & PRINT_F_PLUS)
		sign = '+';
	else if (flags & PRINT_F_SPACE)
		sign = ' ';

	if (ISNAN(fvalue))
		infnan = (flags & PRINT_F_UP) ? "NAN" : "nan";
	else if (ISINF(fvalue))
		infnan = (flags & PRINT_F_UP) ? "INF" : "inf";

	if (infnan != NULL) 
	{
		if (sign != 0)
			iconvert[ipos++] = sign;
		while (*infnan != '\0')
			iconvert[ipos++] = *infnan++;
		fmtstr(str, len, size, iconvert, width, ipos, flags);
		return;
	}

	// "%e" (or "%E") or "%g" (or "%G") conversion
	if (flags & PRINT_F_TYPE_E || flags & PRINT_F_TYPE_G) 
	{
		if (flags & PRINT_F_TYPE_G) 
		{
			/**
			 * For "%g" (and "%G") conversions, the precision
			 * specifies the number of significant digits, which
			 * includes the digits in the integer part.  The
			 * conversion will or will not be using "e-style" (like
			 * "%e" or "%E" conversions) depending on the precision
			 * and on the exponent.  However, the exponent can be
			 * affected by rounding the converted value, so we'll
			 * leave this decision for later.  Until then, we'll
			 * assume that we're going to do an "e-style" conversion
			 * (in order to get the exponent calculated).  For
			 * "e-style", the precision must be decremented by one.
			 */
			precision--;
			/**
			 * For "%g" (and "%G") conversions, trailing zeros are
			 * removed from the fractional portion of the result
			 * unless the "#" flag was specified.
			 */
			if (!(flags & PRINT_F_NUM))
				omitzeros = 1;
		}
		exponent = getexponent(fvalue);
		estyle = 1;
	}

again:
	/**
	 * Sorry, we only support 9, 19, or 38 digits (that is, the number of
	 * digits of the 32-bit, the 64-bit, or the 128-bit UINTMAX_MAX value
	 * minus one) past the decimal point due to our conversion method.
	 */
	switch (sizeof(UINTMAX_T)) 
	{
	case 16:
		if (precision > 38)
			precision = 38;
		break;
	case 8:
		if (precision > 19)
			precision = 19;
		break;
	default:
		if (precision > 9)
			precision = 9;
		break;
	}
	ufvalue = (fvalue >= 0.0) ? fvalue : -fvalue;
	if (estyle)
		ufvalue /= mypow10(exponent);

	if ((intpart = cast(ufvalue)) == UINTMAX_MAX) 
	{
		*overflow = 1;
		return;
	}

	/**
	 * Factor of ten with the number of digits needed for the fractional
	 * part.  For example, if the precision is 3, the mask will be 1000.
	 */
	mask = mypow10(precision);
	/**
	 * We "cheat" by converting the fractional part to integer by
	 * multiplying by a factor of ten.
	 */
	if ((fracpart = myround(mask * (ufvalue - intpart))) >= mask) 
	{
		/**
		 * For example, ufvalue = 2.99962, intpart = 2, and mask = 1000
		 * (because precision = 3).  Now, myround(1000 * 0.99962) will
		 * return 1000.  So, the integer part must be incremented by one
		 * and the fractional part must be set to zero.
		 */
		intpart++;
		fracpart = 0;
		if (estyle && intpart == 10) 
		{
			/**
			 * The value was rounded up to ten, but we only want one
			 * integer digit if using "e-style".  So, the integer
			 * part must be set to one and the exponent must be
			 * incremented by one.
			 */
			intpart = 1;
			exponent++;
		}
	}

	/**
	 * Now that we know the real exponent, we can check whether or not to
	 * use "e-style" for "%g" (and "%G") conversions.  If we don't need
	 * "e-style", the precision must be adjusted and the integer and
	 * fractional parts must be recalculated from the original value.
	 *
	 * C99 says: "Let P equal the precision if nonzero, 6 if the precision
	 * is omitted, or 1 if the precision is zero.  Then, if a conversion
	 * with style `E' would have an exponent of X:
	 *
	 * - if P > X >= -4, the conversion is with style `f' (or `F') and
	 *   precision P - (X + 1).
	 *
	 * - otherwise, the conversion is with style `e' (or `E') and precision
	 *   P - 1." (7.19.6.1, 8)
	 *
	 * Note that we had decremented the precision by one.
	 */
	if (flags & PRINT_F_TYPE_G && estyle && precision + 1 > exponent && exponent >= -4) 
	{
		precision -= exponent;
		estyle = 0;
		goto again;
	}

	if (estyle) 
	{
		if (exponent < 0) 
		{
			exponent = -exponent;
			esign = '-';
		}
		else
			esign = '+';

		/**
		 * Convert the exponent.  The sizeof(econvert) is 4.  So, the
		 * econvert buffer can hold e.g. "e+99" and "e-99".  We don't
		 * support an exponent which contains more than two digits.
		 * Therefore, the following stores are safe.
		 */
		epos = convert(exponent, econvert, 2, 10, 0);
		/**
		 * C99 says: "The exponent always contains at least two digits,
		 * and only as many more digits as necessary to represent the
		 * exponent." (7.19.6.1, 8)
		 */
		if (epos == 1)
			econvert[epos++] = '0';
		econvert[epos++] = esign;
		econvert[epos++] = (flags & PRINT_F_UP) ? 'E' : 'e';
	}

	// Convert the integer part and the fractional part
	ipos = convert(intpart, iconvert, sizeof(iconvert), 10, 0);
	if (fracpart != 0)
		fpos = convert(fracpart, fconvert, sizeof(fconvert), 10, 0);

	leadfraczeros = precision - fpos;

	if (omitzeros) 
	{
		if (fpos > 0)
		{
			while (omitcount < fpos && fconvert[omitcount] == '0')
				omitcount++;
		}
		else 
		{
			omitcount = precision;
			leadfraczeros = 0;
		}
		precision -= omitcount;
	}

	/**
	 * Print a decimal point if either the fractional part is non-zero
	 * and/or the "#" flag was specified.
	 */
	if (precision > 0 || flags & PRINT_F_NUM)
		emitpoint = 1;
	if (separators)
		separators = getnumsep(ipos);

	padlen = width                  // Minimum field width
		- ipos                      // Number of integer digits
		- epos                      // Number of exponent characters
		- precision                 // Number of fractional digits
		- separators                // Number of group separators
		- (emitpoint ? 1 : 0)       // Will we print a decimal point ?
		- ((sign != 0) ? 1 : 0);    // Will we print a sign character ?

	if (padlen < 0)
		padlen = 0;

	/**
	 * C99 says: "If the `0' and `-' flags both appear, the `0' flag is
	 * ignored." (7.19.6.1, 6)
	 */
	if (flags & PRINT_F_MINUS)
		padlen = -padlen;
	else if (flags & PRINT_F_ZERO && padlen > 0) 
	{
		if (sign != 0) 
		{
			OUTCHAR(str, *len, size, sign);
			sign = 0;
		}
		while (padlen > 0) 
		{
			OUTCHAR(str, *len, size, '0');
			padlen--;
		}
	}
	while (padlen > 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		padlen--;
	}
	if (sign != 0)
		OUTCHAR(str, *len, size, sign);
	while (ipos > 0) 
	{
		ipos--;
		OUTCHAR(str, *len, size, iconvert[ipos]);
		if (separators > 0 && ipos > 0 && ipos % 3 == 0)
			printsep(str, len, size);
	}
	if (emitpoint) 
	{
#if HAVE_LOCALECONV && HAVE_LCONV_DECIMAL_POINT
		if (lc->decimal_point != NULL && *lc->decimal_point != '\0')
			OUTCHAR(str, *len, size, *lc->decimal_point);
		else
#endif
			OUTCHAR(str, *len, size, '.');
	}
	while (leadfraczeros > 0) 
	{
		OUTCHAR(str, *len, size, '0');
		leadfraczeros--;
	}
	while (fpos > omitcount) 
	{
		fpos--;
		OUTCHAR(str, *len, size, fconvert[fpos]);
	}
	while (epos > 0) 
	{
		epos--;
		OUTCHAR(str, *len, size, econvert[epos]);
	}
	while (padlen < 0) 
	{
		OUTCHAR(str, *len, size, ' ');
		padlen++;
	}
}

void printsep(char* str, size_t* len, size_t size)
{
#if HAVE_LOCALECONV && HAVE_LCONV_THOUSANDS_SEP
	struct lconv* lc = localeconv();
	int i;

	if (lc->thousands_sep != NULL)
	{
		for (i = 0; lc->thousands_sep[i] != '\0'; i++)
			OUTCHAR(str, *len, size, lc->thousands_sep[i]);
	}
	else
#endif
		OUTCHAR(str, *len, size, ',');
}

int getnumsep(int digits)
{
	int separators = (digits - ((digits % 3 == 0) ? 1 : 0)) / 3;
#if HAVE_LOCALECONV && HAVE_LCONV_THOUSANDS_SEP
	int strln;
	struct lconv* lc = localeconv();

	// We support an arbitrary separator length (including zero)
	if (lc->thousands_sep != NULL) 
	{
		for (strln = 0; lc->thousands_sep[strln] != '\0'; strln++)
			continue;
		separators *= strln;
	}
#endif
	return separators;
}

int getexponent(LDOUBLE value)
{
	LDOUBLE tmp = (value >= 0.0) ? value : -value;
	int exponent = 0;

	/**
	 * We check for 99 > exponent > -99 in order to work around possible
	 * endless loops which could happen (at least) in the second loop (at
	 * least) if we're called with an infinite value.  However, we checked
	 * for infinity before calling this function using our ISINF() macro, so
	 * this might be somewhat paranoid.
	 */
	while (tmp < 1.0 && tmp > 0.0 && --exponent > -99)
		tmp *= 10;
	while (tmp >= 10.0 && ++exponent < 99)
		tmp /= 10;
	return exponent;
}

int convert(UINTMAX_T value, char* buf, size_t size, int base, int caps)
{
	const char* digits = caps ? "0123456789ABCDEF" : "0123456789abcdef";
	size_t pos = 0;

	// We return an unterminated buffer with the digits in reverse order
	do 
	{
		buf[pos++] = digits[value % base];
		value /= base;
	} 
	while (value != 0 && pos < size);

	return (int)pos;
}

UINTMAX_T cast(LDOUBLE value)
{
	UINTMAX_T result;

	/**
	 * We check for ">=" and not for ">" because if UINTMAX_MAX cannot be
	 * represented exactly as an LDOUBLE value (but is less than LDBL_MAX),
	 * it may be increased to the nearest higher representable value for the
	 * comparison (cf. C99: 6.3.1.4, 2).  It might then equal the LDOUBLE
	 * value although converting the latter to UINTMAX_T would overflow.
	 */
	if (value >= UINTMAX_MAX)
		return UINTMAX_MAX;
	result = value;

	/**
	 * At least on NetBSD/sparc64 3.0.2 and 4.99.30, casting long double to
	 * an integer type converts e.g. 1.9 to 2 instead of 1 (which violates
	 * the standard).  Sigh.
	 */
	return (result <= value) ? result : result - 1;
}

UINTMAX_T myround(LDOUBLE value)
{
	UINTMAX_T intpart = cast(value);
	return ((value -= intpart) < 0.5) ? intpart : intpart + 1;
}

LDOUBLE mypow10(int exponent)
{
	LDOUBLE result = 1;

	while (exponent > 0) 
	{
		result *= 10;
		exponent--;
	}
	while (exponent < 0) 
	{
		result /= 10;
		exponent++;
	}
	return result;
}
