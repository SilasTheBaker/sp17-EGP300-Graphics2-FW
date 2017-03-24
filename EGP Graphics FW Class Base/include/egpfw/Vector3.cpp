#include "Vector3.h"
#include <stdio.h>
#include <math.h>


Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

Vector3::~Vector3()
{
}

float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z *z);
}

float Vector3::sqrMagnitude() const
{
	return x * x + y * y + z * z;
}

float Vector3::dot(const Vector3 &left, const Vector3 &right)
{
	return left.x*right.x + left.y * right.y + left.z * right.z;
}

Vector3 Vector3::crossProduct(const Vector3 &left, const Vector3 &right)
{
	Vector3 result;

	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;

	return result;
}

Vector3 Vector3::lerp(const Vector3 &start, const Vector3 &end, float t)
{
	Vector3 result;
	
	if (t < 0) t = 0;
	if (t > 1) t = 1;

	result.x = start.x * (1 - t) + end.x * t;
	result.x = start.y * (1 - t) + end.y * t;
	result.x = start.z * (1 - t) + end.z * t;

	return result;
}

Vector3 Vector3::multiply(float scaler) const
{
	Vector3 result;

	result.x = x * scaler;
	result.y = y * scaler;
	result.z = z * scaler;

	return result;
}

Vector3 Vector3::multiplyVector3(const Vector3 &vec, float scaler)
{
	Vector3 result;

	result.x = vec.x * scaler;
	result.y = vec.y * scaler;
	result.z = vec.z * scaler;

	return result;
}


Vector3 Vector3::subtractVector3(const Vector3 &left, const Vector3 &right)
{
	Vector3 result;

	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;

	return result;
}

Vector3 Vector3::addVector3(const Vector3 &left, const Vector3 &right)
{
	Vector3 result;

	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;

	return result;
}

void Vector3::convertVector3ToArray(GLfloat* arr) const
{
	arr[0] = x;
	arr[1] = y;
	arr[2] = z;
}

Vector3 Vector3::convertArrayToVector3(const GLfloat* arr)
{
	Vector3 vec;

	vec.x = arr[0];
	vec.y = arr[1];
	vec.z = arr[2];

	return vec;
}

Vector3 Vector3::normalize() const
{
	return *this * (1.0f / magnitude());
}


Vector3 Vector3::operator*(float scaler) const
{
	return multiply(scaler);
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
	return addVector3(*this, rhs);
}

Vector3& Vector3::operator*=(const float& scaler)
{
	*this = *this * scaler;

	

}

