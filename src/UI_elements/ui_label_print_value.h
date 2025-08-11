#pragma once
#include "stdafx.h"
#include "ui_element_class.h"


template<typename T>
class UILabelPrintValue : public UIElement {
 private:
  std::string text_format_;
  std::function<T(void)> get_value_;

 public:
  UILabelPrintValue(int x, int y, const std::string& text_format, std::function<T()> get_value_function);
  void Draw() override;
};

#include "ui_label_print_value.ipp"