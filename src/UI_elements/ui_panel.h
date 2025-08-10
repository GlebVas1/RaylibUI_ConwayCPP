#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "ui_shadow_effect.h"


class UIPanel : public UIElement {
  private:
    float roundness_;
    std::unique_ptr<UIShadowEffect> shadow_ = nullptr;
  public:
    void SetRoundness(float val);
    void Draw() override;
    void Init() override;
    UIPanel();
    UIPanel(int x_pos, int y_pos, int width, int height, float roundness);
};