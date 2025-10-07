#version 330 core

layout (location=0) in vec2 _aPos;

void main() {

	gl_Position = vec4(_aPos, 0.0, 1.0);
  
}
