#version 330 core
layout(location = 0) in vec3 Qpos;
layout(location = 1) in vec2 Ipos;
layout(location = 2) in vec3 Icolor; 

out vec3 outColor;

void main() {
    outColor = Icolor;
    gl_Position = Vec4(Qpos + Ipos, 1.0);
}