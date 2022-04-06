#include "polycmp.h"

#include <string.h>
#include <math.h>

float VectorDistance(vec3_t a, vec3_t b)
{
	float x = a[0] - b[0];
	float y = a[1] - b[1];
	float z = a[2] - b[2];

	return sqrtf((x * x) + (y * y) + (z * z));
}

int VectorCmp(const void *a, const void *b)
{
	vec3_t zero;
	vec3_t *vecA = (vec3_t *)a;
	vec3_t *vecB = (vec3_t *)b;

	float distanceA = VectorDistance(*vecA, zero);
	float distanceB = VectorDistance(*vecB, zero);
	
	return distanceA - distanceB;
}

int FloatCmp(const void *a, const void *b)
{
	const float ia = *(const float *)a;
	const float ib = *(const float *)b;

	return ia - ib;
}

int IntCmp(const void *a, const void *b)
{
	const int ia = *(const int *)a;
	const int ib = *(const int *)b;

	return ia - ib;
}

int StringCmp(const void *a, const void *b)
{
	const char *ia = *(const char **)a;
	const char *ib = *(const char **)b;

	return strcmp(ia, ib);
}

int Scr_VectorCmp(const void *a, const void *b)
{
	vec3_t zero;
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;

	vec3_t vecA;
	vecA[0] = ia->u.vectorValue[0];
	vecA[1] = ia->u.vectorValue[1];
	vecA[2] = ia->u.vectorValue[2];

	vec3_t vecB;
	vecB[0] = ib->u.vectorValue[0];
	vecB[1] = ib->u.vectorValue[1];
	vecB[2] = ib->u.vectorValue[2];

	float distanceA = VectorDistance(vecA, zero);
	float distanceB = VectorDistance(vecB, zero);

	return distanceA - distanceB;
}

int Scr_FloatCmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;

	return ia->u.floatValue - ib->u.floatValue;
}

int Scr_IntCmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;

	return ia->u.intValue - ib->u.intValue;
}

int Scr_StringCmp(const void *a, const void *b)
{
	VariableValue *ia = *(VariableValue **)a;
	VariableValue *ib = *(VariableValue **)b;

	const char *sia = Plugin_SL_ConvertToString(ia->u.stringValue);
	const char *sib = Plugin_SL_ConvertToString(ib->u.stringValue);

	return strcmp(sia, sib);
}
