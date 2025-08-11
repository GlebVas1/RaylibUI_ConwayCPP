#include "ui_button.h"
#include "../UI_Tools/ui_tools.h"


UIButton::UIButton(int x_pos, int y_pos, int width, int height, float corner_radius, std::function<void()> func) :
  UIElement(x_pos, y_pos, width, height) {
    corner_radius_ = corner_radius;
    binding_ = func;
}

void UIButton::Draw() {
  const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
  Color background_color = UIColorThemeManager::GetInstance().GetTheme().ui_neutral_color;
  switch (state_)
  {
  case MouseState::MOUSE_CLEAR:
    break;
  case MouseState::MOUSE_HOVERED:
    background_color = ColorTint(background_color, this_theme.ui_color_hovered);
    break;  
  case MouseState::MOUSE_PRESSED:
    background_color = ColorTint(background_color, this_theme.ui_color_pressed);
    break;
  }

  UITools::DrawRectangle(
    GetAbsoluteXPosition(),
    GetAbsoluteYPosition(),
    width_,
    height_,
    this_theme.line_narrow_thikness,
    this_theme.elements_corner_radius,
    background_color,
    this_theme.ui_line_color
  );
}

void UIButton::Update() {
  const bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
    static_cast<float>(GetAbsoluteXPosition()),
    static_cast<float>(GetAbsoluteYPosition()),
    static_cast<float>(width_),
    static_cast<float>(height_)
  });
  
  if (mouse_on_button) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      state_ = MouseState::MOUSE_PRESSED;
      binding_();
    } else {
      state_ = MouseState::MOUSE_HOVERED;
    }
  } else {
    state_ = MouseState::MOUSE_CLEAR;
  }
}
