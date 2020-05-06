#version 440

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 4) uniform mat4 viewMatrix;
layout(location = 8) uniform mat4 projectionMatrix;
layout(location = 12) uniform mat4 modelViewMatrix;
layout(location = 16) uniform mat4 modelViewProjectionMatrix;
layout(location = 20) uniform mat3 normalMatrix;

layout(location = 24) uniform vec4 lightPosition; // view

in vec3 vertex;
in vec3 normal;
in vec3 tangent;
in vec2 texCoord;

out vec3 position;
out vec3 toLight_u;
out vec3 toEye_u;
out vec2 texCoord_diffuse;
out vec2 texCoord_normal;

void main()
{
    // position (view)
	position = vec3(modelViewMatrix * vec4(vertex, 1.0));
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);

	// texture coordinates
	texCoord_diffuse = texCoord; // textureMatrix?
	texCoord_normal = texCoord;

	// tangent space basis vectors (view)
	vec3 n = normalize(normalMatrix * normal);
	vec3 t = normalize(normalMatrix * tangent);
	vec3 b = cross(n, t);

	/*
		|t.x t.y t.z|
		|b.x b.y b.z|
		|n.x n.y n.z|
	*/

	mat3 tangentMatrix = mat3(t.x, b.x, n.x,
							  t.y, b.y, n.y,
							  t.z, b.z, n.z);

	// toLight vector (tangent)
	vec3 toLight_view = lightPosition.xyz - position;
	toLight_u = tangentMatrix * toLight_view;
	
	// toEye (tangent)
	vec3 toEye_view = -position;
	toEye_u = tangentMatrix * toEye_view;
}