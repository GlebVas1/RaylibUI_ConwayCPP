#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "field.h"

class UI {
    private:
    UI();
    ~UI();
    int window_width = 600;
    int window_height = 600;

    int main_texture_width_ = 500;
    int main_texture_height_ = 500;

    uint8_t* color_buffer_ = nullptr;
    std::shared_ptr<Texture2D> main_texture_ = nullptr;

    void InitializeMainTexture();
    void DrawRenderTexture();
    public: 

    static UI& GetInstance();

    void Start();

    void SetColorBuffer(uint8_t* new_color_buffer);

};