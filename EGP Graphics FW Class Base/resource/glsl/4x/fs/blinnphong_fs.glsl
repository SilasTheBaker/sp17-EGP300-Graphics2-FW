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


//light data
const vec4 lightAmbientIntensity = vec4(0.4, 0.4, 0.4, 1);
const vec4 lightDiffuseIntensity  = vec4(.9, .9, .9, 1);
const vec4 lightSpecularIntensity  = vec4(1, 1, 1, 1);

//material data, play around with this later
const vec4 ambientReflectance = vec4(1, 1, 1, 1);
const vec4 diffuseReflectance = vec4(1, 1, 1, 1);
const vec4 specularReflectance = vec4(1, 1, 1, 1);
const float shininess = 80;


// ****
// target
layout (location = 0) out vec4 fragColor;

vec4 getDiffuse(in vec4 N, in vec4 L)
{
	//Lambertian reflection
	float diffuseTerm = clamp(dot(N,L), 0, 1);
	return diffuseReflectance * lightDiffuseIntensity * diffuseTerm;
}

vec4 getSpecular(in vec4 N, in vec4 L, in vec4 V)
{
	float specularTerm = 0;
	
	//If we can "see" the light
	if(dot(N, L) > 0)
	{
		vec4 H = normalize(L + V);
		specularTerm = pow(dot(N, H), shininess);
	}

	return specularReflectance * lightSpecularIntensity * specularTerm;
}

// shader function
void main()
{
	//Normalize Vectors
	vec4 L = normalize(data.lightVec);
	vec4 V = normalize(data.eyeVec);
	vec4 N = normalize(data.normal);

	//Get reflection stuff
	vec4 ambient = (ambientReflectance *  lightAmbientIntensity);
	vec4 diffuse = getDiffuse(N, L);
	vec4 specular = getSpecular(N, L, V);

	vec4 diffuseSample = texture(tex_dm, data.texcoord);
	vec4 specularSample = texture(tex_sm, data.texcoord);
	specular *= specularSample;
	fragColor = diffuseSample * (ambient + diffuse + specular);


//	//trying rim lighting with help from http://roxlu.com/2014/037/opengl-rim-shader
	float rimShadingContribution = 1 - max(dot(data.eyeVec, data.normal), 0.0);
	
	fragColor.a = 1; //Do I need to do this?
	fragColor.rgb += vec3(smoothstep(0.1, 1.0, rimShadingContribution)); 


 //****
	// this example: phong shading algorithm

	//Diffuse Coeficient, need normal and light vector
	//vec4 N = normalize(data.normal);
	//vec4 L = normalize(data.lightVec);
	//float kd = dot(N, L);

	//specular coeficient
	//need view vector and reflected vector
	//vec4 V = normalize(data.eyeVec);
	//vec4 R = (kd + kd)*N - L;
	//float ks = dot(V, R);

	//calmp both and power specular
	//kd = max(0.0, kd);
	//ks = max(0.0, ks);
	//ks *= ks;
	//ks *= ks;
	//ks *= ks;
	//ks *= ks;

	// ****
	// output: phong
	//const vec4 AMB = vec4(0.0, 0.1, 0.2, 1.0);
	//fragColor = AMB + vec4(kd + ks);

	// ****
	// extra: apply textures as well
	//vec4 diffuseSample = texture(tex_dm, data.texcoord);
	//vec4 specularSample = texture(tex_sm, data.texcoord);
	//fragColor = AMB + diffuseSample * kd + specularSample * ks;
}