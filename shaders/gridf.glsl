#version 330 core

in vec2 apos;
uniform vec2 size;
uniform vec2 texsize;
out vec4 acolor;
uniform sampler2D sim;

vec3 viridis(float t) {
  const vec3 c0 = vec3(0.277727, 0.005407, 0.334100);
  const vec3 c1 = vec3(0.105093, 1.404614, 1.384590);
  const vec3 c2 = vec3(-0.330862, 0.214848, 0.095095);
  const vec3 c3 = vec3(-4.634230, -5.799101, -19.332441);
  const vec3 c4 = vec3(6.228270, 14.179933, 56.690553);
  const vec3 c5 = vec3(4.776385, -13.745145, -65.353033);
  const vec3 c6 = vec3(-5.435456, 4.645853, 26.312435);

  return c0 + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * (c5 + t * c6)))));
}

void main() {
    vec2 normpos = apos + vec2(1.0, 1.0);
    normpos = normpos * 0.5;
    normpos = normpos * size;
    vec2 aapos = (apos * size ) / (size - vec2(40, 0.0));
    aapos.y *= size.y / (size.x - 40.0) * texsize.x / texsize.y;
    aapos *= 0.5;
    aapos += vec2(0.5, 0.5);
    if (0 <= aapos.x && aapos.x <= 1.0 && 0 <= aapos.y && aapos.y <= 1) {
        float weight = texture(sim, aapos).x;
        vec2 center = vec2(0.33, 0.0);
        aapos = (aapos - vec2(0, 0.5)) * vec2(1.0, texsize.y / texsize.x);
        if (length(aapos - center) <= 0.25 * 0.25) {
            acolor = vec4(0.9, 0.9, 0.8, 1.0);
        }
        else { 
            acolor = vec4(viridis(weight), 1.0);
        }
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
