#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_element_class.h"
#include "stdafx.h"
#include "ui_mouse_state.h"

class UICheckbox : public UIElement, UIMouseState {
    private:
    bool* value_;
    int x_pos_ = 0;
    int y_pos_ = 6;
    int box_size_ = 20;
    int check_size_ = 5;

    float box_roundness_ = 0.2f;
    float check_roundness_ = 0.7f;
    std::string text_;
     
    public:
    void Draw() override;
    void Update();
    UICheckbox();
    UICheckbox(int x, int y, bool* val_ptr, const std::string& text);
    void SetBoolPtr(bool* ptr);

};
