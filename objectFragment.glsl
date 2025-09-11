#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

struct pointLight{
	vec3 pos;
	vec3 color;
	float radius;
};

struct dirLight{
	vec3 pos;
	float brightness;
	vec3 rot;
	vec3 color;
	vec3 dir;
	vec3 size;
	mat4 invRot;
};

struct Camera{
	vec3 pos;
};

uniform int numPointLights;
uniform int numDirLights;

layout (std140) uniform Lights
{
	pointLight pointLights[32];
	dirLight dirLights[32];
};

uniform Camera camera;

uniform sampler2D texture1;

uniform float specularStrength;
uniform float specularExp;
//uniform sampler2D texture2;
//float mix;

void main() //  
{
	float distance;
	float rad;
	float attenuation;
	vec4 ambientStrength = vec4(0.1f);
	vec3 norm;
	vec3 lightDir;
	vec3 cameraDir;
	vec3 reflectDir;
	vec3 fragPosObjSpace = vec3(0.0f);
	float diff;
	float spec;
	vec3 diffuse;
	FragColor = vec4(0.0f);
	norm = normalize(Normal);cameraDir = normalize(camera.pos - FragPos);
	//vec3 lightPos = vec3(2.0f, -1.0f, 1.0f);
	// FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1.0) * vec4(ourColor, 0.0); // round(TexCoord * 50) / 50)
	for(int i = 0; i < numPointLights; i++){
		distance = distance(pointLights[i].pos, FragPos); //float(int(distance(lightPos, FragPos) / 2)) * 2;

		rad = pointLights[i].radius / 0.315631605917;

		attenuation = (rad * rad) / (rad * rad + 4.4 * rad * distance + 76.4 * distance * distance);
		
		//FragColor = vec4(1.0f);

		//norm = normalize(Normal); // Normalizes our normal vector
		lightDir = normalize(pointLights[i].pos - FragPos); // Finds light direction vector based on light and fragment positions

		//diff = max(dot(norm, lightDir), 0.0) * attenuation; // Finds the difference in the normal vector and light direction vector - note that it uses the max() function so it doesn't go below zero

		//diff = (float(int(diff * 10))) / 10;

		diffuse = max(dot(norm, lightDir), 0.0) * attenuation * pointLights[i].color; // Finds the color by multiplying the light color and the difference between the vectors
		FragColor += vec4(diffuse, 1.0f);

		reflectDir = reflect(-lightDir, norm);

		spec = pow(max(dot(cameraDir, reflectDir), 0.0), specularExp);
		FragColor += vec4(max(spec * pointLights[i].color * specularStrength, 0.0f), 1.0f);

		//diffuse = max(dot(norm, -dirLights[i].dir), 0.0) * dirLights[i].color;
		//FragColor += vec4(diffuse, 1.0f);
		//FragColor = vec4(-dirLights[i].dir, 0.0);
	}

	for(int i = 0; i < numDirLights; i++){
		fragPosObjSpace = vec3(dirLights[i].invRot * (vec4(FragPos, 1.0f) - vec4(dirLights[i].pos, 1.0f)));
		//if(fragPosObjSpace.x < dirLights[i].size.x / 2.0f && fragPosObjSpace.x > -dirLights[i].size.x / 2.0f && fragPosObjSpace.y < dirLights[i].size.y && fragPosObjSpace.y > 0.0f && fragPosObjSpace.z < dirLights[i].size.z / 2.0f && fragPosObjSpace.z > -dirLights[i].size.z / 2.0f){
		if(fragPosObjSpace.x < dirLights[i].size.x / 2.0f && fragPosObjSpace.x > -dirLights[i].size.x / 2.0f && fragPosObjSpace.y < dirLights[i].size.y && fragPosObjSpace.y > 0.0f && fragPosObjSpace.z < dirLights[i].size.z / 2.0f && fragPosObjSpace.z > -dirLights[i].size.z / 2.0f){
			diffuse = max(dot(norm, -dirLights[i].dir), 0.0f) * dirLights[i].color * dirLights[i].brightness;
			FragColor += vec4(diffuse, 1.0f);
			
			spec = pow(max(dot(cameraDir, reflect(dirLights[i].dir, norm)), 0.0f), specularExp);
			FragColor += vec4(max(spec * dirLights[i].color * specularStrength * dirLights[i].brightness, 0.0f), 1.0f);
			//FragColor += vec4(vec3(spec) * dirLights[i].color * specularStrength, 1.0f);
			//FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
		}
		//FragColor = vec4(fragPosObjSpace, 1.0f);
		//FragColor = vec4(FragPos / 30.0f, 1.0f);
		//FragColor = vec4(dirLights[i].size, 1.0f);
		//FragColor = vec4(vec3(dirLights[i].size.y / 40), 1.0f);
		//FragColor = vec4(vec3(fragPosObjSpace.y / 40), 1.0f);
		//FragColor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
		//FragColor = (vec4(FragPos, 1.0f) - vec4(dirLights[i].pos, 1.0f));
		//FragColor = vec4(dirLights[i].pos, 1.0f);
		//FragColor = vec4(dirLights[i].brightness);
	}

	FragColor += ambientStrength;

	FragColor *= texture(texture1, TexCoord); // * min(FragColor, 1.0f); // Gets the final color of the fragment(pixel) by multiplying the diffuse color and texture color

	//FragColor = vec4(pointLights[5].color, 1.0f);
	
	//FragColor = vec4(vec3(length(cameraDir) / 50), 1.0f);
	//FragColor = vec4(cameraPos, 1.0f);
	//FragColor = vec4(2.0f);
	//FragColor = vec4(lightRadii[0] / 20);
}