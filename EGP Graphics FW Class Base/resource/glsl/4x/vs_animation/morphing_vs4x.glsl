/*
	Morphing
	By Dan Buckstein
	Vertex shader that performs morph target animation.
	
	Modified by: ______________________________________________________________
*/

#version 430


// ****
// attributes: one per morphing attribute (e.g. multiple positions)
layout (location = 0) in vec4 position0;
layout (location = 1) in vec4 position1;
layout (location = 2) in vec4 position2;
layout (location = 3) in vec4 position3;

// ****
// uniforms: animation controls
#define KEYFRAME_COUNT 4

uniform mat4 mvp;
uniform float param;
uniform int index[KEYFRAME_COUNT];

// varying output: solid color
out vec4 passColor;

// ****
// LERP
vec4 lerp(in vec4 p0, in vec4 p1, const float t)
{
	return p0 + (p1 - p0) * t;
}

// ****
// Catmull-Rom spline interpolation
vec4 sampleCatmullRom(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const float t)
{
	mat4 influenceMat = mat4(pPrev, p0, p1, pNext);
	mat4 MCR = transpose(mat4(0, -1, 2, -1, 2, 0, -5, 3, 0, 1, 4, -3, 0, 0, -1, 1));
	
	MCR *= 0.5f;
	vec4 polyTerms = vec4(1, t, t * t, t * t * t);

	return influenceMat * MCR * polyTerms;
}

// ****
// draw cubic Hermite spline segment
vec4 sampleCubicHermite(in vec4 p0, in vec4 m0, in vec4 p1, in vec4 m1, const float t)
{
	mat4 influenceMat = mat4(p0, m0, p1, m1);
	mat4 MCR = transpose(mat4(1, 0, -3, 2, 0, 1, -2, 1, 0, 0, 3, -2, 0, 0, -1, 1));
	vec4 polyTerms = vec4(1, t, t * t, t * t * t);

	return influenceMat * MCR * polyTerms;
}

void main()
{
	// ****
	// do morphing, transform the correct result before assigning to output

	vec4 position;

	vec4 p[KEYFRAME_COUNT] = { position0, position1, position2, position3 };

	position = sampleCatmullRom(p[index[0]], p[index[1]], p[index[2]], p[index[3]], param);
	//position = sampleCubicHermite(p[index[0]], p[index[1]], p[index[2]], p[index[3]], param);

	gl_Position = mvp * position;

	// TESTING: send position as color to give us some variance
	passColor = position*0.5+0.5;
}