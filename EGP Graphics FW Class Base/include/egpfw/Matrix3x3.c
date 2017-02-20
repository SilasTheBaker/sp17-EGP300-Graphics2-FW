#include "Matrix3x3.h"
#include "Vector3.h"
#include <stdio.h>
#include <math.h>

void copyMatrix(struct Matrix3x3* dest, const struct Matrix3x3* source)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			dest->elements[i][j] = source->elements[i][j];
		}
	}
}

struct Matrix3x3 transposeMatrix3x3(const struct Matrix3x3* matrix)
{
	struct Matrix3x3 transpose;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; i++)
		{
			transpose.elements[i][j] = matrix->elements[j][i];
		}
	}

	return transpose;
}

//Only works on rotation matricies
struct Matrix3x3 inverseMatrix3x3(const struct Matrix3x3* rotationMatrix)
{
	//I guess????
	return transposeMatrix3x3(rotationMatrix);
}

struct Matrix3x3 uniformScaleMatrix3x3(GLfloat scale)
{
	struct Matrix3x3 uniformScaleMatrix;

	zeroOutMatrix3x3(&uniformScaleMatrix);

	for (int i = 0; i < 3; i++)
	{
		uniformScaleMatrix.elements[i][i] = scale;
	}

	return uniformScaleMatrix;
}

struct Matrix3x3 identityMatrix3X3()
{
	return uniformScaleMatrix3x3(1);
}

struct Matrix3x3 concatenateMatrix3X3(const struct Matrix3x3* left, const struct Matrix3x3* right)
{
	struct Matrix3x3 result;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				result.elements[i][j] += left->elements[i][k] * right->elements[k][j];
			}
		}
	}
}

//Not sure if this works
struct Vector3 multiplyByVector3(const struct Matrix3x3* matrix, const struct Vector3* vec)
{
	GLfloat vector[3];
	convertVector3ToArray(vec, vector);

	GLfloat result[3];

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			result[i] += matrix->elements[i][j] * vector[j];
		}
	}

	return convertArrayToVector3(vector);
}

void zeroOutMatrix3x3(struct Matrix3x3* matrix)
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			matrix->elements[i][j] = 0;
		}
	}
}

struct Matrix3x3 xRotationMatrix3x3(const GLfloat xRot)
{
	struct Matrix3x3 rotationMatrix = identityMatrix3X3();

	rotationMatrix.elements[1][1] = cos(xRot);
	rotationMatrix.elements[1][2] = -sin(xRot);
	rotationMatrix.elements[2][1] = sin(xRot);
	rotationMatrix.elements[2][2] = cos(xRot);

	return rotationMatrix;
}

struct Matrix3x3 yRotationMatrix3x3(const GLfloat yRot)
{
	struct Matrix3x3 rotationMatrix = identityMatrix3X3();

	rotationMatrix.elements[0][0] = cos(yRot);
	rotationMatrix.elements[0][2] = sin(yRot);
	rotationMatrix.elements[2][0] = -sin(yRot);
	rotationMatrix.elements[2][2] = cos(yRot);

	return rotationMatrix;
}

struct Matrix3x3 zRotationMatrix3x3(const GLfloat zRot)
{
	struct Matrix3x3 rotationMatrix = identityMatrix3X3();

	rotationMatrix.elements[0][0] = cos(zRot);
	rotationMatrix.elements[0][1] = -sin(zRot);
	rotationMatrix.elements[1][0] = sin(zRot);
	rotationMatrix.elements[1][1] = cos(zRot);

	return rotationMatrix;
}

struct Vector3 eulerXYZRotation(const struct Vector3* vector, const GLfloat xRot, const GLfloat yRot, const GLfloat zRot)
{
	struct Vector3 product;

	struct Matrix3x3 xRotation = xRotationMatrix3x3(xRot);
	struct Matrix3x3 yRotation = yRotationMatrix3x3(yRot);
	struct Matrix3x3 zRotation = zRotationMatrix3x3(zRot);

	struct Matrix3x3 zyRot = concatenateMatrix3X3(&yRotation, &zRotation);
	struct Matrix3x3 xyzRot = concatenateMatrix3X3(&xRotation, &zyRot);
	product = multiplyByVector3(&xyzRot, vector);

	return product;
}

struct Vector3 eulerZYXRotation(const struct Vector3* vector, const GLfloat zRot, const GLfloat yRot, const GLfloat xRot)
{
	struct Vector3 product;

	struct Matrix3x3 xRotation = xRotationMatrix3x3(xRot);
	struct Matrix3x3 yRotation = yRotationMatrix3x3(yRot);
	struct Matrix3x3 zRotation = zRotationMatrix3x3(zRot);

	struct Matrix3x3 xyRot = concatenateMatrix3X3(&yRotation, &xRotation);
	struct Matrix3x3 xyzRot = concatenateMatrix3X3(&zRotation, &xyRot);
	product = multiplyByVector3(&xyzRot, vector);

	return product;
}

struct Matrix3x3 eulerXYZRotationMatrix(const GLfloat xRot, const GLfloat yRot, const GLfloat zRot)
{
	struct Matrix3x3 xRotation = xRotationMatrix3x3(xRot);
	struct Matrix3x3 yRotation = yRotationMatrix3x3(yRot);
	struct Matrix3x3 zRotation = zRotationMatrix3x3(zRot);

	struct Matrix3x3 zyRot = concatenateMatrix3X3(&yRotation, &zRotation);
	return concatenateMatrix3X3(&xRotation, &zyRot);
}

struct Matrix3x3 eulerZYXRotationMatrix(const GLfloat zRot, const GLfloat yRot, const GLfloat xRot)
{
	struct Matrix3x3 xRotation = xRotationMatrix3x3(xRot);
	struct Matrix3x3 yRotation = yRotationMatrix3x3(yRot);
	struct Matrix3x3 zRotation = zRotationMatrix3x3(zRot);

	struct Matrix3x3 xyRot = concatenateMatrix3X3(&yRotation, &xRotation);
	return concatenateMatrix3X3(&zRotation, &xyRot);
}
