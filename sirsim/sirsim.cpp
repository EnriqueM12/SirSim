#include "sirsim.h"
#include "sirsim/simulation/basic_navierstokes.h"
#include "sirsim/widgets/scene2d.h"


App::AppLayer::AppLayer(): _scene(), _sim(300, 150) {}

void App::AppLayer::init() {
    SetActive(true);
}

void App::AppLayer::gui_render() {
    ImGui::DockSpaceOverViewport();
    _scene.Gui();
    
    ImGui::Begin("Simulation Parameters");
    BasicNavierStokes::SimParameters& params = _sim.GetParameters();
    
    ImGui::DragInt("Iterations", &params.iters, 1.0, 1, 64);
    ImGui::DragFloat("Over Correction", &params.oc, 0.01, 1.0, 2.0);
    ImGui::DragFloat("Scale", &params.res, 1.0, 0.1, 1000);
    ImGui::DragFloat("Simulation Speed", &params.speed, 0.05, 0.1, 5.0);
    ImGui::End();
}

void App::AppLayer::on_render() {
    _scene.DrawContents(_sim.GetDensity(), _sim.GetWidth(), _sim.GetHeight());
}

void App::AppLayer::update() {
    _sim.UpdateFrame(sscore::App::GetInstance().GetDeltaTime());
}
