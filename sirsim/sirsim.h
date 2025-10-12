#pragma once

#include <core/sirsim.h>
#include "sirsim/simulation/basic_navierstokes.h"
#include "sirsim/widgets/scene2d.h"

namespace App {
class AppLayer : public sscore::Layer {
private: 
    SceneViewer2D _scene;
    BasicNavierStokes _sim;

public:
    AppLayer();

private:
    void init();
    void on_render();
    void gui_render();
    void update();
};
};
