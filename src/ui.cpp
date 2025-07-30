#include "ui.h"

UI::UI() {};

UI& UI::GetInstance() {
    static UI obj;
    return obj;
}

UI::~UI() {
    CloseWindow();
}

void UI::Start() {

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(window_width, window_height, ".");

    SetTargetFPS(60);
    ClearBackground(WHITE);

    InitializeMainTexture();
    while (!WindowShouldClose()) {
        //f->UpdateField();
        BeginDrawing();
        DrawRenderTexture();
        EndDrawing();
    }
}

void UI::DrawRenderTexture() {
    uint8_t* data = static_cast<uint8_t*>(malloc(main_texture_width_ * main_texture_height_ * 4));
    std::memcpy(data, color_buffer_, main_texture_width_ * main_texture_height_ * 4);
    Image img = {
        .data = data,
        .width = main_texture_width_,
        .height = main_texture_height_,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };

    Color* pixels = LoadImageColors(img);
    UpdateTexture(*main_texture_, pixels);
    UnloadImage(img);
    DrawTexture(*main_texture_, 0, 0, WHITE);
    UnloadImageColors(pixels);
}


void UI::InitializeMainTexture() {
    uint8_t* data0 = static_cast<uint8_t*>(malloc(main_texture_width_ * main_texture_width_ * 4));
    Image img0 = {
        .data = data0,
        .width = main_texture_width_,
        .height = main_texture_width_,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 
    };
    main_texture_ = std::make_shared<Texture2D>(LoadTextureFromImage(img0));
    UnloadImage(img0);
}

void UI::SetColorBuffer(uint8_t* new_color_buffer) {
        color_buffer_ = new_color_buffer;
}