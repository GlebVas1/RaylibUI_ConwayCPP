#include "ui_button.h"
#include "ui.h"

UIButton::UIButton(int x_pos, int y_pos, int width, int height, float roundness, std::function<void()> func) : UIElement(x_pos, y_pos, width, height) {
    roundness_ = roundness;
    binding = func;
}

void UIButton::Draw() {
    Rectangle main_field{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_line{
        static_cast<float>(GetAbsoluteXPosition() + 1),
        static_cast<float>(GetAbsoluteYPosition() + 1),
        static_cast<float>(width_ - 1),
        static_cast<float> (height_ - 1)
    };

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

    DrawRectangleRounded(main_field, roundness_, 0, Fade(background_color, 0.9f));
    DrawRectangleRoundedLinesEx(main_field_line, roundness_, 0, 2, Fade(BLACK, 1.0f));
}

void UIButton::Update() {
    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
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