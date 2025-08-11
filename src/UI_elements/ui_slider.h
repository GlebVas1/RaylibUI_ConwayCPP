#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "../UI_Tools/ui_tools.h"


template <typename T>
class UIHorizontalSlider : public UIElement {
 private:
  T value_ = 0;
  T min_value_ = 0;
  T max_value_ = 600;

  static const int x_offset_ = 10;
  static const int line_height_ = 4;
  static const int slider_width_ = 10;
  static const int slider_height_ = 20;

  std::function<void(T)> on_value_change_;

 public:
  UIHorizontalSlider(int x, int y, int width, int height, std::function<void(T)> on_value_change);

  void Draw() override;
  void Update() override;

  void NormalizeValue();
  void SetMaxValue(T val);
  void SetMinValue(T val);

  T GetValue();
  void SetValue(T val);
};

#include "ui_slider.ipp"