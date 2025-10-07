#pragma once

namespace sscore {

class App;

//
// layer
//
class Layer {
private:
    friend class App;

    bool _is_active;
    int _index;
protected:
    virtual ~Layer() {}

    virtual void init() { SetActive(true); }
    virtual void terimnate() {}
    virtual void update() {}
    virtual void gui_render() {}
    virtual void on_render() {}

public:
    inline void SetActive(bool active) { _is_active = active; }
    inline void ToggleActive() { _is_active = !_is_active; }
    inline bool GetActive() { return _is_active; }
    template<typename T>
    void SwapLayer();
};

};
