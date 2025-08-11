#include "raylib.h"
#include "ui_toogle.h"
#include "../UI_Tools/ui_tools.h"

UIToggle::UIToggle() {

}

UIToggle::UIToggle(int x, int y, std::function<void(bool)> func, const std::string& text) : UIElement(x, y, 60, 20) {
    text_ = text;
    binding_ = func;
}

void UIToggle::Draw() {
    Color background_color;
    const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
    background_color = this_theme.ui_neutral_color;
    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_hovered);
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_pressed);
        break;
    }

    //DrawRectangle(GetAbsoluteXPosition(), GetAbsoluteYPosition(), 100, 100, WHITE);

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + x_pos_,
        GetAbsoluteYPosition(),
        box_width_,
        height_,
        this_theme.line_narrow_thikness,
        this_theme.elements_corner_radius,
        value_ ? this_theme.ui_light_color : this_theme.ui_dark_color,
        this_theme.ui_line_color
    );

    int x_position_of_slider = value_ ? GetAbsoluteXPosition() + x_pos_ :  GetAbsoluteXPosition() + x_pos_ + box_width_ - slider_width_;
    UITools::DrawRectangle(
        x_position_of_slider,
        GetAbsoluteYPosition(),
        slider_width_,
        height_,
        this_theme.line_narrow_thikness,
        this_theme.elements_corner_radius,
        background_color,
        this_theme.ui_line_color
    );
    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + x_pos_ + box_width_ + 10, 
        GetAbsoluteYPosition() + height_ / 2 - 8,
        text_.c_str(), 
        18, 
        this_theme.ui_text_dark);
}

void UIToggle::Update() {
    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + x_pos_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(box_width_),
        static_cast<float>(height_)
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

bool UIToggle::GetValue() {
    return value_;
}
void UIToggle::SetValue(bool val) {
    value_ = val;
}