#version 140

in vec3 position;
uniform vec4 input_color;

uniform mat4 PVMmatrix; 

out vec4 color;

void main() {
  gl_Position = PVMmatrix * vec4(position, 1);
  color = input_color;
}
