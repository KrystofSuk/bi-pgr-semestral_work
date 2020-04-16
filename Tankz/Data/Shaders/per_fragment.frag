#version 150

uniform sampler2D texSampler;  // sampler for the texture access
in vec2 texCoord_v;     // fragment texture coordinates

in vec3 normal_v;
in vec3 frag_v;

in DirectionLight{
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  vec3  pos;
  float  shininess;
} dir_v;

in vec4 color;
out vec4 result_color;

void main() {
    vec3 normal_n = normalize(normal_v);

    vec3 L = normalize(dir_v.pos); 
    float diffuse = max(dot(L, normal_n), 0.0);

    vec3 V = normalize(-frag_v);
    vec3 R = reflect(-L, normal_n);  

    float specular = pow(max(dot(V, R), 0.0), dir_v.shininess);
         

    result_color =  vec4(dir_v.ambient + dir_v.diffuse * diffuse + dir_v.specular * specular, 1.0);//texture(texSampler, texCoord_v) * vec4(dir_v.ambient + dir_v.diffuse * diffuse + dir_v.specular * specular, 1.0);
}
