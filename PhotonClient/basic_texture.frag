#version 330 core
in vec2 texCoord;
in vec3 normal_frag;
in vec3 current_pos;
in vec3 lightPos;
in vec3 FragPos;

out vec4 FragColor;

uniform vec4 ObjectColor;
uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 camPos;

void main()
{
   //ambient
   float ambient_intensity = 0.7;
   vec3 ambient = ambient_intensity * lightColor.xyz;

   //diffuse
   vec3 normal = normalize(normal_frag);
   vec3 lightDirection = normalize(lightPosition - FragPos);
   float diff = max(dot(normal, lightDirection),0);
   vec3 diffuse = diff * lightColor.xyz;

   //specular light
   float specular_strength = 0.5f;
   vec3 view_dir = normalize(camPos - FragPos);
   vec3 reflection_dir = reflect(-lightDirection, normal);
   float spec_amount = pow(max(dot(view_dir, reflection_dir), 0), 32);
   vec3 specular = spec_amount * specular_strength * lightColor.xyz;

   vec3 result = (ambient + diffuse + specular) * ObjectColor.xyz * texture(tex0, texCoord).xyz;
   FragColor = vec4(result, 1.0);
}