#pragma once
#include "imgui.h"
#include "simulation/basic_navierstokes.h"

#include <core/sirsim.h>
#include <core/graphics/shader.h>

namespace App {
class SceneViewer2D : public sscore::Layer {
    sscore::Shader _grid_shader;
    unsigned int _frame_buffer;
    unsigned int _texture_id;
    unsigned int _grid_vbo;
    unsigned int _grid_vao;
    ImVec2 _size;

    BasicNavierStokes _sim;

    unsigned int _sim_texture;

    void init();
    void on_render();
    void update();
    void terminate();
    void gui_render();

    void initialize_grid();
    void render_grid(); 
    void delete_grid();

public:
    SceneViewer2D();
    ~SceneViewer2D();
};
};
