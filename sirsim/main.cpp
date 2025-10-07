#include "sirsim/scene2d.h"
#include <core/sirsim.h>

namespace App {

class AppLayer : public sscore::Layer {
public:
    AppLayer();

    void init();
    void gui_render();
};

};

int main(int argc, char** argv) {
    sscore::AppConfig config;
    config.window_width = 1024;
    config.window_height = 780;
    config.window_title = "Hello World";
    config.window_maximized = false;

    sscore::App sirsim(config);

    sirsim.PushLayer<App::AppLayer>();
    sirsim.PushLayer<App::SceneViewer2D>();
    sirsim.Run();
}
