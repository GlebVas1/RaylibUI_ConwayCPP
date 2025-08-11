#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "ui_shadow_effect.h"


class UIPanel : public UIElement {
 private:
  float corner_radius_;
  std::unique_ptr<UIShadowEffect> shadow_ = nullptr;
 public:
  UIPanel();
  UIPanel(int x_pos, int y_pos, int width, int height, float corner_radius);
  void SetRoundness(float val);

  void Init() override;
  void Draw() override;
};