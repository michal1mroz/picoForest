#version 330 core
out vec4 FragColor;

in vec3 norm;
in vec3 fragPos;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform float ambientStrength = 0.1;
uniform float specularStrength = 0.5;
uniform int shininess = 32;

void main()
{
  vec3 normal = normalize(norm);
  vec3 ambient = ambientStrength * lightColor;
  vec3 lightDir = normalize(lightPos - fragPos);
  float diff = max(dot(normal, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 viewDir = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
  vec3 specular = specularStrength * spec * lightColor;

  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
} 
