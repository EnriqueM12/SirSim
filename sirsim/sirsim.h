#include <core/sirsim.h>
#include <imgui.h>

namespace App {

class AppLayer : public sscore::Layer {
public:
    AppLayer() {};

    void init() {
        SetActive(true);
    }

    void on_render() {
        std::cout << "Hello World" << std::endl;
        ImGui::DockSpaceOverViewport();
        ImGui::Begin("Hello World");
        ImGui::Text("This is some text");
        ImGui::End();
        ImGui::ShowDemoWindow();
    }
};

};
