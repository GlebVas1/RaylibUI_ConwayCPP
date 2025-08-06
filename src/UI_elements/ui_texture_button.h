#pragma once
#include "raylib.h"
#include "ui_button.h"

class UITextureButton : public UIButton {
    private:
    Texture2D* texture_;
    public:
    UIButton(int x_pos, int y_pos, int width, int height, float roundness, std::function<void()> func, const std::string& texture);
};