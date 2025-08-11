#include "ui_text_component.h"


UITextComponent::UITextComponent() {}

UITextComponent::UITextComponent(const std::string& str) : text_(str) {}

void UITextComponent::SetTextComponent(const std::string& str) {
  text_ = str;
}

std::string& UITextComponent::GetTextComponent() { 
  return text_;
}