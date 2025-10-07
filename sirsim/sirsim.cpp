#include <core/sirsim.h>

#include "imgui.h"
#include "sirsim/scene2d.h"

namespace App {
class AppLayer : public sscore::Layer {
public:
    AppLayer();

    void init();
    void gui_render();
};
};

App::AppLayer::AppLayer() {
}

void App::AppLayer::init() {
    SetActive(true);
}

void App::AppLayer::gui_render() {
    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Another Window");
    ImGui::End();
}
