#include "ui_panel.h"
#include "../UI_Tools/ui_tools.h"
#include "ui.h"

void UIPanel::Init() {
    shadow_ = std::make_shared<UIShadowEffect>(
        x_position_ - 5,
        y_position_ - 5,
        width_ + 10,
        height_ + 10,
        roundness_,
        4
    );
}

void UIPanel::Draw() {
    shadow_->Draw();
    UITools::DrawRectangle(
        x_position_,
        y_position_,
        width_,
        height_,
        2,
        roundness_,
        ui.ui_accent_color_1,
        ui.ui_line_color
    );
}

void UIPanel::SetRoundness(float val) {
    roundness_ = val;
}

UIPanel::UIPanel() {}

UIPanel::UIPanel(int x_pos, int y_pos, int width, int height, float roundness) : UIElement(x_pos, y_pos, width, height) {
    roundness_ = roundness;
}