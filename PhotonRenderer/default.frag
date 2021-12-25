#version 330 core
out vec4 FragColor;
in vec3 color;
in vec2 texCoord;
in vec3 current_pos;
in vec3 normal_frag;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 camPos;

void main()
{
   float ambient_intensity = 0.2;
   vec3 normal = normalize(normal_frag);
   vec3 lightDirection = normalize(lightPosition - current_pos);

   float diffuse = max(dot(normal, lightDirection),0);

   float specular_light = 0.5f;
   vec3 view_dir = normalize(camPos - current_pos);
   vec3 reflection_dir = (-lightDirection, normal);
   float spec_amount = pow(max(dot(view_dir, reflection_dir), 0), 8);
   float specular = spec_amount * specular_light;

   FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient_intensity + specular);
}
