#include "ui_text_component.h"

std::string& UITextComponent::GetTextComponent() { 
    return text_;
}

UITextComponent::UITextComponent() {}

UITextComponent::UITextComponent(const std::string& str) : text_(str) {}

void UITextComponent::SetTextComponent(const std::string& str) {
    text_ = str;
}