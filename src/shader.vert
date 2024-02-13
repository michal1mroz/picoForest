#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;

out vec3 norm;

uniform mat4 projection;

void main() {
    norm = aNorm;

    vec3 cameraPos = vec3(2, 2, -7.0);
    vec3 pos = vec3(aPos.x - cameraPos.x, aPos.y - cameraPos.y, aPos.z - cameraPos.z);
    gl_Position = projection * vec4(pos.x, pos.y, -pos.z, 1.0);
}