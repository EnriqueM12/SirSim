#include "basic_navierstokes.h"

App::BasicNavierStokes::BasicNavierStokes(int w, int h) {
    _width = w, _height = h;
    _h_vels = new float[(w+1)*h];
    _v_vels = new float[(h+1)*w];
    _dg1 = new float[w*h];
    _dg2 = new float[w*h];
    _iterations = 12;
    _over_correction = 1.0;

    for (int j = 0; j < h; ++j) 
        for (int i = 0; i < w+1; ++i) 
            _h_vels[j*(w+1) + i] = get_random_vel();
    
    for (int j = 0; j < h+1; ++j) 
        for (int i = 0; i < w; ++i) 
            _v_vels[j*(w) + i] = get_random_vel();

    std::memset(_dg1, 0, sizeof(float) * w * h);
}

App::BasicNavierStokes::~BasicNavierStokes() {
    delete [] _h_vels;
    delete [] _v_vels;
    delete [] _dg1;
    delete [] _dg2; 
}

void App::BasicNavierStokes::UpdateFrame(float dt) {
    for (int j = 0; j < _height; ++j )
        for (int i = 0; i < _width; ++i)
            external_forces(j, i, dt);
        
    for (int l = 0; l < _iterations; ++l ) {
        for (int j = 0; j < _height; ++j) {
            for (int i = 0; i < _width; ++i) {
                float div = divergence(j, i);
                incompress(div * _over_correction, j, i);
            }
        }
    }

    for (int j = 0; j < _height; ++j) 
        for (int i = 0; i < _width; ++i) 
            calculate_density(j, i);

    std::swap(_dg1, _dg2);
}

void App::BasicNavierStokes::external_forces(int column, int row, float dt) {
    return;
}

float App::BasicNavierStokes::divergence(int column, int row) {
    return -1.0;
}

float App::BasicNavierStokes::incompress(float divergence, int column, int row) {
    return -1.0;
}

void App::BasicNavierStokes::calculate_density(int column, int row) {
    return;
}

float App::BasicNavierStokes::get_random_vel() {
    return -1.0;
}
