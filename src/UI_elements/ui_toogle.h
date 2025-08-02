#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"

class UIToggle : public UIElement, UIMouseState {
    private:
    bool* value_;
    std::string text_;
    int slider_width_ = 10;
    int box_width_ = 30;
    int x_pos_ = 0;
    public:
    UIToggle();
    UIToggle(int x, int y, bool* ptr, const std::string& text);
    void Draw() override;
    void Update() override;
};