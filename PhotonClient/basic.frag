#version 330 core
in vec2 texCoord;
in vec3 normal_frag;
in vec3 current_pos;
in vec3 lightPos;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 ReflectionColor;
//uniform vec4 SolidColor;
uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 camPos;

void main()
{
   //ambient
   float ambient_intensity = 0.2f;

   //diffuse
   vec3 normal = normalize(normal_frag);
   vec3 lightDirection = normalize(lightPosition - FragPos);
   float diffuse = max(dot(normal, lightDirection),0);

   //specular light
   float specular_light = 0.5f;
   vec3 view_dir = normalize(camPos - FragPos);
   vec3 reflection_dir = reflect(-lightDirection, normal);
   float spec_amount = pow(max(dot(view_dir, reflection_dir), 0), 8);
   float specular = spec_amount * specular_light;

   FragColor = (texture(tex0, texCoord) + ReflectionColor) * lightColor * (diffuse + ambient_intensity + specular); //+ SolidColor;
   //FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient_intensity + specular);
   //FragColor = vec4(1,1,1,1);
   //FragColor = texture(tex0, texCoord) * lightColor;
}
