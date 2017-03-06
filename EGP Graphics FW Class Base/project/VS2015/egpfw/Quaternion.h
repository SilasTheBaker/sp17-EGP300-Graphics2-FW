//Implement a quaternion type in C with the same features as the 3D vector
//structure described above. Extend its functionality by implementing the
//following free functions: 
//	X - make rotation X, 
//	X - make rotation Y, 
//	X - make rotation Z,
//	X - make rotation XYZ 
//  O - and ZYX, 
//	X - make identity, 
//	X - concatenate, 
//	X - multiply 3D vector, //	O - spherical linear interpolation(SLERP), //	X - convert to 3D matrix.

#pragma once
#include <egpfw/Vector3.h>
#include <egpfw/Matrix4x4.h>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float i, float j, float k, float w);
	Quaternion(const Quaternion& quat);
	Quaternion(float amount, const Vector3& axis);
	~Quaternion();

	static Quaternion makeRotationX(float xRot);
	static Quaternion makeRotationY(float xRot);
	static Quaternion makeRotationZ(float zRot);
	static Quaternion makeIdentity();
	static Quaternion makeRotationXYZ(float xRot, float yRot, float zRot);
	static Quaternion makeRotationZYX(float xRot, float yRot, float zRot);
	static Quaternion multiply(const Quaternion& left, const Quaternion& right);
	static Matrix4x4 getTransformation(const Quaternion& quat);
	static Quaternion rotateVector3(const Quaternion& left, const Vector3& vec);
	
	//Operators
	Quaternion operator*(const Quaternion& other) const;

private:
	union
	{
		float mData[4];
		struct
		{
			float i, j, k, w;
		} mVals;
	};



};
