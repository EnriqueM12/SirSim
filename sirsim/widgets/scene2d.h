#pragma once
#include "imgui.h"
#include "sirsim/simulation/basic_navierstokes.h"

#include <core/sirsim.h>
#include <core/graphics/shader.h>

namespace App {
class SceneViewer2D {
    sscore::Shader _grid_shader;
    unsigned int _frame_buffer;
    unsigned int _texture_id;
    unsigned int _grid_vbo;
    unsigned int _grid_vao;
    ImVec2 _size;

    unsigned int _sim_texture;

    void init();
    void terminate();
    void render_grid(float* data, int width, int height); 
    void initialize_grid();
    void delete_grid();

public:
    void DrawContents(float* data, int width, int height);
    void Gui();

    SceneViewer2D();
    ~SceneViewer2D();
};
};
