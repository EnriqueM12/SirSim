#pragma once
#include "core/layer.h"

class GLFWwindow;
class ImGuiContext;

//
// application
//
namespace sscore {
struct AppConfig {
    int window_width;
    int window_height;
    std::string window_title;
    bool window_maximized;
};

class App {
private:
    friend class Layer;
    static App* _instance;

    std::vector<Layer*> _layers;

    GLFWwindow* _main_window;
    ImGuiContext* _main_context;

    template <typename T>
    void swap_layer(int i);
public:
    App(const AppConfig& config);
    ~App();

    template<typename T>
    int PushLayer();
    void Run();
};
}; 

//
// template implementations
//
template<typename T>
int sscore::App::PushLayer() {
    if (!std::is_base_of<Layer, T>())
        throw std::runtime_error("ERROR layer must inherit sscore::Layer");

    _layers.push_back(new T());
    int index = _layers.size()-1;
    _layers[index]->_index = index;
    return index;
}

template<typename T>
void sscore::Layer::SwapLayer() {
    App::_instance->swap_layer<T>(_index);
}

template<typename T>
void sscore::App::swap_layer(int i) {
    // TODO: 
}

