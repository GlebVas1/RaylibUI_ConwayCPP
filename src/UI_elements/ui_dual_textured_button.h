#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "ui_button.h"


class UIDualTextureButton : public UIButton {
  private:
  Texture2D* true_state_;
  Texture2D* false_state_;
  bool current_state_ = false;
  std::function<void(bool)> on_state_change_function_;

  public:
  UIDualTextureButton(
    int x, 
    int y, 
    int width, 
    int height,
    float corner_radius, 
    std::function<void(bool)> func, 
    const std::string& true_state, 
    const std::string& false_state,
    bool initial_state
  );
  
  void Draw() override;
  
  void SetState(bool val);
  bool GetState();
};