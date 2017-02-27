// By Dan Buckstein
// Modified by: Charlie McGarey, Silas Baker, and Laura Reilly
/*
We certify that this work is
entirely our own. The assessor of this project may reproduce this project
and provide copies to other academic staff, and/or communicate a copy of
this project to a plagiarism-checking service, which may retain a copy of the
project on its database.
*/
#include "egpfw/egpfw/egpfwOBJLoader.h"


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define BUFFER_OFFSET_BYTE(p,n) ((char *)(p) + n)


// ****
// load triangulated OBJ file
// File-IO work done by Silas Baker and Laura Reilly
// OBJ loading and debugging done by Charlie McGarey and Silas Baker
egpTriOBJDescriptor egpfwLoadTriangleOBJ(const char *objPath, const egpMeshNormalMode normalMode, const double globalScale)
{
	// load triangulated OBJ file
	egpTriOBJDescriptor obj = { 0 };
	obj.numFaces = obj.numNormals = obj.numTexcoords = obj.numVerticies = 0;

	unsigned int vertexCount = 0, texCoordCount = 0, normalCount = 0, faceCount = 0;

	if (objPath && objPath != "")
	{
		FILE* file = fopen(objPath, "r");
		int currentIndex = 0;

		while (1) //count size
		{
			char header[256];

			int readVal = fscanf(file, "%s", header);

			if (readVal == EOF) break; //reached the end

			if (strcmp(header, "v") == 0) //vertex positions
				vertexCount++;
			else if (strcmp(header, "vt") == 0) //vertex textcoords
				texCoordCount++;
			else if (strcmp(header, "vn") == 0) //vertex normals
				normalCount++;
			else if (strcmp(header, "f") == 0) // faces
				faceCount++;
		}

		// Allocates
		obj.vertices = calloc(vertexCount + 1, sizeof(float3));
		obj.texcoords = calloc(texCoordCount + 1, sizeof(float2));
		obj.normals = calloc(normalCount + 1, sizeof(float3));
		obj.faces = calloc(faceCount + 1, sizeof(egpFace));

		rewind(file);

		while (1) //true
		{
			char header[256];

			int readVal = fscanf(file, "%s", header);

			if (readVal == EOF)
				break; //reached the end

			if (strcmp(header, "v") == 0) //vertex positions
			{
				float3 vertex;
				vertex.f0 = vertex.f1 = vertex.f2 = 0.0f;
				fscanf(file, "%f %f %f\n", &vertex.f0, &vertex.f1, &vertex.f2);
				obj.vertices[obj.numVerticies] = vertex;
				obj.numVerticies++;
			}
			else if (strcmp(header, "vt") == 0) //vertex textcoords
			{
				float2 texcoord;
				texcoord.f0 = texcoord.f1 = 0.0f;
				fscanf(file, "%f %f\n", &texcoord.f0, &texcoord.f1);
				obj.texcoords[obj.numTexcoords] = texcoord;
				obj.numTexcoords++;
			}
			else if (strcmp(header, "vn") == 0) //vertex normals
			{
				float3 normal;
				normal.f0 = normal.f1 = normal.f2 = 0.0f;
				fscanf(file, "%f %f %f\n", &normal.f0, &normal.f1, &normal.f2);
				obj.normals[obj.numNormals] = normal;
				obj.numNormals++;
			}
			else if (strcmp(header, "f") == 0)
			{
				egpFace face;
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face.vertexIndicies[0], &face.texcoordIndicies[0], &face.normalIndicies[0],
					&face.vertexIndicies[1], &face.texcoordIndicies[1], &face.normalIndicies[1],
					&face.vertexIndicies[2], &face.texcoordIndicies[2], &face.normalIndicies[2]);

				// all .obj indices start at 1, array indicies start at 0 
				--face.vertexIndicies[0]; --face.texcoordIndicies[0]; --face.normalIndicies[0];
				--face.vertexIndicies[1]; --face.texcoordIndicies[1]; --face.normalIndicies[1];
				--face.vertexIndicies[2]; --face.texcoordIndicies[2]; --face.normalIndicies[2];


				if (matches != 9)
				{
					printf("File cannot be parsed.\n");
					egpTriOBJDescriptor obj2 = { 0 };
					return obj2;
				}
				obj.faces[obj.numFaces] = face;
				obj.numFaces++;
			}
		}

		fclose(file);

	}
	return obj;
}


// ****
// convert OBJ to VAO & VBO
// written by Silas Baker
int egpfwCreateVAOFromOBJ(const egpTriOBJDescriptor *obj, egpVertexArrayObjectDescriptor *vao_out, egpVertexBufferObjectDescriptor *vbo_out)
{
	if (!obj || !vao_out || !vbo_out)
		return -1;

	unsigned int numVertices = obj->numFaces * 3;

	// allocate data for faces
	float3* vertices = calloc(sizeof(float3), numVertices);
	float3* normals = calloc(sizeof(float3), numVertices);
	float2* texcoords = calloc(sizeof(float2), numVertices);

	unsigned int j = -1;
	for (unsigned int i = 0; i < obj->numFaces; i++)
	{
		struct egpFace face = obj->faces[i];

		//Vertex One
		j++;
		vertices[j] = obj->vertices[face.vertexIndicies[0]];
		normals[j] = obj->normals[face.normalIndicies[0]];
		texcoords[j] = obj->texcoords[face.texcoordIndicies[0]];

		//Vertex Two
		j++;
		vertices[j] = obj->vertices[face.vertexIndicies[1]];
		normals[j] = obj->normals[face.normalIndicies[1]];
		texcoords[j] = obj->texcoords[face.texcoordIndicies[1]];

		//Vertex Three
		j++;
		vertices[j] = obj->vertices[face.vertexIndicies[2]];
		normals[j] = obj->normals[face.normalIndicies[2]];
		texcoords[j] = obj->texcoords[face.texcoordIndicies[2]];
	}


	unsigned int attribsSize = 3;
	egpAttributeDescriptor attribs[] = { egpCreateAttributeDescriptor(ATTRIB_POSITION, ATTRIB_VEC3, vertices),
		egpCreateAttributeDescriptor(ATTRIB_NORMAL, ATTRIB_VEC3, normals),
		egpCreateAttributeDescriptor(ATTRIB_TEXCOORD, ATTRIB_VEC2, texcoords) };

	*vbo_out = egpCreateVBOInterleaved(attribs, attribsSize, numVertices);
	*vao_out = egpCreateVAO(PRIM_TRIANGLES, vbo_out, NULL);

	free(vertices);
	free(normals);
	free(texcoords);

	return 0;
}


