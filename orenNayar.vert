#version 130

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
	vec4 position_4 = gl_ModelViewMatrix * vec4(vertex, 1.0);
	position = position_4.xyz;
	gl_Position = gl_ProjectionMatrix * position_4;

	// texture coordinates
	texCoord_diffuse = vec2(gl_TextureMatrix[0] * vec4(texCoord, 0.0, 0.0));
	texCoord_normal = texCoord_diffuse;

	// tangent space basis vectors (view)
	vec3 n = normalize(gl_NormalMatrix * normal);
	vec3 t = normalize(gl_NormalMatrix * tangent);
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
	// vec3 toLight_view = vec3(gl_ModelViewMatrix * gl_LightSource[0].position) - position;
	vec3 toLight_view = gl_LightSource[0].position.xyz - position; // ???
	toLight_u = tangentMatrix * toLight_view;
	
	// toEye (tangent)
	vec3 toEye_view = -position;
	toEye_u = tangentMatrix * toEye_view;
}