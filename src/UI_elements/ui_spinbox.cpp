#include "ui_spinbox.h"
#include "ui.h"

void UISpinBox::SetValuePtr(float* ptr) {
    value_ = ptr;
}

void UISpinBox::NormalizeValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ = std::min(max_value, std::max(min_value, *value_));
}

void UISpinBox::Draw() {
    if (value_ == nullptr) {
        return;
    }
    std::string str = std::to_string(*value_);

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

    Rectangle main_field_left{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(buttons_width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_left_line{
        static_cast<float>(x_position_ + 1),
        static_cast<float>(y_position_ + 1),
        static_cast<float>(buttons_width_ - 1),
        static_cast<float> (height_ - 1)
    };

    Rectangle main_field_right{
        static_cast<float>(x_position_ + width_ - buttons_width_),
        static_cast<float>(y_position_),
        static_cast<float>(buttons_width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_right_line{
        static_cast<float>(x_position_ + width_ - buttons_width_ + 1),
        static_cast<float>(y_position_ + 1),
        static_cast<float>(buttons_width_ - 1),
        static_cast<float> (height_ - 1)
    };

    Color left_color;
    switch (left_state_)
    {
    case MouseState::MOUSE_CLEAR:
        left_color = ui.ui_button_default;
        break;
    case MouseState::MOUSE_HOVERED:
        left_color = ui.ui_button_hovered;
        break;   
    case MouseState::MOUSE_PRESSED:
        left_color = ui.ui_button_pressed;
        break;
    }

    Color right_color;
    switch (right_state_)
    {
    case MouseState::MOUSE_CLEAR:
        right_color = ui.ui_button_default;
        break;
    case MouseState::MOUSE_HOVERED:
        right_color = ui.ui_button_hovered;
        break;   
    case MouseState::MOUSE_PRESSED:
        right_color = ui.ui_button_pressed;
        break;
    }

    DrawRectangleRounded(main_field, roundness_, 0, ui.ui_accent_color_3);
    DrawRectangleRoundedLinesEx(main_field_line, roundness_, 0, 2, ui.ui_line_color);

    DrawRectangleRounded(main_field_left, roundness_, 0, left_color);
    DrawRectangleRoundedLinesEx(main_field_left_line, roundness_, 0, 2, ui.ui_line_color);

    DrawRectangleRounded(main_field_right, roundness_, 0, right_color);
    DrawRectangleRoundedLinesEx(main_field_right_line, roundness_, 0, 2, ui.ui_line_color);

    DrawText(TextFormat("%02.0f", *value_), x_position_ + width_ / 2 - 8 , y_position_ + height_ / 2 - 5, 14, WHITE);
}



void UISpinBox::IncreaseValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ += step_;
    NormalizeValue();
}

void UISpinBox::DecreaseValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ -= step_;
    NormalizeValue();
}

void UISpinBox::Update() {
    bool mouse_on_left_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    bool mouse_on_right_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(x_position_ + width_ - buttons_width_),
        static_cast<float>(y_position_),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    if (mouse_on_left_button) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            left_state_ = MouseState::MOUSE_PRESSED;
            DecreaseValue();
        } else {
            left_state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        left_state_ = MouseState::MOUSE_CLEAR;
    }

    if (mouse_on_right_button) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            right_state_ = MouseState::MOUSE_PRESSED;
            IncreaseValue();
        } else {
            right_state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        right_state_ = MouseState::MOUSE_CLEAR;
    }

}

void UISpinBox::SetMaxValue(float val) {
    max_value = val;
}

void UISpinBox::SetMinValue(float val) {
    min_value = val;
}

void UISpinBox::SetStep(float val) {
    step_ = val;
}