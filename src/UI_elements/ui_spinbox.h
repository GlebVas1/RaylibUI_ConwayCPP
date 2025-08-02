#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"

class UISpinBox : public UIElement, public UIMouseState {
    private:
    float* value_;
    float step_ = 0.1f;
    float min_value = 0.0f;
    float max_value = 1.0f;

    float roundness_ = 0.1;

    int buttons_width_ = 15;

    MouseState left_state_;
    MouseState right_state_;

    public:

    UISpinBox();
    UISpinBox(int x, int y, float* ptr, float step = 0.1f);

    void Update();
    void Draw() override;
    
    void SetValuePtr(float* ptr);
    void NormalizeValue();

    void DecreaseValue();
    void IncreaseValue();

    void SetMaxValue(float val);
    void SetMinValue(float val);

    void SetStep(float val);
};