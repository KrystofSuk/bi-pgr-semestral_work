#version 150



in vec3 position;
in vec3 normal;
in vec2 texCoord; 

    

uniform mat4 PVM; 
uniform mat4 V;
uniform mat4 M;
uniform mat4 NM;  

out vec3 normal_v;
out vec3 frag_v;

out vec3 normal_m;
out vec3 frag_m;

out vec4 color;

out vec2 texCoord_v;

void main() {
  gl_Position = PVM * vec4(position, 1.0);
  
  frag_v = (V * M * vec4(position, 1.0)).xyz;
  normal_v = normalize((NM * vec4(normal, 0.0)).xyz);

  frag_m = (M * vec4(position, 1.0)).xyz;
  normal_m = (NM * vec4(normal, 0.0)).xyz;


  texCoord_v = texCoord;
}
