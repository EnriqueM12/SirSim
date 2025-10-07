#version 330 core

in vec2 pos;
uniform vec2 size;
out vec4 acolor;

void main() {
    vec2 normpos = pos + vec2(1.0, 1.0);
    normpos = normpos * 0.5;
    normpos = normpos * size;

    int xpos = int(normpos.x);
    int ypos = int(normpos.y);

    if (xpos % 20 < 3 && ypos % 20 < 3) {
        acolor = vec4(0.7, 0.7, 0.7, 1.0);
    }
    else {
        acolor = vec4(0.2, 0.2, 0.2, 1.0);
    }
}
