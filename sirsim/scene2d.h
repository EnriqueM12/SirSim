#pragma once
#include <core/sirsim.h>

namespace App {
class SceneViewer2D : sscore::Layer {
    unsigned int _frame_buffer;

    void init();
    void on_render();
    void update();
    void terminate();
};
};
