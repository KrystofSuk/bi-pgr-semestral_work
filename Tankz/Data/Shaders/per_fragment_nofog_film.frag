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

void main() {
    
    vec4 col = vec4(0.0, 0.0, 0.0, 0.0);
    for(int i = 0; i < point; ++i){
        col += Point_Light(i);
        col = clamp(col, 0.0, 1.0);
    }
    for(int i = 0; i < spot; ++i){
        col += Spot_Light(i);
        col = clamp(col, 0.0, 1.0);
    }
    //col += Direction_Light() * dir_amou;
    col = clamp(col, 0.0, 1.0);
    col += vec4(mat.ambient,1.0);
       

    if(mat.diffTex == 1){
        int frame = int(time*8);
        vec2 offset = vec2(1.0) / vec2(16);

        vec2 texCoordBase = texCoord_v / 16;
        vec2 texCoord = texCoordBase + vec2(frame % 16, 16 - (frame / 16)) * offset;

        result_color = texture(texSampler, texCoord) * col;
    }
    else{
        result_color = col;
    }
}
