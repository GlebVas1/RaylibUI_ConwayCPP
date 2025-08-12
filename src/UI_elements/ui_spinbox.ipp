#include "../UI_Tools/ui_tools.h"
#include "../UI_Tools/ui_textures_loader.h"

template <typename T, bool MouseDown>
const float UISpinBox<T, MouseDown>::roundness_ = 0.1f;

template <typename T, bool MouseDown>
UISpinBox<T, MouseDown>::UISpinBox() {}

template <typename T, bool MouseDown>
UISpinBox<T, MouseDown>::UISpinBox(int x, int y, std::function<void(T)> func, T step) {
    binding_ = func;
    SetPosition(x, y);
    SetDimensions(default_width_, default_height_);
    SetStep(step);
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::Init() {
    arrow_left = UITextureLoader::GetInstance().GetTexture("arrow_left");
    arrow_right = UITextureLoader::GetInstance().GetTexture("arrow_right");
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::Draw() {
    const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
    Color left_color = this_theme.ui_neutral_color;
    switch (left_state_)
    {
    case MouseState::MOUSE_CLEAR:
        break;
    case MouseState::MOUSE_HOVERED:
        left_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_hovered);
        break;   
    case MouseState::MOUSE_PRESSED:
        left_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_pressed);
        break;
    }

    Color right_color = this_theme.ui_neutral_color;
    switch (right_state_)
    {
    case MouseState::MOUSE_CLEAR:
        break;
    case MouseState::MOUSE_HOVERED:
        right_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_hovered);
        break;   
    case MouseState::MOUSE_PRESSED:
        right_color = ColorTint(this_theme.ui_neutral_color, this_theme.ui_color_pressed);
        break;
    }

    UITools::DrawRectangle(
        GetAbsoluteXPosition(), 
        GetAbsoluteYPosition(), 
        width_, 
        height_, 
        this_theme.line_narrow_thikness, 
        this_theme.elements_corner_radius, 
        this_theme.ui_dark_color, 
        this_theme.ui_line_color
    );


    UITools::DrawRectangle(
        GetAbsoluteXPosition(), 
        GetAbsoluteYPosition(), 
        buttons_width_, 
        height_, 
        this_theme.line_narrow_thikness, 
        this_theme.elements_corner_radius, 
        this_theme.ui_neutral_color, 
        this_theme.ui_line_color
    );

    DrawTexturePro(
        *arrow_left,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(arrow_left->width),
            static_cast<float>(arrow_left->height),
        },
        Rectangle{
            static_cast<float>(GetAbsoluteXPosition()),
            static_cast<float>(GetAbsoluteYPosition() + height_ / 2 - buttons_width_ / 2),
            static_cast<float>(buttons_width_),
            static_cast<float>(buttons_width_)
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        this_theme.ui_text_dark
    );

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + width_ - buttons_width_, 
        GetAbsoluteYPosition(), 
        buttons_width_, 
        height_, 
        this_theme.line_narrow_thikness, 
        this_theme.elements_corner_radius, 
        this_theme.ui_neutral_color, 
        this_theme.ui_line_color
    );

    DrawTexturePro(
        *arrow_right,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(arrow_right->width),
            static_cast<float>(arrow_right->height),
        },
        Rectangle{
            static_cast<float>(GetAbsoluteXPosition() + width_ - buttons_width_),
            static_cast<float>(GetAbsoluteYPosition() + height_ / 2 - buttons_width_ / 2),
            static_cast<float>(buttons_width_),
            static_cast<float>(buttons_width_)
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        this_theme.ui_text_dark
    );

    const auto text = UITextFormat<T>::Format(value_);
    const auto text_size = UITools::MeasureTextDefault(text, 18);

    

    UITools::DrawTextDefault(
        GetAbsoluteXPosition() + width_ / 2 - text_size.first / 2,
        GetAbsoluteYPosition() + height_ / 2 - text_size.second / 2, 
        TextFormat(text, value_), 
        18, 
        this_theme.ui_text_light
    );
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::Update() {
    const bool mouse_on_left_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    const bool mouse_on_right_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + width_ - buttons_width_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(buttons_width_),
        static_cast<float>(height_)
    });

    if (mouse_on_left_button) {
        if constexpr(MouseDown) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                left_state_ = MouseState::MOUSE_PRESSED;
                DecreaseValue();
                binding_(value_);
            } else {
                left_state_ = MouseState::MOUSE_HOVERED;
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                left_state_ = MouseState::MOUSE_PRESSED;
                DecreaseValue();
                binding_(value_);
            } else {
                left_state_ = MouseState::MOUSE_HOVERED;
            }
        }
    } else {
        left_state_ = MouseState::MOUSE_CLEAR;
    }

    if (mouse_on_right_button) {
        if constexpr(MouseDown) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                right_state_ = MouseState::MOUSE_PRESSED;
                IncreaseValue();
                binding_(value_);
            } else {
                right_state_ = MouseState::MOUSE_HOVERED;
            }
        } else {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                right_state_ = MouseState::MOUSE_PRESSED;
                IncreaseValue();
                binding_(value_);
            } else {
                right_state_ = MouseState::MOUSE_HOVERED;
            }
        }
    } else {
        right_state_ = MouseState::MOUSE_CLEAR;
    }
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::NormalizeValue() {
    value_ = std::min(max_value_, std::max(min_value_, value_));
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::IncreaseValue() {
    value_ += step_;
    NormalizeValue();
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::DecreaseValue() {
    value_ -= step_;
    NormalizeValue();
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::SetMaxValue(T val) {
    max_value_ = val;
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::SetMinValue(T val) {
    min_value_ = val;
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::SetStep(T val) {
    step_ = val;
}

template <typename T, bool MouseDown>
T UISpinBox<T, MouseDown>::GetValue() {
    return value_;
}

template <typename T, bool MouseDown>
void UISpinBox<T, MouseDown>::SetValue(T val) {
    value_ = val;
    NormalizeValue();
}
