#version 330 core

in vec2 apos;
uniform vec2 size;
out vec4 acolor;

void main() {
    vec2 normpos = apos + vec2(1.0, 1.0);
    normpos = normpos * 0.5;
    normpos = normpos * size;

    int xpos = int(normpos.x);
    int ypos = int(normpos.y);

    if (xpos % 40 < 1 || ypos % 40 < 1) {
        acolor = vec4(0.4, 0.4, 0.4, 1.0);
    }
    else {
        acolor = vec4(0.1, 0.1, 0.1, 1.0);
    }
}
