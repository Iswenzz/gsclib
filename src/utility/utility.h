#pragma once
#include "../../dependencies/cgsc.h"

void GScr_ComPrintf();

void GScr_GetType();
void GScr_Ternary();
void GScr_IfUndef();

void GScr_ToString();
void GScr_ToFloat();
void GScr_ToInt();

qboolean HasFlag(int var, int flag);
qboolean IsFlag(int var, int flag);

float vec_distance(vec3_t a, vec3_t b);

int vec3_cmp(const void *a, const void *b);
int int_cmp(const void *a, const void *b);
int float_cmp(const void *a, const void *b);
int cstring_cmp(const void *a, const void *b);
int gsc_vec3_cmp(const void *a, const void *b);
int gsc_int_cmp(const void *a, const void *b);
int gsc_float_cmp(const void *a, const void *b);
int gsc_cstring_cmp(const void *a, const void *b);