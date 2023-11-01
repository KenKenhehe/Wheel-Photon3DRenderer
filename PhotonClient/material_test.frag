#version 330 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec2 vert_out_texcoord;
in vec3 vert_out_normal;
in vec3 vert_out_current_pos;
in vec3 vert_out_light_pos;
in vec3 vert_out_frag_pos;

out vec4 FragColor;

uniform vec4 objectColor;
uniform sampler2D texture_diffuse1;
uniform vec3 lightColor;
uniform vec3 camPos;

uniform Material material;

void main()
{
    // ambient
    vec3 ambient = lightColor * material.ambient;

    //diffuse
    vec3 normal = normalize(vert_out_normal);
    vec3 lightDirection = normalize(vert_out_light_pos - vert_out_frag_pos);
    float diffuse_factor = max(dot(normal, lightDirection),0);

    vec3 diffuse = lightColor * (diffuse_factor * material.diffuse);

    //specular
    vec3 view_dir = normalize(camPos - vert_out_frag_pos);
    vec3 reflection_dir = reflect(-lightDirection, normal);
    float spec_amount = pow(max(dot(view_dir, reflection_dir), 0), material.shininess);
    vec3 specular = lightColor * (spec_amount * material.specular);  

    vec3 result = ambient + diffuse + specular;
    //FragColor = texture(texture_diffuse1, vert_out_texcoord) * vec4(result, 1.0);
    FragColor = vec4(result, 1.0);
}