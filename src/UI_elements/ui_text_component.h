#pragma once
#include "stdafx.h"


class UITextComponent {
 protected:
  std::string text_;
  size_t text_position_x = 0;
  size_t text_position_y = 0;
 
 public:
  UITextComponent();
  UITextComponent(const std::string& str);
  
  void SetTextComponent(const std::string& str);
  std::string& GetTextComponent();
};