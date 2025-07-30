#include "ui_element_class.h"

void UIElement::SetDimensions(size_t x, size_t y) {
    width = x;
    height = y;
}

void UIElement::SetPosition(size_t x, size_t y) {
    x_position = x;
    y_position = y;
}