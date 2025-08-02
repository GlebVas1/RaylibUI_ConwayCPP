#pragma once
#include "raylib.h"
#include "ui_element_class.h"
#include "stdafx.h"
#include "ui_mouse_state.h"

class UICheckbox : public UIElement, UIMouseState {
    private:
    bool* value_;
    std::string text_;
    public:
    void Draw() override;
    void Update();
    UICheckbox();
    UICheckbox(int x, int y, bool* val, const std::string& text);

};
