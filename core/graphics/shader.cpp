#include "shader.h"

#include <glad/glad.h>

//
// SHADER class
//
// constructors 
//
sscore::Shader::Shader(const std::string& source) {
    _is_ready = false;
    create(source);
}

sscore::Shader::~Shader() {
    if (_is_ready) {
        glDeleteProgram(_prog);
        glDeleteShader(_vert);
        glDeleteShader(_frag);
    }
}

//
// SHADER class
//
// public functions 
//
void sscore::Shader::Use() {
    if (_is_ready) 
        glUseProgram(_prog);
}

void sscore::Shader::AttachShader(const std::string& source) {
    if (_is_ready) {
        glDeleteProgram(_prog);
        glDeleteShader(_vert);
        glDeleteShader(_frag);
    }

    _is_ready = false;

    create(source);
}

//
// SHADER class
//
// private helper functions 
//

//
// create
//
void sscore::Shader::create(const std::string& source) {
    // initialize gl shader
    _vert = glCreateShader(GL_VERTEX_SHADER);
    _frag = glCreateShader(GL_FRAGMENT_SHADER);

    if (!read_and_compile(_vert, "shaders/" + source + "v.glsl")
        || ! read_and_compile(_frag, "shaders/" + source + "f.glsl")) {
        glDeleteShader(_vert);
        glDeleteShader(_frag);
        return;
    }

    // initialize gl program
    _prog = glCreateProgram();
    glAttachShader(_prog, _vert);
    glAttachShader(_prog, _frag);
    glLinkProgram(_prog);

    // error detection
    int status;
    glGetProgramiv(_prog, GL_LINK_STATUS, &status);
    if (!status) {
        char infolog[512];
        glGetProgramInfoLog(_prog, 512, &status, infolog);
        std::cout << "Failed to link program " << source << ":\n" 
            << infolog << std::endl;
        glDeleteProgram(_prog);
        glDeleteShader(_vert);
        glDeleteShader(_frag);
        return;
    }

    _is_ready = true;
}

//
// read_and_compile
//
bool sscore::Shader::read_and_compile(int id, const std::string& source) {
    //open file
    std::fstream file(source, std::ios_base::in);
    if (!file.is_open()) {
        std::cout << "Failed to open file " << source << std::endl;
        return false;
    }

    // load file contents into memory
    std::vector<char> ss;
    for (; !file.eof(); ss.push_back(file.get()));
    ss.push_back('\0');
    const char* ss_ptr = &ss[0];

    // compile shader
    glShaderSource(id, 1, &ss_ptr, nullptr);
    
    glCompileShader(id);

    // error detection
    int status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status) {
        char infolog[512];
        glGetShaderInfoLog(id, 512, &status, infolog);
        std::cout << "Failed to compile shader " << source <<
            ":\n" << infolog << std::endl;
        return false;
    }

    return true;
}
