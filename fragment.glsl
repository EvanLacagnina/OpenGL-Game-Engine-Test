#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
//uniform sampler2D texture2;
//float mix;

void main() //  
{
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1.0) * vec4(ourColor, 0.0); // round(TexCoord * 50) / 50)
	FragColor = texture(texture1, TexCoord); //* vec4(ourColor, 0.0);
}