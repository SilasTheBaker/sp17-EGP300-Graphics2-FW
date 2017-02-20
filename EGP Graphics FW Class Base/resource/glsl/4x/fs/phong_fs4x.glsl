/*
	Phong (FS)
	By Dan Buckstein
	Fragment shader that computes Phong shading.
	
	Modified by: ______________________________________________________________
*/

// version
#version 410


// ****
// varyings
in vertex
{
	vec4 normal;
	vec4 lightVec;
	vec4 eyeVec;
	vec2 texcoord;
} data;

// ****
// uniforms
uniform sampler2D tex_dm;
uniform sampler2D tex_sm;

// ****
// target
layout (location = 0) out vec4 fragColor;

// shader function
void main()
{
	// ****
	// this example: phong shading algorithm

	//Diffuse Coeficient, need normal and light vector
	vec4 N = normalize(data.normal);
	vec4 L = normalize(data.lightVec);
	float kd = dot(N, L);

	//specular coeficient
	//need view vector and reflected vector
	vec4 V = normalize(data.eyeVec);
	vec4 R = (kd + kd)*N - L;
	float ks = dot(V, R);

	//calmp both and power specular
	kd = max(0.0, kd);
	ks = max(0.0, ks);
	ks *= ks;
	ks *= ks;
	ks *= ks;
	ks *= ks;

	// ****
	// output: phong
	const vec4 AMB = vec4(0.0, 0.1, 0.2, 1.0);
	//fragColor = AMB + vec4(kd + ks);

	// ****
	// extra: apply textures as well
	vec4 diffuseSample = texture(tex_dm, data.texcoord);
	vec4 specularSample = texture(tex_sm, data.texcoord);
	fragColor = AMB + diffuseSample * kd + specularSample * ks;
}