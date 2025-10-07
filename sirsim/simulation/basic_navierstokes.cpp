#include "basic_navierstokes.h"
#include <cstdlib>

App::BasicNavierStokes::BasicNavierStokes(int w, int h) {
    _width = w, _height = h;
    _h_vels = new float[(w+1)*h];
    _v_vels = new float[(h+1)*w];
    _h_boundary = new bool[(w+1)*h];
    _v_boundary = new bool[(h+1)*w];
    _dg1 = new float[w*h];
    _dg2 = new float[w*h];
    _iterations = 32;
    _over_correction = 1.9;
    _res = 200.0;
    _speed = 1;


    std::memset(_dg1, 0, sizeof(float) * w * h);
    std::memset(_dg2, 0, sizeof(float) * w * h);

    std::memset(_h_boundary, 0, sizeof(bool) * (w+1) * h);
    std::memset(_v_boundary, 0, sizeof(bool) * w * (h+1));

    std::memset(_h_vels, 0, sizeof(float) * (w+1) * h);
    std::memset(_v_vels, 0, sizeof(float) * w * (h+1));

    for (int i = 0; i < w; ++i) {
        _v_boundary[i] = 1;
        _v_boundary[_height * _width + i] = 1;
    }

    for (int j = 0; j < h; ++j) {
        _h_boundary[j*(w+1)] = 1;
        _h_boundary[j*(w+1) + w] = 1;
    }

    // for (int j = 0; j < h; ++j) {
    //     for (int i = 0; i < w; ++i) {
    //         int xx = i - 200;
    //         int yy = j - h / 2;
    //
    //         if (xx * xx + yy * yy <= 1000) {
    //             _h_boundary[j*(w+1) + i] = 1;
    //             _h_boundary[j*(w+1) + i + 1] = 1;
    //             _v_boundary[j*w + i] = 1;
    //             _v_boundary[(j+1)*w + i] = 1;
    //         }
    //     }
    // }

    for (int j = 0; j < h; ++j) 
        for (int i = 0; i < w+1; ++i) 
            if (is_mutable_h(j*(w+1) + i))
                _h_vels[j*(w+1) + i] = get_random_vel();
    
    for (int j = 0; j < h+1; ++j) 
        for (int i = 0; i < w; ++i) 
            if (is_mutable_v(j*(w) + i))
                _v_vels[j*(_width) + i] = get_random_vel();

    for (int j = 0; j < h; ++j) {
        _h_vels[j * (_width + 1)] = _speed;
        _h_vels[j * (_width + 1) + _width] = _speed;
    }
}

App::BasicNavierStokes::~BasicNavierStokes() {
    delete [] _h_vels;
    delete [] _v_vels;
    delete [] _h_boundary;
    delete [] _v_boundary;
    delete [] _dg1;
    delete [] _dg2; 
}

void App::BasicNavierStokes::UpdateFrame(float dt) {
    for (int j = 0; j < _height; ++j )
        for (int i = 0; i < _width; ++i)
            external_forces(i, j, dt);
        
    for (int l = 0; l < _iterations; ++l ) {
        for (int j = 0; j < _height; ++j) {
            for (int i = 0; i < _width; ++i) {
                float div = divergence(i, j);
                decompress(div * _over_correction, i, j);
            }
        }
    }

    for (int j = 0; j < _height; ++j) 
        for (int i = 0; i < _width; ++i) 
            calculate_density(i, j, dt);

    std::swap(_dg1, _dg2);
}

void App::BasicNavierStokes::external_forces(int column, int row, float dt) {
    // if (is_mutable_v(row*_width + column)) 
    //     _v_vels[row*_width + column] -= 9.81 * dt * 0.1;
}

float App::BasicNavierStokes::divergence(int column, int row) {
    float left = _h_vels[row*(_width+1) + column];
    float right = -_h_vels[row*(_width+1) + column + 1];
    float down = _v_vels[(row+1)*_width + column];
    float up = -_v_vels[row*_width + column];
    return left + right + down + up;
}

void App::BasicNavierStokes::decompress(float divergence, int column, int row) {
    int left = row*(_width+1) + column;
    int right = row*(_width+1) + column + 1;
    int down = (row+1)*_width + column;
    int up = row*_width + column;
    
    int _div = is_mutable_h(left) + is_mutable_h(right)
        + is_mutable_v(up) + is_mutable_v(down);

    if (_div == 0) 
        return;
    _h_vels[left] -= is_mutable_h(left) * divergence / _div;
    _h_vels[right] += is_mutable_h(right) * divergence / _div;
    _v_vels[up] += is_mutable_v(up) * divergence / _div;
    _v_vels[down] -= is_mutable_v(down) * divergence / _div;
}

void App::BasicNavierStokes::calculate_density(int column, int row, float dt) {
    // _dg2[row * _width + column] = _v_vels[row*(_width) + column] * 0.5 + 0.5;
    // return;

    float x_vel = (_h_vels[row*(_width+1) + column] + _h_vels[row*(_width+1) + column + 1]) * 0.5;
    float y_vel = (_v_vels[row*_width + column] + _v_vels[(row+1)*_width + column]) * 0.5;

    float past_x = column - x_vel * _res * dt;
    float past_y = row - y_vel * _res * dt;

    _dg2[row * _width + column] = get_density(past_x, past_y);
}

float App::BasicNavierStokes::get_random_vel() {
    auto distribution = std::uniform_real_distribution<float>(0.0, 1.0);
    std::mt19937 eng(rand());
    float out = distribution(eng);
    return out;
}

float App::BasicNavierStokes::get_density(float x, float y) {
    // float xx = x - 200;
    // float yy = y - y  *0.5;
    // if (xx * xx + yy * yy < 1000) {
    //     float len = sqrt(xx*xx + yy*yy);
    //     len = 100 - len;
    //     x += xx * len;
    //     y += yy * len;
    // }
    int left = std::floor(x);
    int down = std::floor(y);

    float x_ratio = x - left;
    float y_ratio = y - down;

    float ld = get_density(left, down);
    float rd = get_density(left+1, down);
    float lu = get_density(left, down+1);
    float ru = get_density(left+1, down+1);

    return (ru * (x_ratio) * (y_ratio) 
        + rd * (x_ratio) * (1.0 - y_ratio) 
        + lu * (1.0 - x_ratio) * (y_ratio)
        + ld * (1.0 - x_ratio) * (1-y_ratio));
}

float App::BasicNavierStokes::get_density(int x, int y) {
    if (0 <= x && x < _width && 0 <= y && y < _height) {
        return _dg1[y * _width + x];
    }
    if (x < 0) {
        return std::max(1.0 - 5.0 * std::abs((float) y - _height *0.5) / _height, 0.0) * rand() / RAND_MAX;
    }
    return 0.0;
}


bool App::BasicNavierStokes::is_mutable_h(int index) {
    return !_h_boundary[index];
}
bool App::BasicNavierStokes::is_mutable_v(int index) {
    return !_v_boundary[index];
}
