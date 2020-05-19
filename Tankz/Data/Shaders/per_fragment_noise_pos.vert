#version 150



in vec3 position;
in vec3 normal;
in vec2 texCoord; 

    

uniform mat4 PVM; 
uniform mat4 V;
uniform mat4 M;
uniform mat4 NM;  

uniform float time;

out vec3 normal_v;
out vec3 frag_v;
out float time_v;

out vec3 normal_m;
out vec3 frag_m;
out mat4 v;
out mat4 m;


out vec4 color;

out vec2 texCoord_v;


float rand2D( vec2 co){
    return fract(sin(dot(co.xy ,vec2(18.6512,78.233))) * 43758.5453);
}
float rand3D( vec3 co){
    return fract(sin(dot(co.xyz ,vec3(12.9898,78.233,144.7272))) * 43758.5453);
}
float simple_interpolate(float a, float b,  float x)
{
   return a + smoothstep(0.0,1.0,x) * (b-a);
}
float interpolatedNoise3D(float x, float y, float z)
{
    float integer_x = x - fract(x);
    float fractional_x = x - integer_x;

    float integer_y = y - fract(y);
    float fractional_y = y - integer_y;

    float integer_z = z - fract(z);
    float fractional_z = z - integer_z;

    float v1 = rand3D(vec3(integer_x, integer_y, integer_z));
    float v2 = rand3D(vec3(integer_x+1.0, integer_y, integer_z));
    float v3 = rand3D(vec3(integer_x, integer_y+1.0, integer_z));
    float v4 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z));

    float v5 = rand3D(vec3(integer_x, integer_y, integer_z+1.0));
    float v6 = rand3D(vec3(integer_x+1.0, integer_y, integer_z+1.0));
    float v7 = rand3D(vec3(integer_x, integer_y+1.0, integer_z+1.0));
    float v8 = rand3D(vec3(integer_x+1.0, integer_y +1.0, integer_z+1.0));

    float i1 = simple_interpolate(v1,v5, fractional_z);
    float i2 = simple_interpolate(v2,v6, fractional_z);
    float i3 = simple_interpolate(v3,v7, fractional_z);
    float i4 = simple_interpolate(v4,v8, fractional_z);

    float ii1 = simple_interpolate(i1,i2,fractional_x);
    float ii2 = simple_interpolate(i3,i4,fractional_x);

    return simple_interpolate(ii1 , ii2 , fractional_y);
}

float Noise3D(vec3 coord, float wavelength)
{
   return interpolatedNoise3D(coord.x/wavelength, coord.y/wavelength, coord.z/wavelength);
}

void main() {
  float npos = -Noise3D((-position.xzx * sin(time/5) * 30.0)/40.0, 0.1)/3.0 + Noise3D((position.xzx* sin(time*8) * 20.0)/40.0, 1.4)/2.0 + Noise3D((position.xzx* sin(time)*30.0)/40.0, 0.8);
  vec3 sphere = (0.3*npos)*normalize(position - vec3(0.0,0.0,0.0)) + vec3(0.0,0.0,0.0);
  vec3 nposition = position + sphere;
  gl_Position = PVM * vec4(nposition, 1.0);
  
  frag_v = (V * M * vec4(nposition, 1.0)).xyz;
  normal_v = normalize((V * NM * vec4(normal, 0.0)).xyz);
  v = V;
  m = M;
  frag_m = (M * vec4(nposition, 1.0)).xyz;
  normal_m = (NM * vec4(normal, 0.0)).xyz;

  time_v = time;
  texCoord_v = texCoord;
}
