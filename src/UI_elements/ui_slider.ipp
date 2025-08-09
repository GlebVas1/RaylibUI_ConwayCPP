#include "ui.h"

template <typename T>
UIHorizontalSlider<T>::UIHorizontalSlider(int x, int y, int width, int height, std::function<void(T)> func):
    UIElement(x, y, width, height)
{
    binding_ = func;
}



template<typename T>
void UIHorizontalSlider<T>::Draw() {
    int line_width = width_ - 2 * x_offset_;
    int line_y_pos = height_ / 2 - line_height_ / 2;
    float slider_relevant_pos = static_cast<float>(value_) / (max_value_ - min_value_);
    int slider_x_pos = x_offset_ + static_cast<int>(slider_relevant_pos * (line_width - slider_width_));
    int slider_y_pos = height_ / 2 - slider_height_ / 2;

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + x_offset_,
        GetAbsoluteYPosition() + line_y_pos,
        line_width,
        line_height_,
        0,
        1.0f,
        ui.ui_accent_color_3,
        ui.ui_line_color
    );

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + slider_x_pos,
        GetAbsoluteYPosition() + slider_y_pos,
        slider_width_,
        slider_height_,
        0,
        0.1f,
        ui.ui_accent_color_1,
        ui.ui_line_color
    );
}

template <typename T>
void UIHorizontalSlider<T>::Update() {
    int line_width = width_ - 2 * x_offset_;
    bool mouse_on_slider = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + x_offset_),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(line_width),
        static_cast<float>(height_)
    });

    if (mouse_on_slider) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int mouse_x_position_on_line = std::max<int>(GetAbsoluteXPosition() + x_offset_, std::min<int>(GetAbsoluteXPosition() + width_ - x_offset_, GetMousePosition().x));
            value_= static_cast<int>((static_cast<float>(mouse_x_position_on_line - (GetAbsoluteXPosition() + x_offset_)) / (width_ - 2 * x_offset_)) * (max_value_ - min_value_));
            binding_(value_);
        }
    }
}

template<typename T>
void UIHorizontalSlider<T>::SetMinValue(T val) {
    min_value_ = val;
}

template<typename T>
void UIHorizontalSlider<T>::SetMaxValue(T val) {
    max_value_ = val;
}