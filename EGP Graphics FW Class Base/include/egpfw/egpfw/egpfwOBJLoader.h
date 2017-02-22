/*
	EGP Graphics Framework
	(c) 2017 Dan Buckstein
	Wavefront OBJ file loader by Dan Buckstein

	Modified by: ______________________________________________________________
*/

#ifndef __EGPFW_OBJLOADER_H
#define __EGPFW_OBJLOADER_H


#include "egpfw/egpfw/egpfwVertexBuffer.h"


#ifdef __cplusplus
extern "C"
{
#endif	// __cplusplus


//-----------------------------------------------------------------------------
// enumerators

	// normal calculation mode
	enum egpMeshNormalMode
	{
		NORMAL_LOAD,					// load normals from file
		NORMAL_COMPUTE_FACE,			// ignore normals from file and compute per-face
		NORMAL_COMPUTE_VERTEX,			// ignore normals from file and compute per-vertex
		NORMAL_COMPUTE_TANGENT_FACE,	// compute full tangent basis per-face (texcoords must exist)
		NORMAL_COMPUTE_TANGENT_VERTEX,	// compute full tangent basis per-vertex (texcoords must exist)
	};

#ifndef __cplusplus
	typedef enum egpMeshNormalMode egpMeshNormalMode;
#endif	// __cplusplus


//-----------------------------------------------------------------------------
// data structures

#ifndef __cplusplus
	typedef struct egpTriOBJDescriptor egpTriOBJDescriptor;
	typedef struct egpFace egpFace;
#endif	// __cplusplus

	// helper structures
	union float2
	{
		struct { float f0, f1; };
		float f[2];
	};
	union float3
	{
		struct { float f0, f1, f2; };
		float f[3];
	};
	union float4
	{
		struct { float f0, f1, f2, f3; };
		float f[4];
	};
	union int4
	{
		struct { int i0, i1, i2, i3; };
		int i[4];
	};
	union face
	{
		struct { unsigned int v0, v1, v2, vt0, vt1, vt2, vn0, vn1, vn2; };
		struct { unsigned int v[3], vt[3], vn[3]; };
	};

	struct uniqueTriFace;
	struct uniqueVertex;
	struct uniqueTexcoord;
	struct uniqueNormal;

#ifndef __cplusplus
	typedef union float2			float2;
	typedef union float3			float3;
	typedef union float4			float4;
	typedef union int4				int4;
	typedef union face				face;
	typedef struct uniqueTriFace	uniqueTriFace;
	typedef struct uniqueVertex		uniqueVertex;
	typedef struct uniqueTexcoord	uniqueTexcoord;
	typedef struct uniqueNormal		uniqueNormal;
#endif	// __cplusplus

	struct egpFace
	{
		unsigned int vertexIndicies[3];
		unsigned int texcoordIndicies[3];
		unsigned int normalIndicies[3];
	};

	// trianglulated OBJ descriptor
	// NOTE: this is a SHARED RESOURCE; do not load the same OBJ multiple times
	//	because that wastes memory; just *draw* it multiple times!
	// stores all attribute data contiguously
	struct egpTriOBJDescriptor
	{
		unsigned int attribOffset[16];
		unsigned int dataSize;
		void *data;
		unsigned int numVerticies;
		float3* vertices;
		unsigned int numTexcoords;
		float2* texcoords;
		unsigned int numNormals;
		float3* normals;
		unsigned int numFaces;
		egpFace* faces;
	};


//-----------------------------------------------------------------------------
// functions

	// load triangulated OBJ file
	// returns descriptor with fully-ordered, non-indexed attribute data
	// 'objPath' param cannot be null or an empty string
	// 'globalScale' will default to 1 if not positive
	egpTriOBJDescriptor egpfwLoadTriangleOBJ(const char *objPath, const egpMeshNormalMode normalMode, const double globalScale);

	// convert OBJ to VAO & VBO
	// returns number of active attributes if successful, 0 if failed
	// 'obj' param cannot be null and must be initialized
	// 'vao_out' and 'vbo_out' params cannot be null and must be empty
	int egpfwCreateVAOFromOBJ(const egpTriOBJDescriptor *obj, egpVertexArrayObjectDescriptor *vao_out, egpVertexBufferObjectDescriptor *vbo_out);

	// free obj data
	// returns 1 if successful, 0 if failed
	int egpfwReleaseOBJ(egpTriOBJDescriptor *obj);

	// write binary version to file for fast loading next time
	// additionally a load function which returns a new object
	// returns 1 if successful, 0 if failed
	// 'obj' param cannot be null and must be initialized
	// 'binPath' param cannot be null or an empty string
	int egpfwSaveBinaryOBJ(const egpTriOBJDescriptor *obj, const char *binPath);
	egpTriOBJDescriptor egpfwLoadBinaryOBJ(const char *binPath);

	// get attribute data from OBJ
	// 'obj' param cannot be null
	// returns null if the OBJ does not use the requested attribute
	// texcoords are 2D vectors
	// positions, normals, tangents, bitangents are 3D vectors
	// skin weights (float) and indices (int) are 4D vectors
	const void *egpfwGetOBJAttributeData(const egpTriOBJDescriptor *obj, const egpAttributeName attrib);
	unsigned int egpfwGetOBJNumVertices(const egpTriOBJDescriptor *obj);


//-----------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif	// __cplusplus


#endif	// __EGPFW_OBJLOADER_H