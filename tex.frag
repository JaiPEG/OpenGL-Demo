#version 130

uniform sampler2D texture_diffuse;

in vec3 position;	// view-space, interpolated
in vec3 normal;		// view-space, interpolated

void main()
{
	// was interpolated by rasterizer but not normalized
	vec3 normal_nrm = normalize(normal);

	vec3 lightToFrag = position - gl_LightSource[0].position.xyz; // w doesn't matter

	float distance = length(lightToFrag);

	float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation +
							   gl_LightSource[0].linearAttenuation * distance +
							   gl_LightSource[0].quadraticAttenuation * distance * distance);

	vec3 light_incidence = normalize(lightToFrag);
	vec3 light_reflection = reflect(light_incidence, normal_nrm);
	vec3 eye = normalize(-position);

	float luminance = max(dot(-light_incidence, normal_nrm), 0.0);
	float highlight = pow(max(dot(light_reflection, eye), 0.0), gl_FrontMaterial.shininess);

	vec4 lighting = attenuation * (gl_FrontMaterial.ambient * gl_LightSource[0].ambient +
								   gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse * luminance  +
								   gl_FrontMaterial.specular * gl_LightSource[0].specular * highlight);

	gl_FragColor = (lighting * texture(texture_diffuse, gl_TexCoord[0].st)) + gl_FrontMaterial.emission;
	//gl_FragColor = lighting;
}

/*
in vec4 gl_FragCoord;
in bool gl_FrontFacing;
in float gl_ClipDistance[];
in vec2 gl_PointCoord;
in int gl_PrimitiveID;
in int gl_SampleID;
in vec2 gl_SamplePosition;
in int gl_SampleMaskIn[];
in int gl_Layer;
in int gl_ViewportIndex;
out float gl_FragDepth;
out int gl_SampleMask[];
*/