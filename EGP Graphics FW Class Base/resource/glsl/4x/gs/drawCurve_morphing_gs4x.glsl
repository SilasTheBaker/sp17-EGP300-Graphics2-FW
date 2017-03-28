/*
	Draw Curve - Morphing
	By Dan Buckstein
	Geometry shader that draws the path that a morphing vertex follows.
	
	Modified by: ______________________________________________________________
*/

#version 410

// ****
const vec4 BLUE = vec4(0.0, 0.5, 1.0, 1.0);
#define SAMPLES_PER_SEGMENT 128

// geometry type layout qualifiers
layout (triangles) in;
layout (line_strip, max_vertices = SAMPLES_PER_SEGMENT) out;

// ****
// receive varying data
in vertexdata
{
	vec4 position0;
	vec4 position1;
	vec4 position2;
	vec4 position3;
} pass[];

// uniforms
uniform mat4 mvp;

// varying output: solid color
out vec4 passColor;


void drawLineFull(in vec4 p0, in vec4 p1)
{
	gl_Position = mvp * p0;
	EmitVertex();
	gl_Position = mvp * p1;
	EmitVertex();
	EndPrimitive();
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
// draw Catmull-Rom spline segment
void drawCatmullRomSplineSegment(in vec4 pPrev, in vec4 p0, in vec4 p1, in vec4 pNext, const int samples, const float dt)
{
	int i = 0;
	float t = 0.0;

	for(i = 0; i <= samples; i++)
	{
		gl_Position = mvp * sampleCatmullRom(pPrev, p0, p1, pNext, t);
		EmitVertex();
		t += dt;
	}

	EndPrimitive();
}

void main()
{
	// ****
	// do line drawing
	const int samples = SAMPLES_PER_SEGMENT / 12;
	const float dt = 1.0 / float(samples);

	passColor = BLUE;

	//drawLineFull(pass[0].position0, pass[0].position1);
	//drawLineFull(pass[1].position0, pass[1].position1);
	//drawLineFull(pass[2].position0, pass[2].position1);

	//drawLineFull(pass[0].position1, pass[0].position2);
	//drawLineFull(pass[1].position1, pass[1].position2);
	//drawLineFull(pass[2].position1, pass[2].position2);
	
	//drawLineFull(pass[0].position2, pass[0].position3);
	//drawLineFull(pass[1].position2, pass[1].position3);
	//drawLineFull(pass[2].position2, pass[2].position3);
	
	//drawLineFull(pass[0].position3, pass[0].position0);
	//drawLineFull(pass[1].position3, pass[1].position0);
	//drawLineFull(pass[2].position3, pass[2].position0);


	drawCatmullRomSplineSegment(pass[0].position0, pass[0].position1, pass[0].position2, pass[0].position3, samples, dt);
	drawCatmullRomSplineSegment(pass[0].position1, pass[0].position2, pass[0].position3, pass[0].position0, samples, dt);
	drawCatmullRomSplineSegment(pass[0].position2, pass[0].position3, pass[0].position0, pass[0].position1, samples, dt);
	drawCatmullRomSplineSegment(pass[0].position3, pass[0].position0, pass[0].position1, pass[0].position2, samples, dt);


	drawCatmullRomSplineSegment(pass[1].position0, pass[1].position1, pass[1].position2, pass[1].position3, samples, dt);
	drawCatmullRomSplineSegment(pass[1].position1, pass[1].position2, pass[1].position3, pass[1].position0, samples, dt);
	drawCatmullRomSplineSegment(pass[1].position2, pass[1].position3, pass[1].position0, pass[1].position1, samples, dt);
	drawCatmullRomSplineSegment(pass[1].position3, pass[1].position0, pass[1].position1, pass[1].position2, samples, dt);


	drawCatmullRomSplineSegment(pass[2].position0, pass[2].position1, pass[2].position2, pass[2].position3, samples, dt);
	drawCatmullRomSplineSegment(pass[2].position1, pass[2].position2, pass[2].position3, pass[2].position0, samples, dt);
	drawCatmullRomSplineSegment(pass[2].position2, pass[2].position3, pass[2].position0, pass[2].position1, samples, dt);
	drawCatmullRomSplineSegment(pass[2].position3, pass[2].position0, pass[2].position1, pass[2].position2, samples, dt);


	//drawCatmullRomSplineSegment(pass[3].position0, pass[3].position1, pass[3].position2, pass[3].position3, samples, dt);
	//drawCatmullRomSplineSegment(pass[3].position1, pass[3].position2, pass[3].position3, pass[3].position0, samples, dt);
	//drawCatmullRomSplineSegment(pass[3].position2, pass[3].position3, pass[3].position0, pass[3].position1, samples, dt);
	//drawCatmullRomSplineSegment(pass[3].position3, pass[3].position0, pass[3].position1, pass[3].position2, samples, dt);

	// testing: pass solid color


	
	
// DEBUGGING: draw a normal vector for each vertex
	//const vec4 n = vec4(0.0, 0.0, 1.0, 0.0);
	//drawLineFull(pass[0].position1, pass[0].position1 + n);
	//drawLineFull(pass[1].position1, pass[1].position1 + n);
	//drawLineFull(pass[2].position1, pass[2].position1 + n);
}