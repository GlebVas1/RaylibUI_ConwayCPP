

template<typename T>
void UISpinBox<T>::SetValuePtr(T* ptr) {
    value_ = ptr;
}

template<typename T>
void UISpinBox<T>::NormalizeValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ = std::min(max_value, std::max(min_value, *value_));
}

template<typename T>
void UISpinBox<T>::Draw() {
    if (value_ == nullptr) {
        return;
    }
    std::string str = std::to_string(*value_);

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

    DrawText(TextFormat(UITextFormat<T>::format_, *value_), GetAbsoluteXPosition() + width_ / 2 - 8 , GetAbsoluteYPosition() + height_ / 2 - 5, 14, WHITE);
}


template<typename T>
void UISpinBox<T>::IncreaseValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ += step_;
    NormalizeValue();
}

template<typename T>
void UISpinBox<T>::DecreaseValue() {
    if (value_ == nullptr) {
        return;
    }
    *value_ -= step_;
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

template<typename T>
void UISpinBox<T>::SetMaxValue(T val) {
    max_value = val;
}

template<typename T>
void UISpinBox<T>::SetMinValue(T val) {
    min_value = val;
}

template<typename T>
void UISpinBox<T>::SetStep(T val) {
    step_ = val;
}

template<typename T>
UISpinBox<T>::UISpinBox() {}

template<typename T>
UISpinBox<T>::UISpinBox(int x, int y, T* val, T step) {
    SetPosition(x, y);
    SetDimensions(60, 25);
    SetValuePtr(val);
    SetStep(step);
}

