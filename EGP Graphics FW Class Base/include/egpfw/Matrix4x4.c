#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vector3.h"

struct Matrix4x4 makeTransformFromRotation(const struct Matrix3x3* rotationMatix)
{
	struct Matrix4x4 transform = identityMatrix4X4();

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			transform.elements[i][j] = rotationMatix->elements[i][j];
		}
	}

	return transform;
}

struct Matrix4x4 makeTransformFromVector3(const struct Vector3* translation)
{
	struct Matrix4x4 transform = identityMatrix4X4();

	transform.elements[0][3] = translation->x;
	transform.elements[1][3] = translation->y;
	transform.elements[2][3] = translation->z;

	return transform;
}

struct Matrix4x4 makeTransformFromTransformAndVector3(const struct Vector3* translation, const struct Matrix3x3* rotationMatrix)
{
	struct Matrix4x4 transform = identityMatrix4X4();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			transform.elements[i][j] = rotationMatrix->elements[i][j];
		}
	}

	transform.elements[0][3] = translation->x;
	transform.elements[1][3] = translation->y;
	transform.elements[2][3] = translation->z;

	return transform;
}

struct Matrix4x4 uniformScaleMatrix4x4(GLfloat scale)
{
	struct Matrix4x4 uniformScaleMatrix;

	zeroOutMatrix4x4(&uniformScaleMatrix);

	for (int i = 0; i < 4; i++)
	{
		uniformScaleMatrix.elements[i][i] = scale;
	}

	return uniformScaleMatrix;
}

struct Matrix4x4 identityMatrix4X4()
{
	return uniformScaleMatrix4x4(1);
}

void zeroOutMatrix4x4(struct Matrix4x4* matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix->elements[i][j] = 0;
		}
	}
}

struct Matrix3x3 concatenateMatrix4X4(const struct Matrix4x4* left, const struct Matrix4x4* right)
{
	struct Matrix4x4 result;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				result.elements[i][j] += left->elements[i][k] * right->elements[k][j];
			}
		}
	}
}

struct Vector3 matrix4X4TimesVector3(const struct Matrix4x4* transform, const struct Vector3* vec)
{
	GLfloat result[4];
	GLfloat vector[4];
	convertVector3ToArray(vec, vector);
	vector[3] = 1;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i] += transform->elements[i][j] * vector[j];
		}
	}

	return convertArrayToVector3(vector);
}

struct Matrix4x4 inverseMatrix4x4(const struct Matrix4x4* transform)
{
	struct Matrix3x3 invRot = getRotationFrom4x4(transform);
	invRot = inverseMatrix3x3(&invRot);

	struct Vector3 invTranslation = getVector3From4x4(transform);
	invTranslation = multiplyByVector3(&invRot, &invTranslation);

	struct Matrix4x4 result = makeTransformFromTransformAndVector3(&invTranslation, &invRot);
	return result;
}

struct Matrix3x3 getRotationFrom4x4(const struct Matrix4x4* transform)
{
	struct Matrix3x3 rotationMatrix;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rotationMatrix.elements[i][j] = transform->elements[i][j];
		}
	}

	return rotationMatrix;
}

struct Vector3 getVector3From4x4(const struct Matrix4x4* transform)
{
	struct Vector3 translation;

	translation.x = transform->elements[0][3];
	translation.y = transform->elements[1][3];
	translation.z = transform->elements[2][3];

	return translation;
}

