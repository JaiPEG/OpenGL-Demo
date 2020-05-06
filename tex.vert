#version 130

out vec3 position;	// view-space
out vec3 normal;	// view-space

void main()
{
	vec4 position_4 = gl_ModelViewMatrix * gl_Vertex;
	
	position = position_4.xyz / position_4.w;
	normal = gl_NormalMatrix * gl_Normal;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	
	gl_Position = gl_ProjectionMatrix * position_4;
}

/*
in int gl_VertexID;
in int gl_InstanceID;

out gl_PerVertex {
vec4 gl_Position;
float gl_PointSize;
float gl_ClipDistance[];
};
*/

// compatibility
/*
in vec4 gl_Color;
in vec4 gl_SecondaryColor;
in vec3 gl_Normal;
in vec4 gl_Vertex;
in vec4 gl_MultiTexCoord0;
in vec4 gl_MultiTexCoord1;
in vec4 gl_MultiTexCoord2;
in vec4 gl_MultiTexCoord3;
in vec4 gl_MultiTexCoord4;
in vec4 gl_MultiTexCoord5;
in vec4 gl_MultiTexCoord6;
in vec4 gl_MultiTexCoord7;
in float gl_FogCoord;
*/

//...

