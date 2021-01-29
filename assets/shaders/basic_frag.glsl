#version 450 core

out vec4 color;

in vec3 vert_color;
in vec2 texCoords;
in vec3 camera_pos;
in vec3 light_pos;
in vec3 world_pos;
in vec3 vert_normal;
layout(binding=0) uniform sampler2D ourTexture;

void main()
{
	float specularStrength = 0.5;
	vec3 ambient = vec3(0.3,0.3,0.3);
	vec3 diffuseColor = vec3(1,1,1);
	
	vec3 viewDir = normalize(light_pos - vert_normal);
	vec3 lightDir = normalize(light_pos - world_pos);    
	vec3 reflectDir = reflect(-lightDir, vert_normal);  
	
	float diffuseFactor = max(dot(vert_normal,lightDir),0.0) * 0.5;

	vec3 diffuse = diffuseColor * diffuseFactor;
	
	float spec = 0.5;
	vec3 specular = specularStrength * spec * vec3(1,1,1);  

	vec3 outColor = texture(ourTexture,texCoords).xyz * (specular+diffuse+ambient);
	color = vec4(outColor,1.0f);
};