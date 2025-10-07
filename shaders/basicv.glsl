#version 330 core

layout (location=0) in vec2 _aPos;
out vec2 _oPos;

void main() {

	gl_Position = vec4(_aPos, 0.0, 1.0);
  	_oPos = _aPos;
}
