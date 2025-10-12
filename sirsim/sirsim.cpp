#include "sirsim.h"
#include "sirsim/widgets/scene2d.h"


App::AppLayer::AppLayer(): _scene(), _sim(300, 150) {}

void App::AppLayer::init() {
    SetActive(true);
}

void App::AppLayer::gui_render() {
    _scene.Gui();
}

void App::AppLayer::on_render() {
    _scene.DrawContents(_sim.GetDensity(), _sim.GetWidth(), _sim.GetHeight());
}

void App::AppLayer::update() {
    _sim.UpdateFrame(sscore::App::GetInstance().GetDeltaTime());
}
