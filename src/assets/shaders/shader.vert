#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 iPos;
layout (location = 2) in vec3 iColor;

out vec3 fragmentColor;

void main() {
    gl_Position = vec4(aPos.xy + iPos.xy, aPos.z, 1.0);
    /* gl_Position egy előredefinált Vec4 változó
     * Ez lesz a végső pozíciója a vertexnek!
     */
    fragmentColor = iColor;
}
