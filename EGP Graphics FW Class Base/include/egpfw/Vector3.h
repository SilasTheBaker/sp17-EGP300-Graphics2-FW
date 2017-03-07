#pragma once


#include <GL/glew.h>

class Vector3
{
public:
	Vector3();
	Vector3(float newX, float newY, float newZ);
	~Vector3();
	static float dot(const Vector3& left, const Vector3& right);
	static Vector3 crossProduct(const Vector3& left, const Vector3& right);
	static Vector3 lerp(const Vector3& start, const Vector3& end, float t);
	static Vector3 subtractVector3(const Vector3& left, const Vector3& right);
	static Vector3 addVector3(const Vector3& left, const Vector3& right);
	static Vector3 multiplyVector3(const Vector3& vec, float scaler);
	static Vector3 convertArrayToVector3(const GLfloat* arr);

	float magnitude() const;
	float sqrMagnitude() const;
	Vector3 multiply(float scaler) const;
	void convertVector3ToArray(GLfloat* arr) const;
	Vector3 normalize() const;


	Operators
	Vector3 operator*(float scaler) const;
	Vector3 operator+(const Vector3& rhs) const;
	Vector3& operator*=(const float& scaler);

	These should probably be private but getters would be annoying
	float x,
		  y,
		  z;

private:
};