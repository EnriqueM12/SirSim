#version 330 core

layout (location = 0) in int vindex;
out vec2 apos;

void main() {
    vec2 positions[4];
    positions[0] = vec2(-1.0, -1.0);
    positions[1] = vec2(-1.0, 1.0);
    positions[2] = vec2(1.0, -1.0);
    positions[3] = vec2(1.0, 1.0);

    gl_Position = vec4(positions[vindex], 0.0, 1.0);
    apos = positions[vindex];
}
