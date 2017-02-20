#include "Vector3.h"
#include <stdio.h>
#include <math.h>


void assignVector3(float x, float y, float z, struct Vector3* vec)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

GLfloat magnitude(const struct Vector3* vec)
{
	return sqrt(vec->x * vec->x + vec->y * vec->y + vec->z *vec->z);
}

GLfloat sqrMagnitude(const struct Vector3* vec)
{
	return vec->x * vec->x + vec->y * vec->y + vec->z *vec->z;
}

GLfloat dotProduct(const struct Vector3* left, const struct Vector3* right)
{
	return left->x*right->x + left->y * right->y + left->z * right->z;
}

struct Vector3 crossProduct(const struct Vector3* left, const struct Vector3* right)
{
	struct Vector3 result;

	result.x = left->y * right->z - left->z * right->y;
	result.y = left->z * right->x - left->x * right->z;
	result.z = left->x * right->y - left->y * right->x;

	return result;
}

struct Vector3 lerp(const struct Vector3* start, const struct Vector3* end, float t)
{
	struct Vector3 result;
	
	if (t < 0) t = 0;
	if (t > 1) t = 1;

	result.x = start->x * (1 - t) + end->x * t;
	result.x = start->y * (1 - t) + end->y * t;
	result.x = start->z * (1 - t) + end->z * t;

	return result;
}

struct Vector3 multiplyVector3(GLfloat scaler, const struct Vector3* vec)
{
	struct Vector3 result;

	result.x = vec->x * scaler;
	result.y = vec->y * scaler;
	result.z = vec->z * scaler;

	return result;
}

struct Vector3 subtractVector3(const struct Vector3* left, const struct Vector3* right)
{
	struct Vector3 result;

	result.x = left->x - right->x;
	result.y = left->y - right->y;
	result.z = left->z - right->z;

	return result;
}

struct Vector3 addVector3(const struct Vector3* left, const struct Vector3* right)
{
	struct Vector3 result;

	result.x = left->x + right->x;
	result.y = left->y + right->y;
	result.z = left->z + right->z;

	return result;
}

void convertVector3ToArray(const struct Vector3* vec, GLfloat* arr)
{
	arr[0] = vec->x;
	arr[1] = vec->y;
	arr[2] = vec->z;
}

struct Vector3 convertArrayToVector3(const GLfloat* arr)
{
	struct Vector3 vec;

	vec.x = arr[0];
	vec.y = arr[1];
	vec.z = arr[2];

	return vec;
}