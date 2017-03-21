// By Dan Buckstein
// Modified by: _______________________________________________________________
#include "egpfw/egpfw/egpfwInterpolation.h"


#include <math.h>


// ****
// lerp and lerp inverse
float egpfwLerp(const float v0, const float v1, const float param)
{
	//...
	return v0 + (v1 - v0) * param;
}

// ****
float egpfwLerpInv(const float v0, const float v1, const float v)
{
	//...
	return egpfwLerp(v0, v1, 1 - v);
}


// ****
// Catmull-Rom spline interpolation
float egpfwCatmullRom(const float pPrev, const float p0, const float p1, const float pNext, const float t)
{
	float t2 = t * t;
	float t3 = t * t * t;

	float first = -t + 2 * t2 - t3;
	float second = 2 - 5 * t2 + 3 * t3;
	float third = t + 4 * t2 - 3 * t3;
	float fourth = -t2 + t3;

	return 0.5f * (pPrev * first + p0 * second + p1 * third + pNext * fourth);
}


// ****
// Cubic hermite spline interpolation
float egpfwCubicHermite(const float v0, const float dv0, const float v1, const float dv1, const float t)
{
	//...
	float t2 = t * t;
	float t3 = t * t * t;

	float first = 1 - 3 * t2 + 2 * t3;
	float second = t - 2 * t2 + t3;
	float third = 3 * t2 - 2 * t3;
	float fourth = -t2 + t3;

	return first * v0 + second * dv0 + third * v1 + fourth * dv1;
}


// Bezier spline interpolation
float egpfwBezier0(const float v0, const float param)
{
	// this function is complete!
	return v0;
}

// ****
float egpfwBezier1(const float v0, const float v1, const float param)
{
	//...
	return egpfwLerp(v0, v1, param);
}

// ****
float egpfwBezier2(const float v0, const float v1, const float v2, const float t)
{
	//...
	float lerp1 = egpfwLerp(v0, v1, t);
	float lerp2 = egpfwLerp(v1, v2, t);

	return egpfwLerp(lerp1, lerp2, t);
}

// ****
float egpfwBezier3(const float v0, const float v1, const float v2, const float v3, const float t)
{
	//...
	float lerp1 = egpfwLerp(v0, v1, t);
	float lerp2 = egpfwLerp(v1, v2, t);
	float lerp3 = egpfwLerp(v2, v3, t);

	return egpfwLerp(egpfwLerp(lerp1, lerp2, t), egpfwLerp(lerp2, lerp3, t), t);
}

// ****
float egpfwBezier4(const float v0, const float v1, const float v2, const float v3, const float v4, const float t)
{
	//...
	float lerp1 = egpfwLerp(v0, v1, t);
	float lerp2 = egpfwLerp(v1, v2, t);
	float lerp3 = egpfwLerp(v2, v3, t);
	float lerp4 = egpfwLerp(v3, v4, t);

	return egpfwBezier3(lerp1, lerp2, lerp3, lerp4, t);
}

// ****
float egpfwBezier(const float *v, unsigned int order, const float param)
{
	//...
	return 0.0f;
}


// ****
// vector interpolation
void egpfwLerpVector(const float *v0, const float *v1, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwCatmullRomVector(const float *vPrev, const float *v0, const float *v1, const float *vNext, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwCubicHermiteVector(const float *v0, const float *dv0, const float *v1, const float *dv1, const float param, const unsigned int numElements, float *v_out)
{
	//...
}

// ****
void egpfwBezierVector(const float *v, unsigned int order, const float param, const unsigned int numElements, float *v_out)
{
	//...
}


// ****
// table sampling
unsigned int egpfwSearchSampleTable(const float *sampleTable, const float *paramTable, const float searchParam, unsigned int numElements, float *param_out)
{
	//...
	return 0;
}


// ****
// calculate arc length
float egpfwComputeArcLengthCatmullRom(const float *vPrev, const float *v0, const float *v1, const float *vNext, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthCubicHermite(const float *v0, const float *dv0, const float *v1, const float *dv1, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}

// ****
float egpfwComputeArcLengthBezier(const float *v, unsigned int order, unsigned int numElements, unsigned int numSamples, int autoNormalize, float *prevSamplePtr, float *currentSamplePtr, float *sampleTable_out, float *paramTable_out)
{
	//...
	return 0.0f;
}
