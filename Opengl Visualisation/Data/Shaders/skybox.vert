#version 150

in vec3 position;   

uniform mat4 P; 
uniform mat4 V;

out vec3 texCoord_v;

void main()
{
    texCoord_v = position;
    gl_Position = P * V * vec4(position, 1.0);
}  
