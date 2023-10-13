#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_normal;
layout (location = 2) in vec2 in_texcoord;

uniform mat4 model;
uniform mat4 camMatrix;
uniform mat4 view;
uniform vec3 lightPosition;

void main()
{
   gl_Position = camMatrix * model * vec4(in_pos, 1.0);
}