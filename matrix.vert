#version 440

uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;

in vec3 position;
in vec3 normal;

out vec3 normal_interpolated;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);

	mat3 normalMatrix = transpose(inverse(mat3(modelViewMatrix)));

	normal_interpolated = normalMatrix * normal;
}