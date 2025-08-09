#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_element_class.h"

class UICanvas : public UIElement {
    protected:
    std::shared_ptr<Texture2D> main_texture_ = nullptr;
    std::shared_ptr<Texture2D> main_grid_texture_ = nullptr;
    std::shared_ptr<Texture2D> main_grid_empty_texture_ = nullptr;
    int main_texture_width_ = 500;
    int main_texture_height_ = 500;

    uint8_t* color_buffer_ = nullptr;

    /* initializes textures w/o color buffer using */
    void InitializeMainTexture();
    void InitializeMainGridTexture();

    void ReinitializeMainTexture();
    void ReinitializeMainGridTexture();

    bool show_grid_ = false;

    Color grid_color_ = WHITE;

    public: 
    
    virtual void Draw();
    virtual void Init();
    virtual void Update();

    void SetShowGrid(bool val);

    void SetCanvasTextureDimensions(int x, int y);

    void SetColorBuffer(uint8_t* buffer);

    void SetCanvasGridColor(Color c);

};