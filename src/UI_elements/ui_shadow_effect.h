#pragma once
#include "raylib.h"
#include "stdafx.h"


class UIShadowEffect {
  private:
    int width;
    int height;
    std::shared_ptr<Texture2D> shadow = nullptr;
  public:
    UIShadowEffect(int width, int height, float roundness, int iterations);
    ~UIShadowEffect();
    void Draw(int x_pos, int y_pos);
};