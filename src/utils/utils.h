#pragma once
#include <CGSC/cgsc.h>

#define Q_COLOR_ESCAPE '^'
#define Q_IsColorString(p) (p && *(p) == Q_COLOR_ESCAPE && *((p) + 1) && *((p) + 1) != Q_COLOR_ESCAPE)

#define COLOR_BLACK '0'
#define COLOR_RED '1'
#define COLOR_GREEN '2'
#define COLOR_YELLOW '3'
#define COLOR_BLUE '4'
#define COLOR_CYAN '5'
#define COLOR_MAGENTA '6'
#define COLOR_WHITE '7'

#define ColorIndex(c) (((c) - '0') & 7)

extern int q3ToAnsi[8];

void GScr_GetType();
void GScr_Ternary();
void GScr_IfUndef();

char* fmt(char* format, ...);
qboolean HasFlag(int var, int flag);
qboolean IsFlag(int var, int flag);
