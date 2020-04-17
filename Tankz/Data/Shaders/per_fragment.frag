#version 150

uniform sampler2D texSampler;  // sampler for the texture access
in vec2 texCoord_v;     // fragment texture coordinates

in vec3 normal_v;
in vec3 frag_v;
in vec3 normal_m;
in vec3 frag_m;



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

uniform Light_D dir;
uniform Light_P[4] poi;
uniform Light_S[4] spo;


uniform int point;
uniform int spot;


in vec4 color;
out vec4 result_color;

vec4 Direction_Light(){
    vec3 normal_n = normalize(normal_v);

    vec3 L = normalize(dir.pos); 
    float diffuse = max(dot(L, normal_n), 0.0);

    vec3 V = normalize(-frag_v);
    vec3 R = reflect(-L, normal_n);  

    float specular = pow(max(dot(V, R), 0.0), dir.shininess);

    return vec4(dir.ambient + dir.diffuse * diffuse + dir.specular * specular, 1.0);
}

vec4 Point_Light(int i){
    vec3 normal_n = normalize(normal_m);
    vec3 lightDir = normalize(poi[i].pos - frag_m);
    float diff = max(dot(normal_n, lightDir), 0.0);
    vec3 diffuse = poi[i].diffuse * diff;  

    vec3 viewDir = normalize(normalize(-frag_v) - frag_m);
    vec3 reflectDir = reflect(-lightDir, normal_n);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), poi[i].shininess);
    vec3 specular = poi[i].specular * spec; 
    

    float distance = length(poi[i].pos - frag_m);
    float attenuation = 1.0 / (poi[i].constant + poi[i].linear * distance + poi[i].quadratic * (distance * distance));    

    return vec4(poi[i].ambient * attenuation + diffuse * attenuation + specular * attenuation, 1.0);
}

vec4 Spot_Light(int i){
    vec3 normal_n = normalize(normal_m);
    vec3 lightDir = normalize(spo[i].pos - frag_m);
    float diff = max(dot(normal_n, lightDir), 0.0);
    vec3 diffuse = spo[i].diffuse * diff;  

    vec3 viewDir = normalize(normalize(-frag_v) - frag_m);
    vec3 reflectDir = reflect(-lightDir, normal_n);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), spo[i].shininess);
    vec3 specular = spo[i].specular * spec; 

    float theta = dot(lightDir, normalize(-spo[i].dir)); 
    float epsilon = (spo[i].cutOff - spo[i].outerCutOff);
    float intensity = clamp((theta - spo[i].outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    

    float distance = length(spo[i].pos - frag_m);
    float attenuation = 1.0 / (spo[i].constant + spo[i].linear * distance + spo[i].quadratic * (distance * distance));    

    return vec4(spo[i].ambient * attenuation + diffuse * attenuation + specular * attenuation, 1.0);
}


void main() {
    
    vec4 col = vec4(0.0, 0.0, 0.0, 0.0);
    for(int i = 0; i < point; ++i){
        col += Point_Light(i);
    }
    for(int i = 0; i < spot; ++i){
        col += Spot_Light(i);
    }
    col += Direction_Light();
    result_color = col;//texture(texSampler, texCoord_v) * vec4(dir_v.ambient + dir_v.diffuse * diffuse + dir_v.specular * specular, 1.0);
}
