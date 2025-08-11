#include "ui_check_box.h"
#include "../UI_Tools/ui_tools.h"

UICheckbox::UICheckbox() {

}

UICheckbox::UICheckbox(int x, int y, std::function<void(bool)> func, const std::string& text) : UIElement(x, y, 60, 20) {
    text_ = text;
    binding_ = func;
}

void UICheckbox::Draw() {
    Color background_color;

    const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        background_color = this_theme.ui_dark_color;
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = ColorAlphaBlend(this_theme.ui_neutral_color, this_theme.ui_color_hovered, WHITE);;
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = ColorAlphaBlend(this_theme.ui_neutral_color, this_theme.ui_color_pressed, WHITE);;
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
        this_theme.ui_line_color
    );

    if (value_) {
        int offset = (box_size_ - check_size_) / 2;
        UITools::DrawRectangle(
            GetAbsoluteXPosition() + x_pos_ + offset,
            GetAbsoluteYPosition() + y_pos_ + offset,
            check_size_,
            check_size_,
            1, 
            check_roundness_,
            this_theme.ui_light_color,
            this_theme.ui_line_color
        );
    }

    /* DrawText(
        text_.c_str(), 
        GetAbsoluteXPosition() + x_pos_ + box_size_ + 10, 
        GetAbsoluteYPosition() + y_pos_ + box_size_ / 2 - 4, 
        14, 
        this_theme.ui_text_dark); */

    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + x_pos_ + box_size_ + 10, 
        GetAbsoluteYPosition() + y_pos_ + box_size_ / 2 - 8,
        text_.c_str(), 
        18, 
        this_theme.ui_text_dark);
}

void UICheckbox::Update() {

    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + x_pos_),
        static_cast<float>(GetAbsoluteYPosition() + y_pos_),
        static_cast<float>(box_size_),
        static_cast<float>(box_size_)
    });
    
    if (mouse_on_button) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state_ = MouseState::MOUSE_PRESSED;
            value_ = !value_;
            binding_(value_);
        } else {
            state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        state_ = MouseState::MOUSE_CLEAR;
    }
}

bool UICheckbox::GetValue() {
    return value_;
}
void UICheckbox::SetValue(bool val) {
    value_ = val;
}
