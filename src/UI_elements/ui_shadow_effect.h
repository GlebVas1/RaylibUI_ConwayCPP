#pragma once
#include "raylib.h"
#include "stdafx.h"


class UIShadowEffect {
  private:
    int x;
    int y;
    int width;
    int height;
    std::shared_ptr<Texture2D> shadow = nullptr;
  public:
    UIShadowEffect(int x, int y, int width, int height, float roundness, int iterations);
    ~UIShadowEffect();
    void Draw();
};