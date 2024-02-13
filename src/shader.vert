#version 330 core

layout (location = 0) in vec3 aPos;

void main() {

    vec3 cameraPos = vec3(2.0, 2.0, -5.0);
    vec3 pos = vec3(aPos.x - cameraPos.x, aPos.y - cameraPos.y, aPos.z - cameraPos.z);
    gl_Position = vec4(pos.x / pos.z, pos.y / pos.z, 1.0, 1.0);
}