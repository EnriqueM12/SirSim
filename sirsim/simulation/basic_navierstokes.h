#pragma once

namespace App {
struct BasicNavierStokes {
    float *_h_vels;
    float *_v_vels;
    bool *_h_boundary;
    bool *_v_boundary;

    float *_dg1;
    float *_dg2;

    int _width;
    int _height;
    int _iterations;

    float _over_correction;
    float _res;
    float _speed;

    void external_forces(int column, int row, float dt);
    float divergence(int column, int row);
    void decompress(float divergence, int column, int row);
    void calculate_density(int column, int row, float dt);
    float get_random_vel();
    float get_density(float x, float y);
    float get_density(int x, int y);
    bool is_mutable_h(int index);
    bool is_mutable_v(int index);
public: 
    BasicNavierStokes(int w, int h);
    ~BasicNavierStokes();
    
    void UpdateFrame(float dt);

    inline int GetWidth() { return _width; }
    inline int GetHeight() { return _height; }
    inline float* GetDensity() { return _dg1; }
};
}
