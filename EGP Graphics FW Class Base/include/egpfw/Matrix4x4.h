
/*
Implement a 4D (4x4) homogeneous transformation structure in C with

the following free functions: make transform from rotation and/or uniform

scale and/or translation, inverse, concatenate, multiply 3D vector.
*/


#ifndef MATRIX_4_X_4_H
#define MATRIX_4_X_4_H

#include <GL/glew.h>
#include "Matrix3x3.h"


#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

	struct Matrix4x4
	{
		GLfloat elements[4][4];
	};

	struct Matrix4x4 makeTransformFromRotation(const struct Matrix3x3* rotationMatix);
	struct Matrix4x4 makeTransformFromVector3(const struct Vector3* translation);
	struct Matrix3x3 concatenateMatrix4X4(const struct Matrix4x4* left, const struct Matrix4x4* right);
	struct Matrix4x4 makeTransformFromTransformAndVector3(const struct Vector3* translation, const struct Matrix3x3* rotationMatrix);
	struct Matrix4x4 uniformScaleMatrix4x4(GLfloat scale);
	struct Matrix4x4 inverseMatrix4x4(const struct Matrix4x4* transform);
	struct Matrix4x4 identityMatrix4X4();
	struct Matrix3x3 getRotationFrom4x4(const struct Matrix4x4* transform);
	struct Vector3 getVector3From4x4(const struct Matrix4x4* transform);
	void zeroOutMatrix4x4(struct Matrix4x4* matrix);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif //MATRIX_4_X_4_H
