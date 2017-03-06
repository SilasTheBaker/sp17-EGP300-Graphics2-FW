
#include "Quaternion.h"
#include <egpfw/Vector3.h>
#include <egpfw/Matrix4x4.h>
#include <math.h>

Quaternion::Quaternion()
{
	//Identity
	mVals.i = 0.0;
	mVals.j = 0.0;
	mVals.k = 0.0;
	mVals.w = 1.0;
}

Quaternion::Quaternion(float i, float j, float k, float w)
{
	mVals.i = i;
	mVals.i = j;
	mVals.i = k;
	mVals.i = w;
}

Quaternion::Quaternion(const Quaternion &quat)
{
	mVals.i = quat.mVals.i;
	mVals.i = quat.mVals.j;
	mVals.i = quat.mVals.k;
	mVals.i = quat.mVals.w;
}

Quaternion::Quaternion(float amount, const Vector3 &axis)
{
	Vector3 axisNomalize = axis.normalize();

	axisNomalize *= amount;

	mVals.i = axisNomalize.x;
	mVals.j = axisNomalize.y;
	mVals.k = axisNomalize.z;
	mVals.w = cos(amount);
}

Quaternion Quaternion::makeRotationX(float xRot)
{
	Vector3 xAxis = Vector3(1, 0, 0);
	return Quaternion(xRot, xAxis);
}

Quaternion Quaternion::makeRotationY(float yRot)
{
	Vector3 yAxis = Vector3(0, 1, 0);
	return Quaternion(yRot, yAxis);
}

Quaternion Quaternion::makeRotationZ(float zRot)
{
	Vector3 zAxis = Vector3(0, 0, 1);
	return Quaternion(zRot, zAxis);
}

Quaternion Quaternion::makeIdentity()
{
	return Quaternion(); //This is the identity
}

Quaternion Quaternion::makeRotationXYZ(float xRot, float yRot, float zRot)
{
	return makeRotationX(xRot) * makeRotationY(yRot) * makeRotationZ(zRot);
}

Quaternion Quaternion::makeRotationZYX(float xRot, float yRot, float zRot) //Is this wrong
{
	return makeRotationZ(zRot) * makeRotationY(yRot) * makeRotationX(xRot);
}

Quaternion Quaternion::multiply(const Quaternion &left, const Quaternion &right)
{
	float i = right.mVals.w * left.mVals.i +
			  right.mVals.i * left.mVals.w -
			  right.mVals.j * left.mVals.k +
			  right.mVals.k * left.mVals.j;

	float j = right.mVals.w * left.mVals.j +
			  right.mVals.i * left.mVals.k +
			  right.mVals.j * left.mVals.w -
			  right.mVals.k * left.mVals.i;

	float k = right.mVals.w * left.mVals.k -
			  right.mVals.i * left.mVals.j +
			  right.mVals.j * left.mVals.i +
			  right.mVals.k * left.mVals.w;

	float w = right.mVals.w * left.mVals.w -
			  right.mVals.i * left.mVals.i -
			  right.mVals.j * left.mVals.j -
			  right.mVals.k * left.mVals.k;

	return Quaternion(i, j, k, w);
}

 //i-x j-y k-z 
Matrix4x4 Quaternion::getTransformation(const Quaternion &quat)
{
	Matrix3x3 result3x3;

	result3x3.elements[0][0] = 1 - 2 * quat.mVals.j * quat.mVals.j - 2 * quat.mVals.k * quat.mVals.k;
	result3x3.elements[0][1] =     2 * quat.mVals.i * quat.mVals.j - 2 * quat.mVals.k * quat.mVals.w;
	result3x3.elements[0][2] =     2 * quat.mVals.i * quat.mVals.k + 2 * quat.mVals.j * quat.mVals.w;
	result3x3.elements[1][0] =     2 * quat.mVals.i * quat.mVals.j + 2 * quat.mVals.k * quat.mVals.w;
	result3x3.elements[1][1] = 1 - 2 * quat.mVals.i * quat.mVals.i - 2 * quat.mVals.k * quat.mVals.k;
	result3x3.elements[1][2] =     2 * quat.mVals.j * quat.mVals.k - 2 * quat.mVals.i * quat.mVals.w;
	result3x3.elements[2][0] =     2 * quat.mVals.i * quat.mVals.k - 2 * quat.mVals.j * quat.mVals.w;
	result3x3.elements[2][1] =     2 * quat.mVals.j * quat.mVals.k + 2 * quat.mVals.i * quat.mVals.w;
	result3x3.elements[2][2] = 1 - 2 * quat.mVals.i * quat.mVals.i - 2 * quat.mVals.j * quat.mVals.j;

	return makeTransformFromRotation(&result3x3);
}

//http://gamedev.stackexchange.com/questions/28395/rotating-vector3-by-a-quaternion
Quaternion Quaternion::rotateVector3(const Quaternion &quat, const Vector3 &vec)
{
	// Extract the vector part of the quaternion
	Vector3 qVec = Vector3(quat.mVals.i, quat.mVals.j, quat.mVals.k);

	float scaler = quat.mVals.w;

	//vprime = 2.0f * dot(u, v) * u + (s*s - dot(u, u)) * v + 2.0f * s * cross(u, v);
	Vector3 result = qVec * 2.0f * Vector3::dot(qVec, vec) + 
					 vec * (scaler * scaler - Vector3::dot(qVec, qVec)) + 
					 Vector3::crossProduct(qVec, vec) * 2.0f * scaler;

	return Quaternion();
}

Quaternion Quaternion::operator*(const Quaternion& other) const
{
	return multiply(*this, other);
}

Quaternion::~Quaternion()
{

}
