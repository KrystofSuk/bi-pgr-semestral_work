#version 150


struct Direction {
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  float shininess;
};

uniform Direction dir;

in vec3 position;
in vec3 normal;
in vec2 texCoord; 

    

uniform mat4 PVM; 
uniform mat4 V;
uniform mat4 M;
uniform mat4 NM;  

out vec3 normal_v;
out vec3 frag_v;

out vec4 color;

out DirectionLight{
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  float  shininess;
} dir_v;

out vec2 texCoord_v;

void main() {
  gl_Position = PVM * vec4(position, 1.0);
  
  frag_v = (V * M * vec4(position, 1.0)).xyz;
  normal_v = (V * NM * vec4(normal, 0.0)).xyz;


  texCoord_v = texCoord;


  dir_v.ambient = dir.ambient;
  dir_v.diffuse = dir.diffuse;
  dir_v.specular = dir.specular;
  dir_v.pos = dir.pos;
  dir_v.shininess = dir.shininess;
}
