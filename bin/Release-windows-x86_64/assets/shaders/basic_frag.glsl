#version 450 core

out vec4 color;

in vec3 vert_color;
in vec2 texCoords;
in vec3 light_pos;
in vec3 world_pos;
in vec3 vert_normal;

layout(binding=0) uniform sampler2D ourTexture;

void main()
{
	vec3 lightDir = normalize(light_pos - world_pos);    

    float diffuseFactor = max(dot(vert_normal,lightDir),0.0);

	vec3 outColor = texture(ourTexture,texCoords).xyz * diffuseFactor;
	color = vec4(outColor,1.0f);
};