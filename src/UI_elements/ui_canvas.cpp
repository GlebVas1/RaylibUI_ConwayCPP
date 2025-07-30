#include "ui_canvas.h"

void UICanvas::Draw() {
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
    //DrawTexture(*main_texture_, x_position, y_position, WHITE);
    
    //return;

    DrawTexturePro(
        *main_texture_,
        Rectangle{
            0,
            0,
            static_cast<float>(main_texture_width_),
            static_cast<float>(main_texture_height_)
        },
        Rectangle({
            static_cast<float>(x_position),
            static_cast<float>(y_position),
            static_cast<float>(width),
            static_cast<float>(height)
        }),
        Vector2{0.0f, 0.0f},
        0.0f,
        WHITE
    );

    if (show_grid_) {
        DrawTexturePro(
            *main_grid_texture_,
            Rectangle{
                0,
                0,
                static_cast<float>(width),
                static_cast<float>(height)
            },
            Rectangle({
                static_cast<float>(x_position),
                static_cast<float>(y_position),
                static_cast<float>(width),
                static_cast<float>(height)
            }),
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }
    UnloadImageColors(pixels);
}


void UICanvas::InitializeMainTexture() {
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

void UICanvas::InitializeMainGridTexture() {
    uint8_t* data = static_cast<uint8_t*>(malloc(width * height * 4));
    memset(data, 0, 4 * width * height);

    RenderTexture2D grid_render_texture = LoadRenderTexture(width, height);
    SetTextureFilter(grid_render_texture.texture, TEXTURE_FILTER_TRILINEAR);

    BeginTextureMode(grid_render_texture);

    size_t cell_width = width / main_texture_width_;
    size_t cell_height = height / main_texture_height_;
    ClearBackground(Color{0, 0, 0, 0});
    
    BeginBlendMode(BLEND_SUBTRACT_COLORS);

    DrawRectangle(0, 0, width, height, grid_color_);

    for (size_t x = 0; x < main_texture_width_; ++x) {
        for (size_t y = 0; y < main_texture_height_; ++y) {
            DrawRectangleRounded(
            Rectangle{
                    static_cast<float>(x * cell_width + 1),
                    static_cast<float>(y * cell_height + 1),
                    static_cast<float>(cell_width - 1),
                    static_cast<float>(cell_height - 1)
                },
                0.4f, 
                0,
                Color({
                    0,
                    0,
                    0,
                    255
                })
            );
        }
    }
    EndBlendMode();

    EndTextureMode();

    main_grid_texture_ = std::make_shared<Texture2D>(grid_render_texture.texture);
    SetTextureFilter(*main_grid_texture_, TEXTURE_FILTER_BILINEAR);
}


void UICanvas::ReinitializeMainTexture() {
   // UnloadTexture(*main_texture_);
    InitializeMainTexture();
}

void UICanvas::ReinitializeMainGridTexture() {
   // UnloadTexture(*main_grid_texture_);
    InitializeMainGridTexture();
}

void UICanvas::Init() {
    InitializeMainTexture();
    InitializeMainGridTexture();
}

void UICanvas::SetShowGrid(bool val) {
    show_grid_ = val;
}

void UICanvas::SetCanvasTextureDimensions(int x, int y) {
    main_texture_width_ = x;
    main_texture_height_ = y;
    ReinitializeMainTexture();
    ReinitializeMainGridTexture();
}

void UICanvas::SetColorBuffer(uint8_t* buffer) {
    color_buffer_ = buffer;
} 
