#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
uniform vec3 lightColor;

uniform sampler2D texture1;
void main()
{
    FragColor = texture(texture1, TexCoord) * vec4(lightColor, 1.0f);
    //FragColor = vec4(lightColor, 1.0f);
}