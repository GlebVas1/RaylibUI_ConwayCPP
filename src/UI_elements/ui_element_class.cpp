#include "ui_element_class.h"
#include "ui.h"

void UIElement::SetDimensions(int x, int y) {
    width_ = x;
    height_ = y;
}

void UIElement::SetPosition(int x, int y) {
    x_position_ = x;
    y_position_ = y;
}

void UIElement::SetWidth(int x) {
    width_ = x;
}

void UIElement::SetHeight(int y) {
    height_ = y;
}

void UIElement::Draw() {}

void UIElement::Init() {}

void UIElement::Update() {}

//UIElement::UIElement() : ui(UI::GetInstance()) {}
UIElement::UIElement() {
    UI::GetInstance().AddUIElement(this);
}

UIElement::UIElement(int width, int height) :
    width_(width),
    height_(height)
{
    UI::GetInstance().AddUIElement(this);
}

UIElement::UIElement(int x_pos, int y_pos, int width, int height) :
    width_(width),
    height_(height),
    x_position_(x_pos),
    y_position_(y_pos)
{
    UI::GetInstance().AddUIElement(this);
}

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

int UIElement::GetAbsoluteXPosition() {
    int x = parrent_ == nullptr ? 0 : parrent_->GetAbsoluteXPosition();
    return x_position_ + x;
}

int UIElement::GetAbsoluteYPosition() {
    int y = parrent_ == nullptr ? 0 : parrent_->GetAbsoluteYPosition();
    return y_position_ + y;
}

void UIElement::SetParrent(UIElement* parrent) {
    if (parrent_ != nullptr) {
        parrent_->children_.erase(this);
    }
    if (parrent != nullptr) {
        parrent->children_.insert(this);
    }

    parrent_ = parrent;
}

UIElement* UIElement::GetParrent() {
    return parrent_;
}

std::unordered_set<UIElement*> UIElement::GetChildren() {
    return children_;
}