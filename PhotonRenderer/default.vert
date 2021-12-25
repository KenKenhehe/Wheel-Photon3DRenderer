#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color_in;
layout (location = 2) in vec2 tex_in;
layout (location = 3) in vec3 normal_in;

out vec3 color;
out vec2 texCoord;
out vec3 current_pos;
out vec3 normal_frag;

uniform float scale;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   current_pos = vec3(model * vec4(aPos, 1.0f));
   gl_Position = camMatrix * vec4(current_pos, 1.0f);
   color = color_in;
   texCoord = tex_in;
   normal_frag = normal_in;
}