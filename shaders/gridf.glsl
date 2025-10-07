#version 330 core

in vec2 apos;
uniform vec2 size;
uniform vec2 texsize;
out vec4 acolor;
uniform sampler2D sim;

void main() {
    vec2 normpos = apos + vec2(1.0, 1.0);
    normpos = normpos * 0.5;
    normpos = normpos * size;
    vec2 aapos = (apos * size ) / (size - vec2(40, 0.0));
    aapos.y *= size.y / (size.x - 40.0) * texsize.x / texsize.y;
    aapos *= 0.5;
    aapos += vec2(0.5, 0.5);
    if (0 <= aapos.x && aapos.x <= 1.0 && 0 <= aapos.y && aapos.y <= 1) {
        acolor = texture(sim, aapos);
        return;
    }

    int xpos = int(normpos.x);
    int ypos = int(normpos.y);



    if (xpos % 40 < 1 || ypos % 40 < 1) {
        acolor = vec4(0.4, 0.4, 0.4, 1.0);
    }
    else {
        acolor = vec4(0.1, 0.1, 0.1, 1.0);
    }
}
