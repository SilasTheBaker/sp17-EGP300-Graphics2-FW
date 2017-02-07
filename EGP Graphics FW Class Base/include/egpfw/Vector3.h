#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <GL/glew.h>

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus


	struct Vector3
	{
		GLfloat x,
				y,
				z;
	};

	void assignVector3(float x, float y, float z, struct Vector3* vec);
	struct Vector3 addVector3(const struct Vector3* left, const struct Vector3* right);
	struct Vector3 subtractVector3(const struct Vector3* left, const struct Vector3* right);
	struct Vector3 multiplyVector3(GLfloat scaler, const struct Vector3* vec);
	struct Vector3 lerp(const struct Vector3* start, const struct Vector3* end, float t);
	GLfloat magnitude(const struct Vector3* vec);
	GLfloat sqrMagnitude(const struct Vector3* vec);
	GLfloat dotProduct(const struct Vector3* left, const struct Vector3* right);
	struct Vector3 crossProduct(const struct Vector3* left, const struct Vector3* right);
	void convertVector3ToArray(const struct Vector3* vec, GLfloat* arr);
	struct Vector3 convertArrayToVector3(const GLfloat* arr);


#ifdef __cplusplus
}
#endif // __cplusplus

#endif
