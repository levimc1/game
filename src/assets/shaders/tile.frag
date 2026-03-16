#version 330 core
out vec4 FragColor;

in vec3 outColor;
in vec2 outUV;

void main() {
	uvec2 res = uvec2(6u, 7u); // FORDÍTOTT!
	vec2 tile = floor(outUV * res);
	FragColor = vec4(tile/res, 1.0, 1.0);
}

