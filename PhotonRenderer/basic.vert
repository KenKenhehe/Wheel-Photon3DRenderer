#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_in;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 camMatrix;

out vec2 texCoord;
out vec3 normal_frag;
out vec3 current_pos;

void main()
{
   current_pos = vec3(model * vec4(aPos, 1.0f));
   gl_Position = (camMatrix != 0 ? (camMatrix * model * vec4(aPos, 1.0)) : vec4(aPos, 1.0));
   texCoord = tex_in;
   normal_frag = aNormal;
}