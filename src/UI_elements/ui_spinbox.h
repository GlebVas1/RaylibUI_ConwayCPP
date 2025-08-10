#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_mouse_state.h" 
#include "ui_element_class.h"
#include "ui_text_fromat.h"

template <typename T>
class UISpinBox : public UIElement, UIMouseState, UITextFormat<T> {
    private:
    T value_ = 0;
    T step_ = 0;
    T min_value_ = 0;
    T max_value_ = 1;

    std::function<void(T)> binding_;

    static const float roundness_;

    static const int buttons_width_ = 12;

    MouseState left_state_;
    MouseState right_state_;

    public:

    UISpinBox();
    UISpinBox(int x, int y, std::function<void(T)> func, T step = 0.1f);

    void Update();
    void Draw() override;
    
    void NormalizeValue();

    void DecreaseValue();
    void IncreaseValue();

    void SetMaxValue(T val);
    void SetMinValue(T val);

    void SetStep(T val);

    T GetValue();
    void SetValue(T val);
};


#include "ui_spinbox.ipp"