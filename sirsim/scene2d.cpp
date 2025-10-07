#include "scene2d.h"

#include <glad/glad.h>
#include <imgui.h>

// 
// SceneViewer2D
// Constructor
//

App::SceneViewer2D::SceneViewer2D(): _sim(500, 200) {}
App::SceneViewer2D::~SceneViewer2D() {}

// 
// SceneViewer2D
// Layer Methods
//

void App::SceneViewer2D::init() {
    SetActive(true);

    initialize_grid();

    glCreateFramebuffers(1, &_frame_buffer);
    glGenTextures(1, &_texture_id);

    glBindTexture(GL_TEXTURE_2D, _texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void App::SceneViewer2D::gui_render() {

    ImGui::Begin("2D Viewer");
    _size = ImGui::GetContentRegionAvail();
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    ImGui::Image(_texture_id, _size, ImVec2(0.0, 1.0), ImVec2(1.0, 0.0));
    ImGui::End();
}

void App::SceneViewer2D::on_render() {
    
    glBindFramebuffer(GL_FRAMEBUFFER, _frame_buffer);
    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int) _size.x, (int) _size.y,
            0, GL_RGB, GL_UNSIGNED_BYTE, nullptr); 
    glViewport(0, 0, (int) _size.x, (int) _size.y);

    glClearColor(0.0, 1.0, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 0.0, 0.5, 1.0);

    render_grid();

    glBindTexture(GL_TEXTURE_2D, _texture_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, _texture_id, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void App::SceneViewer2D::update() {
    _sim.UpdateFrame(sscore::App::GetInstance().GetDeltaTime());
}

void App::SceneViewer2D::terminate() {
    glDeleteTextures(1, &_texture_id);
    glDeleteFramebuffers(1, &_frame_buffer);

    delete_grid();
}

// 
// SceneViewer2D
// private methods
//

void App::SceneViewer2D::initialize_grid() {
    glGenBuffers(1, &_grid_vbo);
    glGenVertexArrays(1, &_grid_vao);

    glBindVertexArray(_grid_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _grid_vbo);

    char _verts[] = {0, 1, 2, 3};
    glBufferData(GL_ARRAY_BUFFER, sizeof(_verts), _verts, GL_STATIC_DRAW);

    glVertexAttribIPointer(0, 1, GL_BYTE, sizeof(char), (void*) 0);
    glEnableVertexAttribArray(0);

    _grid_shader.AttachShader("grid");

    glGenTextures(1, &_sim_texture);
    glBindTexture(GL_TEXTURE_2D, _sim_texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void App::SceneViewer2D::render_grid() {
    glBindVertexArray(_grid_vao);
    _grid_shader.Use();
    glUniform2f(0, _size.x, _size.y);
    glUniform2f(1, (float) _sim.GetWidth(), (float) _sim.GetHeight());

    glBindTexture(GL_TEXTURE_2D, _sim_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, _sim.GetWidth(),
            _sim.GetHeight(), 0, GL_RED, GL_FLOAT, _sim.GetDensity());
    glGenerateMipmap(GL_TEXTURE_2D);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void App::SceneViewer2D::delete_grid() {
    glDeleteBuffers(1, &_grid_vbo);
    glDeleteVertexArrays(1, &_grid_vao);
}