// ****
// free obj data
// written by Charlie McGarey
int egpfwReleaseOBJ(egpTriOBJDescriptor *obj)
{
	free(obj->faces);
	obj->faces = NULL;
	free(obj->vertices);
	obj->vertices = NULL;
	free(obj->texcoords);
	obj->texcoords = NULL;
	free(obj->normals);
	obj->normals = NULL;
	return 0;
}


// ****
// save/load binary
// Both written by Charlie McGarey
int egpfwSaveBinaryOBJ(const egpTriOBJDescriptor *obj, const char *binPath)
{
	FILE* binFile = fopen(binPath, "wb");

	if (!binFile)
	{
		fprintf(stderr, "Couldn't open file at %s for writing!", binPath);
		return 1;
	}

	fwrite(&obj->numVerticies, sizeof(unsigned int), 1, binFile);
	for (unsigned int i = 0; i < obj->numVerticies; i++)
	{
		fwrite(&obj->vertices[i], sizeof(float3), 1, binFile);
	}
	fwrite(&obj->numTexcoords, sizeof(unsigned int), 1, binFile);
	for (unsigned int i = 0; i < obj->numTexcoords; i++)
	{
		fwrite(&obj->texcoords[i], sizeof(float2), 1, binFile);
	}
	fwrite(&obj->numNormals, sizeof(unsigned int), 1, binFile);
	for (unsigned int i = 0; i < obj->numNormals; i++)
	{
		fwrite(&obj->normals[i], sizeof(float3), 1, binFile);
	}
	fwrite(&obj->numFaces, sizeof(unsigned int), 1, binFile);
	for (unsigned int i = 0; i < obj->numFaces; i++)
	{
		fwrite(&obj->faces[i].vertexIndicies, sizeof(unsigned int), 3, binFile);
		fwrite(&obj->faces[i].texcoordIndicies, sizeof(unsigned int), 3, binFile);
		fwrite(&obj->faces[i].normalIndicies, sizeof(unsigned int), 3, binFile);
	}

	fclose(binFile);
	return 0;
}

egpTriOBJDescriptor egpfwLoadBinaryOBJ(const char *binPath)
{
	egpTriOBJDescriptor obj = { 0 };
	FILE* binFile = fopen(binPath, "rb");

	if (!binFile)
	{
		fprintf(stderr, "Couldn't open file at %s for reading!", binPath);
		return obj;
	}

	fread(&obj.numVerticies, sizeof(unsigned int), 1, binFile);
	obj.vertices = calloc(obj.numVerticies, sizeof(float3));
	for (unsigned int i = 0; i < obj.numVerticies; i++)
	{
		fread(&obj.vertices[i], sizeof(float3), 1, binFile);
	}
	fread(&obj.numTexcoords, sizeof(unsigned int), 1, binFile);
	obj.texcoords = calloc(obj.numTexcoords, sizeof(float2));
	for (unsigned int i = 0; i < obj.numTexcoords; i++)
	{
		fread(&obj.texcoords[i], sizeof(float2), 1, binFile);
	}
	fread(&obj.numNormals, sizeof(unsigned int), 1, binFile);
	obj.normals = calloc(obj.numNormals, sizeof(float3));
	for (unsigned int i = 0; i < obj.numNormals; i++)
	{
		fread(&obj.normals[i], sizeof(float3), 1, binFile);
	}
	fread(&obj.numFaces, sizeof(unsigned int), 1, binFile);
	obj.faces = calloc(obj.numFaces, sizeof(egpFace));
	for (unsigned int i = 0; i < obj.numFaces; i++)
	{
		fread(&obj.faces[i].vertexIndicies, sizeof(unsigned int), 3, binFile);
		fread(&obj.faces[i].texcoordIndicies, sizeof(unsigned int), 3, binFile);
		fread(&obj.faces[i].normalIndicies, sizeof(unsigned int), 3, binFile);
	}

	fclose(binFile);
	return obj;
}


// these functions are complete!
// get attribute data from OBJ
const void *egpfwGetOBJAttributeData(const egpTriOBJDescriptor *obj, const egpAttributeName attrib)
{
	if (obj && obj->data && obj->attribOffset[attrib])
		return BUFFER_OFFSET_BYTE(obj->data, obj->attribOffset[attrib]);
	return 0;
}

unsigned int egpfwGetOBJNumVertices(const egpTriOBJDescriptor *obj)
{
	if (obj && obj->data)
		return *((unsigned int *)obj->data);
	return 0;
}