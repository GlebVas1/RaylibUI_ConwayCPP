#pragma once
#include "stdafx.h"

class UIElement {
    protected:
    size_t width = 0;
    size_t height = 0;
    size_t x_position;
    size_t y_position;
    public:
    virtual void Init() = 0;
    virtual void Draw() = 0;
    void SetDimensions(size_t x, size_t y);
    void SetPosition(size_t x, size_t y);
};