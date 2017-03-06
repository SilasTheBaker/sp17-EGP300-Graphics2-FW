#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vector3.h"

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::~Matrix4x4()
{
	
}


Matrix4x4 Matrix4x4::makeTransformFromRotation(const struct Matrix3x3* rotationMatix)
{
	Matrix4x4 transform = identityMatrix4X4();

	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			transform.elements[i][j] = rotationMatix->elements[i][j];
		}
	}

	return transform;
}
 
Matrix4x4 Matrix4x4::makeTransform(const Vector3* translation)
{
	Matrix4x4 transform = identityMatrix4X4();

	transform.elements[0][3] = translation->x;
	transform.elements[1][3] = translation->y;
	transform.elements[2][3] = translation->z;

	return transform;
}

Matrix4x4 Matrix4x4::makeTransform(const Vector3* translation, const struct Matrix3x3* rotationMatrix)
{
	Matrix4x4 transform = identityMatrix4X4();

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

Matrix4x4 Matrix4x4::uniformScaleMatrix4x4(GLfloat scale)
{
	Matrix4x4 uniformScaleMatrix;

	zeroOutMatrix4x4(uniformScaleMatrix);

	for (int i = 0; i < 4; i++)
	{
		uniformScaleMatrix.elements[i][i] = scale;
	}

	return uniformScaleMatrix;
}

Matrix4x4 Matrix4x4::identityMatrix4X4()
{
	return uniformScaleMatrix4x4(1);
}

void Matrix4x4::zeroOutMatrix4x4(Matrix4x4 &matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix.elements[i][j] = 0;
		}
	}
}

Matrix4x4 Matrix4x4::concatenateMatrix4X4(const Matrix4x4* left, const Matrix4x4* right)
{
	Matrix4x4 result;

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

	return result;
}

Vector3 Matrix4x4::matrix4X4TimesVector3(const Matrix4x4 &transform, const Vector3 &vec)
{
	GLfloat result[4];
	GLfloat vector[4];
	vec.convertVector3ToArray(vector);
	vector[3] = 1;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i] += transform.elements[i][j] * vector[j];
		}
	}

	return Vector3::convertArrayToVector3(vector);
}

Matrix4x4 Matrix4x4::inverse()
{
	struct Matrix3x3 invRot = getRotationMatrix();
	invRot = inverseMatrix3x3(&invRot);

	Vector3 invTranslation = getVector3();
	invTranslation = multiplyByVector3(&invRot, &invTranslation);

	return makeTransform(&invTranslation, &invRot);
}

struct Matrix3x3 Matrix4x4::getRotationMatrix()
{
	struct Matrix3x3 rotationMatrix;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			rotationMatrix.elements[i][j] = elements[i][j];
		}
	}

	return rotationMatrix;
}

Vector3 Matrix4x4::getVector3()
{
	Vector3 translation;

	translation.x = elements[0][3];
	translation.y = elements[1][3];
	translation.z = elements[2][3];

	return translation;
}

