#version 330 core
out vec4 FragColor;

in vec3 norm;

void main()
{
    float shade = abs(dot(norm, normalize(vec3(1.0, 2.0, 3.0))));
    FragColor = vec4(shade * 1.0, shade * 1.0, shade * 1.0, 1.0);
} 
