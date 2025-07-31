#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_element_class.h"

class UICanvas : public UIElement {
    private:
    std::shared_ptr<Texture2D> main_texture_ = nullptr;
    std::shared_ptr<Texture2D> main_grid_texture_ = nullptr;

    int main_texture_width_ = 500;
    int main_texture_height_ = 500;

    uint8_t* color_buffer_ = nullptr;

    void InitializeMainTexture();
    void InitializeMainGridTexture();

    void ReinitializeMainTexture();
    void ReinitializeMainGridTexture();

    bool show_grid_ = false;

    Color grid_color_ = WHITE;

    public: 

    void Draw() override;
    void Init() override;
    void Update() override;

    void SetShowGrid(bool val);

    void SetCanvasTextureDimensions(int x, int y);

    void SetColorBuffer(uint8_t* buffer);
};