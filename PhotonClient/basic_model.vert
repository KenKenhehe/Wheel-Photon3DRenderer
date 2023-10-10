#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texcoord;

uniform mat4 model;
uniform mat4 camMatrix;
uniform mat4 view;
uniform vec3 lightPosition;

out vec2 vert_out_texcoord;
out vec3 vert_out_normal;
out vec3 vert_out_current_pos;
out vec3 vert_out_light_pos;
out vec3 vert_out_frag_pos;

void main()
{
   vert_out_current_pos = vec3(model * vec4(in_pos, 1.0f));
   gl_Position = camMatrix * model * vec4(in_pos, 1.0);
   vert_out_frag_pos = vec3(view * model * vec4(in_pos, 1.0));
   vert_out_texcoord = in_texcoord;
   vert_out_normal = mat3(transpose(inverse(view * model))) * in_normal;
   vert_out_light_pos = vec3(view * vec4(lightPosition, 1.0));
   //lightPos = lightPosition;
}