#include "../UI_Tools/ui_tools.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wall"
#pragma GCC diagnostic ignored "-Wextra"


template<typename T>
void UISpinBox<T>::NormalizeValue() {
    value_ = std::min(max_value_, std::max(min_value_, value_));
}

template<typename T>
const float UISpinBox<T>::roundness_ = 0.1f;

template<typename T>
void UISpinBox<T>::Draw() {
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

    Rectangle main_field_left{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_left_line{
        static_cast<float>(GetAbsoluteXPosition() + 1),
        static_cast<float>(GetAbsoluteYPosition() + 1),
        static_cast<float>(buttons_width_ - 1),
        static_cast<float> (height_ - 1)
    };

    Rectangle main_field_right{
        static_cast<float>(GetAbsoluteXPosition() + width_ - buttons_width_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_right_line{
        static_cast<float>(GetAbsoluteXPosition() + width_ - buttons_width_ + 1),
        static_cast<float>(GetAbsoluteYPosition() + 1),
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

    const auto text_size = UITools::MeasureTextDefault(TextFormat(UITextFormat<T>::format_, value_), 18);

    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + width_ / 2 - text_size.first / 2,
        GetAbsoluteYPosition() + height_ / 2 - text_size.second / 2, 
        TextFormat(UITextFormat<T>::format_, value_), 
        18, 
        ui.ui_text_light
    );

    
    //DrawText(TextFormat(UITextFormat<T>::format_, *value_), GetAbsoluteXPosition() + width_ / 2 - 8 , GetAbsoluteYPosition() + height_ / 2 - 6, 14, WHITE);
}


template<typename T>
void UISpinBox<T>::IncreaseValue() {
    value_ += step_;
    NormalizeValue();
}

template<typename T>
void UISpinBox<T>::DecreaseValue() {
    value_ -= step_;
    NormalizeValue();
}

template<typename T>
void UISpinBox<T>::Update() {
    bool mouse_on_left_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    bool mouse_on_right_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + width_ - buttons_width_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    if (mouse_on_left_button) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            left_state_ = MouseState::MOUSE_PRESSED;
            DecreaseValue();
            binding_(value_);
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
            binding_(value_);
        } else {
            right_state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        right_state_ = MouseState::MOUSE_CLEAR;
    }

}

template<typename T>
void UISpinBox<T>::SetMaxValue(T val) {
    max_value_ = val;
}

template<typename T>
void UISpinBox<T>::SetMinValue(T val) {
    min_value_ = val;
}

template<typename T>
void UISpinBox<T>::SetStep(T val) {
    step_ = val;
}

template<typename T>
UISpinBox<T>::UISpinBox() {}

template<typename T>
UISpinBox<T>::UISpinBox(int x, int y, std::function<void(T)> func, T step) {
    binding_ = func;
    SetPosition(x, y);
    SetDimensions(60, 20);
    SetStep(step);
}

template<typename T>
T UISpinBox<T>::GetValue() {
    return value_;
}

template<typename T>
void UISpinBox<T>::SetValue(T val) {
    value_ = val;
}

#pragma GCC diagnostic pop
