#include "ui_label.h"
#include "../UI_Tools/ui_tools.h"
#include "ui.h"

UILabel::UILabel() {}

UILabel::UILabel(int x, int y, const std::string& text) : UIElement(x, y, 10, 10) {
    text_ = text;
}

void UILabel::Draw() {
    UITools::DrawText(GetAbsoluteXPosition(), GetAbsoluteYPosition(), text_, 14, ui.ui_text_dark);
}