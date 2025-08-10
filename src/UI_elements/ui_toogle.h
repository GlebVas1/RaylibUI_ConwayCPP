#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"

class UIToggle : public UIElement, UIMouseState {
    private:
    bool value_= false;
    std::function<void(bool)> binding_;
    std::string text_;
    int slider_width_ = 15;
    int box_width_ = 35;
    int x_pos_ = 0;
    public:
    UIToggle();
    UIToggle(int x, int y, std::function<void(bool)>, const std::string& text);
    void Draw() override;
    void Update() override;

    bool GetValue();
    void SetValue(bool val);
};