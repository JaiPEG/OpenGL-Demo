#version 130

in vec4 vertex;

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
}