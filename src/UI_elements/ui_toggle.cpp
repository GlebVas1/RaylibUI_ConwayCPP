#include "raylib.h"
#include "ui_toogle.h"
#include "../UI_Tools/ui_tools.h"
#include "ui.h"

UIToggle::UIToggle() {

}

UIToggle::UIToggle(int x, int y, bool* val_ptr, const std::string& text) : UIElement(x, y, 60, 20) {
    text_ = text;
    value_ = val_ptr;
}

void UIToggle::Draw() {
    if (value_ == nullptr) {
        return;
    }
    Color background_color;

    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        background_color = ui.ui_button_default;
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = ui.ui_button_hovered;
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = ui.ui_button_pressed;
        break;
    }

    //DrawRectangle(GetAbsoluteXPosition(), GetAbsoluteYPosition(), 100, 100, WHITE);

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + x_pos_,
        GetAbsoluteYPosition(),
        box_width_,
        height_,
        2,
        0.1,
        *value_ ? ui.ui_accent_color_2 : ui.ui_accent_color_3,
        ui.ui_line_color
    );

    int x_position_of_slider = *value_ ? GetAbsoluteXPosition() + x_pos_ :  GetAbsoluteXPosition() + x_pos_ + box_width_ - slider_width_;
    UITools::DrawRectangle(
        x_position_of_slider,
        GetAbsoluteYPosition(),
        slider_width_,
        height_,
        2,
        0.1,
        background_color,
        ui.ui_line_color
    );

    /* DrawText(
        text_.c_str(), 
        GetAbsoluteXPosition() + x_pos_ + box_width_ + 10, 
        GetAbsoluteYPosition() + height_ / 2 - 4, 
        14, 
        ui.ui_text_dark); */

    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + x_pos_ + box_width_ + 10, 
        GetAbsoluteYPosition() + height_ / 2 - 8,
        text_.c_str(), 
        18, 
        ui.ui_text_dark);
  //  UITools::DrawRectangle
}

void UIToggle::Update() {
    if (value_ == nullptr) {
        return;
    }

    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + x_pos_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(box_width_),
        static_cast<float>(height_)
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