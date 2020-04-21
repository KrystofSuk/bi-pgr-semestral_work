#version 150

uniform sampler2D texSampler;  // sampler for the texture access
in vec2 texCoord_v;     // fragment texture coordinates

in vec3 normal_v;
in vec3 frag_v;
in vec3 normal_m;
in vec3 frag_m;

struct Material{
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  float shininess;
  int diffTex;
};

struct Light_D {
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  float shininess;
};

struct Light_P {
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  float shininess;
  float constant;
  float linear;
  float quadratic;
};

struct Light_S{
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  vec3  dir;
  float shininess; 
  
  float cutOff;
  float outerCutOff;
  
  float constant;
  float linear;
  float quadratic;  
};

struct Fog{
  vec3 color;
  float inte;
  float ramp;
  float inte_h;
  float ramp_h;
  float amount;
};

uniform Light_D dir;
uniform Light_P[4] poi;
uniform Light_S[4] spo;

uniform Fog fog;

uniform float time;
uniform float dir_amou;
uniform int point;
uniform int spot;

uniform Material mat;

in vec4 color;
in mat4 v;

out vec4 result_color;

vec4 Direction_Light(){
    vec3 pos = (v * vec4(dir.pos, 0.0)).xyz;

    vec3 lightDir = normalize(pos);
    float diff = max(dot(normal_v, lightDir), 0.0);
    vec3 diffuse = dir.diffuse * diff;  

    vec3 viewDir = normalize(-frag_v);
    vec3 reflectDir = reflect(-lightDir, normal_v);  
    float spec = 0;
    if(mat.shininess > 0.0)
       spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = dir.specular * spec; 
    

    return vec4(dir.ambient + mat.diffuse * diffuse + mat.specular * specular, 1.0);
}

vec4 Point_Light(int i){
    vec3 pos = (vec4(poi[i].pos, 0.0)).xyz - frag_m;

    vec3 lightDir = normalize(v * vec4(pos, 0.0)).xyz;
    float diff = max(dot(normalize(normal_v), lightDir), 0.0);
    vec3 diffuse = poi[i].diffuse * diff;  
    
    vec3 viewDir = normalize(normalize(-frag_v));
    vec3 reflectDir = reflect(-lightDir, normal_v);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = poi[i].specular * spec; 



    float distance = length(poi[i].pos - frag_m);
    float attenuation = 1.0 / (poi[i].constant + poi[i].linear * distance + poi[i].quadratic * (distance * distance));    

    return vec4(poi[i].ambient * attenuation + mat.diffuse * diffuse * attenuation + mat.specular * specular * attenuation , 1.0);
}

vec4 Spot_Light(int i){
     vec3 pos = (vec4(spo[i].pos, 0.0)).xyz - frag_m;

    vec3 lightDir = normalize(v * vec4(pos, 0.0)).xyz;
    float diff = max(dot(normalize(normal_v), lightDir), 0.0);
    vec3 diffuse = spo[i].diffuse * diff;  
    
    vec3 viewDir = normalize(normalize(-frag_v));
    vec3 reflectDir = reflect(-lightDir, normal_v);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
    vec3 specular = spo[i].specular * spec; 

    float theta = dot(lightDir, normalize(-(v * vec4(spo[i].dir, 0.0)).xyz)); 
    float epsilon = (spo[i].cutOff - spo[i].outerCutOff);
    float intensity = clamp((theta - spo[i].outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    

    float distance = length(spo[i].pos - frag_m);
    float attenuation = 1.0 / (spo[i].constant + spo[i].linear * distance + spo[i].quadratic * (distance * distance));    

    return vec4(spo[i].ambient * attenuation + mat.diffuse * diffuse * attenuation + mat.specular * specular * attenuation, 1.0);
}

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

vec4 CalculateFog(vec4 color){
    float fogFactor = 1.0;
    float d = length(frag_v);
    fogFactor = exp(-pow(d*fog.inte, fog.ramp));

    fogFactor = clamp(fogFactor, 0.0, 1.0);

    float fogCoef = -Noise3D((-frag_m.xzx + time*1)/40.0, 0.1)/3.0 + Noise3D((frag_m.xzx- time*3)/40.0, 1.4)/2.0 + Noise3D((frag_m.xzx + time/4.0 - time/5.0)/40.0, 0.8)/1.0;
    
    float heightCoef = pow((-frag_m.y - 1 )/fog.inte_h, fog.ramp_h); 
    heightCoef = clamp(heightCoef*fogCoef*fog.amount, 0.0, 1.0);

    vec4 fog_col = mix(vec4(fog.color, 1.0), color, fogFactor);
    fog_col = mix(fog_col, vec4(fog.color, 1.0), heightCoef);

    return fog_col;
}

void main() {
    
    vec4 col = vec4(0.0, 0.0, 0.0, 0.0);
    for(int i = 0; i < point; ++i){
        col += Point_Light(i);
    }
    for(int i = 0; i < spot; ++i){
        col += Spot_Light(i);
    }
    col += Direction_Light() * dir_amou;

    col += vec4(mat.ambient,1.0);

    col = CalculateFog(col);
    

    if(mat.diffTex == 1){
        result_color = texture(texSampler, texCoord_v) * col;
    }
    else{
        result_color = col;
    }
}
