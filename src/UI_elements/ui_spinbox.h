#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_mouse_state.h" 
#include "ui_element_class.h"
#include "ui_text_fromat.h"

template <typename T>
class UISpinBox : public UIElement, UIMouseState, UITextFormat<T> {
    private:
    T* value_;
    T step_ = 0;
    T min_value = 0;
    T max_value = 1;

    float roundness_ = 0.1;

    int buttons_width_ = 12;

    MouseState left_state_;
    MouseState right_state_;

    public:

    UISpinBox();
    UISpinBox(int x, int y, T* ptr, T step = 0.1f);

    void Update();
    void Draw() override;
    
    void SetValuePtr(T* ptr);
    void NormalizeValue();

    void DecreaseValue();
    void IncreaseValue();

    void SetMaxValue(T val);
    void SetMinValue(T val);

    void SetStep(T val);
};


#include "ui_spinbox.ipp"