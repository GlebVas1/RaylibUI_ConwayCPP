#include "ui_element_class.h"

void UIElement::SetDimensions(int x, int y) {
    width_ = x;
    height_ = y;
}

void UIElement::SetPosition(int x, int y) {
    x_position_ = x;
    y_position_ = y;
}



void UIElement::Draw() {}

void UIElement::Init() {}

void UIElement::Update() {}

UIElement::UIElement() {}

UIElement::UIElement(int width, int height) : width_(width), height_(height) {}

UIElement::UIElement(int x_pos, int y_pos, int width, int height) :
    width_(width),
    height_(height),
    x_position_(x_pos),
    y_position_(y_pos) 
{}

void UIElement::SetXPosition(int x) {
    x_position_ = x;
}

void UIElement::SetYPosition(int y) {
    y_position_ = y;
}

int UIElement::GetWidth() { return width_; };

int UIElement::GetHeight() { return height_; };

int UIElement::GetXPosition() { return x_position_; };

int UIElement::GetYPosition() { return y_position_; };