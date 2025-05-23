#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aNormal;
out vec3 ourColor;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

//uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//gl_Position = projection * view * model * vec4(aPos, 1.0);
	gl_Position = projection * view * model * vec4(aPos, 1.0f); // Needs a 4 element vector, so we take the 3 element one and add an element
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
}