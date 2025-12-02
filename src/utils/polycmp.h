#pragma once
#include <CGSC/cgsc.h>

float VectorDistance(vec3_t a, vec3_t b);

int VectorCmp(const void *a, const void *b);
int IntCmp(const void *a, const void *b);
int FloatCmp(const void *a, const void *b);
int StringCmp(const void *a, const void *b);

int Scr_VectorCmp(const void *a, const void *b);
int Scr_IntCmp(const void *a, const void *b);
int Scr_FloatCmp(const void *a, const void *b);
int Scr_StringCmp(const void *a, const void *b);
