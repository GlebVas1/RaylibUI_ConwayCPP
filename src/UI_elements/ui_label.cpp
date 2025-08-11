#include "ui_label.h"
#include "../UI_Tools/ui_tools.h"


UILabel::UILabel() {}

UILabel::UILabel(int x, int y, const std::string& text) : UIElement(x, y, 10, 10) {
  text_ = text;
}

void UILabel::Draw() {
  UITools::DrawTextDefault(
    GetAbsoluteXPosition(), 
    GetAbsoluteYPosition(), 
    text_, 
    18, 
    UIColorThemeManager::GetInstance().GetTheme().ui_text_dark
  );
}