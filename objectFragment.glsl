#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform int numLights;
uniform vec3 lightColors[128];

uniform vec3 lightPos[128];

uniform sampler2D texture1;

uniform float lightRadii[128];
//uniform sampler2D texture2;
//float mix;

void main() //  
{
	float distance;
	float rad;
	float attenuation;
	vec4 ambientStrength;
	vec3 norm;
	vec3 lightDir;
	float diff;
	vec3 diffuse;
	FragColor = vec4(0.0f);
	//vec3 lightPos = vec3(2.0f, -1.0f, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1.0) * vec4(ourColor, 0.0); // round(TexCoord * 50) / 50)
	for(int i = 0; i < numLights; i++){
		distance = distance(lightPos[i], FragPos); //float(int(distance(lightPos, FragPos) / 2)) * 2;

		rad = lightRadii[i] / 0.315631605917;

		attenuation = (rad * rad) / (rad * rad + 4.4 * rad * distance + 76.4 * distance * distance);

		ambientStrength = vec4(0.1); // Ambient lighting strength
		
		//FragColor = vec4(1.0f);

		norm = normalize(Normal); // Normalizes our normal vector
		lightDir = normalize(lightPos[i] - FragPos); // Finds light direction vector based on light and fragment positions

		diff = max(dot(norm, lightDir), 0.0) * attenuation; // Finds the difference in the normal vector and light direction vector - note that it uses the max() function so it doesn't go below zero

		//diff = (float(int(diff * 10))) / 10;

		diffuse = diff * lightColors[i]; // Finds the color by multiplying the light color and the difference between the vectors
		FragColor += vec4(diffuse, 1.0f);
	}
	FragColor += ambientStrength;

	FragColor *= texture(texture1, TexCoord); // * min(FragColor, 1.0f); // Gets the final color of the fragment(pixel) by multiplying the diffuse color and texture color
	//FragColor = vec4(2.0f);
	//FragColor = vec4(lightRadii[0] / 20);
}