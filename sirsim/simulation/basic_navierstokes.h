#pragma once

namespace App {
struct BasicNavierStokes {
    float *_h_vels;
    float *_v_vels;

    float *_dg1;
    float *_dg2;

    int _width;
    int _height;
    int _iterations;

    float _over_correction;

    void external_forces(int column, int row, float dt);
    float divergence(int column, int row);
    float incompress(float divergence, int column, int row);
    void calculate_density(int column, int row);
    float get_random_vel();
public: 
    BasicNavierStokes(int w, int h);
    ~BasicNavierStokes();
    
    void UpdateFrame(float dt);

    inline int GetWidth() { return _width; }
    inline int GetHeight() { return _height; }
    inline float* GetDensity() { return _dg1; }
};
}
