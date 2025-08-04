#include "ui_button.h"

UIButton::UIButton() {}
UIButton::UIButton(int width, int height) : UIElement(width, height) {}
UIButton::UIButton(int x_pos, int y_pos, int width, int height) : UIElement(x_pos, y_pos, width, height) {}
UIButton::UIButton(int x_pos, int y_pos, int width, int height, const std::string& str) :
    UIElement(x_pos, y_pos, width, height),
    UITextComponent(str) {}

void UIButton::Draw() {
    Rectangle main_field{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_line{
        static_cast<float>(x_position_ + 1),
        static_cast<float>(y_position_ + 1),
        static_cast<float>(width_ - 1),
        static_cast<float> (height_ - 1)
    };

    Color background_color;
    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        background_color = default_c_;
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = covered_c_;
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = pressed_c_;
        break;
    }

    DrawRectangleRounded(main_field, roundness_, 0, Fade(background_color, 0.9f));
    DrawText(text_.c_str(), x_position_ + 15, y_position_ + 5, 20, BLACK);
    DrawRectangleRoundedLinesEx(main_field_line, roundness_, 0, 2, Fade(BLACK, 1.0f));
}

void UIButton::Update() {
    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(width_),
        static_cast<float>(height_)
    });
    
    if (mouse_on_button) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            state_ = MouseState::MOUSE_PRESSED;
            binding();
        } else {
            state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        state_ = MouseState::MOUSE_CLEAR;
    }
}

void UIButton::SetRoundness(float roundness) {
    roundness_ = std::max(0.0f, std::min(roundness, 1.0f));
}