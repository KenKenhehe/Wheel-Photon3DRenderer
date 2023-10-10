#version 330 core
in vec2 vert_out_texcoord;
in vec3 vert_out_normal;
in vec3 vert_out_current_pos;
in vec3 vert_out_light_pos;
in vec3 vert_out_frag_pos;

out vec4 FragColor;

uniform vec4 Color;
uniform sampler2D tex0;
uniform vec4 lightColor;
//uniform vec3 lightPosition;
uniform vec3 camPos;

void main()
{
   float ambient_intensity = 0.2;
   vec3 normal = normalize(vert_out_normal);
   
   vec3 lightDirection = normalize(vert_out_light_pos - vert_out_frag_pos);

   float diffuse = max(dot(normal, lightDirection),0);

   float specular_light = 0.5f;
   vec3 view_dir = normalize(-vert_out_frag_pos);
   vec3 reflection_dir = (-lightDirection, normal);
   float spec_amount = pow(max(dot(view_dir, reflection_dir), 0), 8);
   float specular = spec_amount * specular_light;

   FragColor = (texture(tex0, vert_out_texcoord) + Color) * lightColor * (diffuse + ambient_intensity + specular);
}