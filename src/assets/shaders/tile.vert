#version 330 core
layout(location = 0) in vec3 Qpos;
layout(location = 1) in vec2 Quv;
layout(location = 2) in vec2 Ipos;
layout(location = 3) in uint ILayer;
layout(location = 4) in vec3 Icolor; 

uniform mat4 projection;

out vec3 outColor;
out vec2 outUV;

void main() {
    outColor = Icolor;
    outUV = Quv;
    float z = 0.9 - float(ILayer) * 0.001;
    gl_Position = projection * vec4(Qpos.xy + Ipos, z, 1.0);
}