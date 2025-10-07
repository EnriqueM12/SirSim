#include "core/sirsim.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

sscore::App* sscore::App::_instance = nullptr;

//
// application initialization
//
sscore::App::App(const AppConfig& config) {
    // checking that application is unique
    if (_instance) 
        throw std::runtime_error("Only one instance of the application can exist");
    _instance = this;

    // initializing glfw
    if (!glfwInit()) 
        throw std::runtime_error("ERROR failed to initizalize glfw");

    // creating glfw window
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    _main_window = glfwCreateWindow(config.window_width,
            config.window_height,
            config.window_title.c_str(),
            nullptr,
            nullptr);
    if (!_main_window) 
        throw std::runtime_error("ERROR failed to create glfw window");
    glfwMakeContextCurrent(_main_window);

    // initializing glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        throw std::runtime_error("ERROR failed to initialize glad");
    glViewport(0, 0, config.window_width, config.window_height);
    glClearColor(0.0, 1.0, 1.0, 1.0);

    // initializing imgui
    ImGui::CreateContext();
    auto& imgui_io = ImGui::GetIO();
    imgui_io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    imgui_io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui_ImplGlfw_InitForOpenGL(_main_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

sscore::App::~App() {
    glfwDestroyWindow(_main_window);
    glfwTerminate();

    for (auto& layer : _layers) 
        delete layer;

    _instance = nullptr;
}

void sscore::App::Run() {
    for (auto& layer : _layers)
        layer->init();

    while (!glfwWindowShouldClose(_main_window)) {
        // imgui and glfw pre
        glfwPollEvents();
        glfwMakeContextCurrent(_main_window);
        int width, height;
        glfwGetWindowSize(_main_window, &width, &height);
        glViewport(0, 0, width, height); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        for (auto& layer : _layers) {
            if (layer->_is_active) 
                layer->gui_render();
        }

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(_main_window);
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(_main_window);

        for (auto& layer : _layers) {
            if (layer->_is_active) 
                layer->on_render();
        }

        for (auto& layer : _layers) {
            if (layer->_is_active) 
                layer->update();
        }
    }
}
