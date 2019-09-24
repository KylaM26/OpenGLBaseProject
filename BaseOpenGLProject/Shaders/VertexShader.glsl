
#version 330
layout (location = 0) in vec3 pos;
out vec4 color;
uniform vec4 uPosition;
uniform mat4 uMat4x4;
uniform float uScale;
void main() {
	gl_Position = uMat4x4 * vec4(pos, 1.0f);
	color = vec4(clamp(pos, 0.0f, 1.0f), 1.f);
}