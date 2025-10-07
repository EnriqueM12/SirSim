#pragma once

namespace sscore {
class Shader {
private:
    unsigned int _vert,
                 _frag, 
                 _prog;
    bool _is_ready;

    bool read_and_compile(int id, const std::string& source);
    void create(const std::string& source);
public:
    Shader(const std::string& source);
    Shader();
    ~Shader();

    void AttachShader(const std::string& source);
    void Use();
    inline bool IsOk() { return _is_ready; }
};
};
