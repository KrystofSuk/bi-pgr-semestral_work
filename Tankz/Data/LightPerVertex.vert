#version 140

in vec3 position;
uniform vec4 input_color;

out vec4 color;

void main() {
  gl_Position = vec4(position+vec3(0,0,0), 1.0f);
  color = input_color;
}
