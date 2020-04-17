#version 330 core
out vec4 FragColor;

in vec3 texCoord_v;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, -texCoord_v);
}