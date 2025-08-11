#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_element_class.h"
#include "ui_mouse_state.h"


class UICheckbox : public UIElement, UIMouseState {
 private:
  bool value_ = false;
  std::function<void(bool)> binding_;
  static const int x_pos_ = 0;
  static const int y_pos_ = 0;
  static const int box_size_ = 20;
  static const int check_size_ = 12;

  static const float check_roundness_;
  std::string text_;
   
 public:
  UICheckbox();
  UICheckbox(int x, int y, std::function<void(bool)> func, const std::string& text);

  void Draw() override;
  void Update() override;
  

  bool GetValue();
  void SetValue(bool val);
};
