#include "ui_check_box.h"
#include "../UI_Tools/ui_tools.h"
#include "ui.h"
UICheckbox::UICheckbox() {

}

UICheckbox::UICheckbox(int x, int y, bool* val_ptr, const std::string& text) : UIElement(x, y, 60, 20) {
    text_ = text;
    value_ = val_ptr;
}

void UICheckbox::SetBoolPtr(bool* ptr) {
    value_ = ptr;
}

void UICheckbox::Draw() {
    if (value_ == nullptr) {
        return;
    }
    Color background_color;

    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        background_color = ui.ui_accent_color_1;
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = ui.ui_accent_color_3;
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = ui.ui_accent_color_3;
        break;
    }

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + x_pos_,
        GetAbsoluteYPosition() + y_pos_,
        box_size_,
        box_size_,
        2, 
        box_roundness_,
        background_color,
        ui.ui_line_color
    );

    if (*value_) {
        int offset = (box_size_ - check_size_) / 2;
        UITools::DrawRectangle(
            GetAbsoluteXPosition() + x_pos_ + offset,
            GetAbsoluteYPosition() + y_pos_ + offset,
            check_size_,
            check_size_,
            0, 
            check_roundness_,
            ui.ui_text_dark,
            ui.ui_line_color
        );
    }

    /* DrawText(
        text_.c_str(), 
        GetAbsoluteXPosition() + x_pos_ + box_size_ + 10, 
        GetAbsoluteYPosition() + y_pos_ + box_size_ / 2 - 4, 
        14, 
        ui.ui_text_dark); */

    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + x_pos_ + box_size_ + 10, 
        GetAbsoluteYPosition() + y_pos_ + box_size_ / 2 - 8,
        text_.c_str(), 
        18, 
        ui.ui_text_dark);
}

void UICheckbox::Update() {
    if (value_ == nullptr) {
        return;
    }

    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + x_pos_),
        static_cast<float>(GetAbsoluteYPosition() + y_pos_),
        static_cast<float>(box_size_),
        static_cast<float>(box_size_)
    });
    
    if (mouse_on_button) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state_ = MouseState::MOUSE_PRESSED;
            *value_ = !*value_;
        } else {
            state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        state_ = MouseState::MOUSE_CLEAR;
    }


}
