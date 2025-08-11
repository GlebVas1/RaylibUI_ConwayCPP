#include "ui_panel.h"

#include "../UI_Tools/ui_tools.h"


UIPanel::UIPanel() {}

UIPanel::UIPanel(int x_pos, int y_pos, int width, int height, float corner_radius) : 
  UIElement(x_pos, y_pos, width, height) 
{
  corner_radius_ = corner_radius;
}

void UIPanel::SetRoundness(float val) {
  corner_radius_ = val;
  Init();
}

void UIPanel::Init() {
  float roundness = static_cast<float>(corner_radius_) / std::min(width_, height_);
  shadow_ = std::make_unique<UIShadowEffect>(
    x_position_ - 5,
    y_position_ - 5,
    width_ + 10,
    height_ + 10,
    roundness,
    4
  );
}

void UIPanel::Draw() {
  shadow_->Draw();
  const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
  UITools::DrawRectangle(
    x_position_,
    y_position_,
    width_,
    height_,
    this_theme.line_default_thikness,
    corner_radius_,
    this_theme.ui_neutral_color,
    this_theme.ui_line_color
  );
}