#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_in;
layout (location = 3) in vec3 aNormal;

uniform mat4 model;
uniform mat4 camMatrix;
uniform mat4 view;
uniform vec3 lightPosition;

out vec2 texCoord;
out vec3 normal_frag;
out vec3 current_pos;
out vec3 lightPos;
out vec3 FragPos;

void main()
{
   current_pos = vec3(model * vec4(aPos, 1.0f));
   gl_Position = camMatrix * model * vec4(aPos, 1.0);
   FragPos = vec3(view * model * vec4(aPos, 1.0));
   texCoord = tex_in;
   normal_frag = mat3(transpose(inverse(view * model))) * aNormal;
   lightPos = vec3(view * vec4(lightPosition, 1.0));
   //lightPos = lightPosition;
}