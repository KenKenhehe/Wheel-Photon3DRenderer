#version 330 core
in vec2 vert_out_texcoord;
in vec3 vert_out_normal;
in vec3 vert_out_current_pos;
in vec3 vert_out_light_pos;
in vec3 vert_out_frag_pos;

out vec4 FragColor;

uniform vec4 objectColor;
uniform sampler2D texture_diffuse1;
uniform vec4 lightColor;
//uniform vec3 lightPosition;
uniform vec3 camPos;

void main()
{
    
}