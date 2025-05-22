#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D texture1;
//uniform sampler2D texture2;
//float mix;

void main() //  
{
	//vec3 lightPos = vec3(2.0f, -1.0f, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1.0) * vec4(ourColor, 0.0); // round(TexCoord * 50) / 50)

	vec4 ambientStrength = vec4(0.2);
	
	//FragColor = vec4(1.0f);

	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-lightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	FragColor = texture(texture1, TexCoord) * (ambientStrength + vec4(diffuse, 1.0f)); // * vec4(lightColor, 1.0); //* vec4(ourColor, 0.0);
}