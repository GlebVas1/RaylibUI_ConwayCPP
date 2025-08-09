#include "ui_text_button.h"
#include "../UI_Tools/ui_tools.h"
#include "ui.h"

UITextButton::UITextButton(
    int x_pos, 
    int y_pos, 
    int width, 
    int height, 
    float roundness, 
    std::function<void()> func, 
    const std::string& text) :
    UIButton(x_pos, y_pos, width, height, roundness, func) {
        text_ = text;
}

void UITextButton::Draw() {
    UIButton::Draw();
    UITools::DrawTextDefault(GetAbsoluteXPosition() + 5, GetAbsoluteYPosition() + height_ / 2 - 9, text_, 18, ui.ui_text_dark);
}