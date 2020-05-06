#version 440

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 4) uniform mat4 viewMatrix;
layout(location = 8) uniform mat4 projectionMatrix;
layout(location = 12) uniform mat4 modelViewMatrix;
layout(location = 16) uniform mat4 modelViewProjectionMatrix;
layout(location = 20) uniform mat3 normalMatrix;

layout(location = 24) uniform vec4 lightPosition; // view
layout(location = 25) uniform vec4 lightAmbient;
layout(location = 26) uniform vec4 lightDiffuse;
layout(location = 27) uniform vec4 lightSpecular;
layout(location = 28) uniform float lightAttenuationC;
layout(location = 29) uniform float lightAttenuationQ;
layout(location = 30) uniform float lightRadius;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;

in vec3 position;   // view
in vec3 toLight_u;  // tangent
in vec3 toEye_u;    // tangent
in vec2 texCoord_diffuse;
in vec2 texCoord_normal;

out vec4 fragColor;

void main()
{
	//*
    vec4 materialAmbient = vec4(0.5, 0.5, 0.5, 1.0);
    vec4 materialDiffuse = vec4(0.5, 0.5, 0.5, 1.0);
    vec4 materialSpecular = vec4(0.1, 0.1, 0.1, 1.0);
    vec4 materialEmission = vec4(0.0, 0.0, 0.0, 1.0);
    float materialShininess = 32.0;
    //*/
    
    vec3 toLight = normalize(toLight_u);
	vec3 toEye = normalize(toEye_u);

	float dist = distance(lightPosition.xyz, position);
	float attenuation = 1.0 / (lightAttenuationC + lightAttenuationQ * dist * dist);

	vec4 base = texture(texture_diffuse, texCoord_diffuse);
	vec3 normal = texture(texture_normal, texCoord_normal).xyz * 2.0 - 1.0;

	vec3 incidence = -toLight;
	vec3 reflection = reflect(incidence, normal);

	float luminance = max(dot(normal, toLight), 0.0);
	//float sigma = 0.0;
	//float lambert = max(dot(normal, toLight), 0.0);
	//float luminance = 1.0 - ((1.0 - lambert) * (1.0 - sigma));
	float highlight = pow(max(dot(reflection, toEye), 0.0), materialShininess);

	vec4 ambient = lightAmbient * materialAmbient * base;
	vec4 diffuse = lightDiffuse * materialDiffuse * luminance * base;
	vec4 specular = lightSpecular * materialSpecular * highlight;
	vec4 emission = materialEmission;
    
	fragColor = ambient + diffuse + specular + emission;
    fragColor *= attenuation;

	//fragColor = vec4(position, 1.0);
	//dist *= 0.1;
	//fragColor = vec4(dist, dist, dist, 1.0);
	//fragColor = vec4(toLight, 1.0);
	//fragColor = vec4(toEye, 1.0);
	//fragColor = vec4(normal, 1.0);
	//fragColor = vec4(incidence, 1.0);
	//fragColor = vec4(reflection, 1.0);
	//fragColor = attenuation * vec4(luminance, luminance, luminance, 1.0);
	//fragColor = attenuation * vec4(highlight, highlight, highlight, 1.0);
	//fragColor = attenuation * vec4(luminance, highlight, 0.0, 1.0);
	//fragColor = vec4(attenuation, attenuation, attenuation, 1.0);
}