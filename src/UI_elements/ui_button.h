#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"


class UIButton : public UIElement, public UIMouseState {
 protected:
  float corner_radius_;
  std::function<void()> binding_;

 public: 
  UIButton(int x_pos, int y_pos, int width, int height, float corner_radius, std::function<void()> func);

  void Draw() override;
  void Update() override;
};