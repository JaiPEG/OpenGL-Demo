uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;

in vec3 position;
in vec3 toLight_u;
in vec3 toEye_u;
in vec2 texCoord_diffuse;
in vec2 texCoord_normal;

void main()
{
	vec3 toLight = normalize(toLight_u);
	vec3 toEye = normalize(toEye_u);

	// float dist = distance(vec3(gl_ModelViewMatrix * gl_LightSource[0].position), position);
	float dist = distance(gl_LightSource[0].position.xyz, position); // ???
	float attenuation = 1.0 / (gl_LightSource[0].constantAttenuation +
							   gl_LightSource[0].linearAttenuation * dist +
							   gl_LightSource[0].quadraticAttenuation * dist * dist);

	vec4 base = texture(texture_diffuse, texCoord_diffuse);
	vec3 normal = texture(texture_normal, texCoord_normal).xyz * 2.0 - 1.0;

	vec3 incidence = -toLight;
	vec3 reflection = reflect(incidence, normal);

	float luminance = max(dot(normal, toLight), 0.0);
	float highlight = pow(max(dot(reflection, toEye), 0.0), gl_FrontMaterial.shininess);

	vec4 ambient = gl_LightSource[0].ambient * gl_FrontMaterial.ambient;
	vec4 diffuse = gl_LightSource[0].diffuse * gl_FrontMaterial.diffuse * luminance;
	vec4 specular = gl_LightSource[0].specular * gl_FrontMaterial.specular * highlight;
	vec4 emission = gl_FrontMaterial.emission;

	gl_FragColor = attenuation * (ambient * base +
								  diffuse * base +
								  specular +
								  emission);

	//gl_FragColor = vec4(toLight, 1.0);
	//gl_FragColor = vec4(toEye, 1.0);
	//gl_FragColor = vec4(normal, 1.0);
	//gl_FragColor = vec4(incidence, 1.0);
	//gl_FragColor = vec4(reflection, 1.0);
	gl_FragColor = vec4(luminance, luminance, luminance, 1.0);
	//gl_FragColor = attenuation * vec4(highlight, highlight, highlight, 1.0);
	//gl_FragColor = vec4(luminance, highlight, 0.0, 1.0);
	//gl_FragColor = vec4(attenuation, attenuation, attenuation, 1.0);
}