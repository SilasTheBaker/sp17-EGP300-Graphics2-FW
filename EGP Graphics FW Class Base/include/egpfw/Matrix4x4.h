#pragma once

/*
Implement a 4D (4x4) homogeneous transformation structure in C with

the following free functions: make transform from rotation and/or uniform

scale and/or translation, inverse, concatenate, multiply 3D vector.
*/



#include <GL/glew.h>

struct Matrix3x3;
class Vector3;

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4();
	static Matrix4x4 makeTransformFromRotation(const Matrix3x3* rotationMatix);
	static Matrix4x4 uniformScaleMatrix4x4(GLfloat scale);
	static Matrix4x4 identityMatrix4X4();
	static void zeroOutMatrix4x4(Matrix4x4 &matrix);
	static Matrix4x4 concatenateMatrix4X4(const Matrix4x4* left, const Matrix4x4* right);
	static Matrix4x4 makeTransform(const Vector3* translation);
	static Matrix4x4 makeTransform(const Vector3* translation, const struct Matrix3x3* rotationMatrix);
	static Vector3 matrix4X4TimesVector3(const Matrix4x4 &transform, const Vector3 &vec);

	Matrix4x4 inverse();
	Matrix3x3 getRotationMatrix();
	Vector3 Matrix4x4::getVector3();

	//These should be private buut getters would get pretty annoying
	// in some of my other code I may overload this later
	GLfloat elements[4][4];
private:

};

