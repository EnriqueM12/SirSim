#version 330 core

in vec2 _oPos;
out vec4 color;

void main() {
    color = vec4(abs(_oPos), 0.2, 1.0);
}
