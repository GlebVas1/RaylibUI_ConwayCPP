#include "ui_canvas.h"


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
  // SetTextureFilter(*main_texture_, TEXTURE_FILTER_TRILINEAR);
  // on small res looks strange
  UnloadImage(img0);
}

void UICanvas::InitializeMainGridTexture() {
  const float cell_width = static_cast<float>(width_) / main_texture_width_;
  const float cell_height = static_cast<float>(height_) / main_texture_height_;

  RenderTexture2D grid_render_texture = LoadRenderTexture(width_, height_);
  SetTextureFilter(grid_render_texture.texture, TEXTURE_FILTER_TRILINEAR);

  BeginTextureMode(grid_render_texture);

  ClearBackground(Color{0, 0, 0, 0});
  DrawRectangle(0, 0, width_, height_, WHITE);

  BeginBlendMode(BLEND_SUBTRACT_COLORS);
  for (size_t x = 0; x < main_texture_width_; ++x) {
    for (size_t y = 0; y < main_texture_height_; ++y) {
      DrawRectangleRounded(
      Rectangle{
          static_cast<float>(x * cell_width + 1.1f),
          static_cast<float>(y * cell_height + 1.1f),
          static_cast<float>(cell_width - 1.1f),
          static_cast<float>(cell_height - 1.1f)
        },
        0.4f, 
        4,
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

  RenderTexture2D grid_empty_render_texture = LoadRenderTexture(width_, height_);
  SetTextureFilter(grid_empty_render_texture.texture, TEXTURE_FILTER_TRILINEAR);

  BeginTextureMode(grid_empty_render_texture);

  ClearBackground(Color{0, 0, 0, 0});
  DrawRectangle(0, 0, width_, height_, WHITE);

  BeginBlendMode(BLEND_SUBTRACT_COLORS);
  DrawRectangleRounded(
  Rectangle{
      1.1f,
      1.1f,
      static_cast<float>(width_) - 1.1f,
      static_cast<float>(height_) - 1.1f
    },
    static_cast<float>(10) / width_, 
    4,
    Color({
      0,
      0,
      0,
      255
    })
  );
  EndBlendMode();

  EndTextureMode();

  main_grid_empty_texture_ = std::make_shared<Texture2D>(grid_empty_render_texture.texture);
  SetTextureFilter(*main_grid_empty_texture_, TEXTURE_FILTER_BILINEAR);
}


void UICanvas::ReinitializeMainTexture() {
  if (main_texture_ != nullptr) {
    UnloadTexture(*main_texture_);
  }
  InitializeMainTexture();
}

void UICanvas::ReinitializeMainGridTexture() {
  if (main_grid_texture_ != nullptr) {
    UnloadTexture(*main_grid_texture_);
  }
  if (main_grid_empty_texture_ != nullptr) {
    UnloadTexture(*main_grid_empty_texture_);
  }
  InitializeMainGridTexture();
}

UICanvas::UICanvas() {}

UICanvas::~UICanvas() {
  UnloadTexture(*main_texture_);
  UnloadTexture(*main_grid_texture_);
  UnloadTexture(*main_grid_empty_texture_);
}

void UICanvas::Init() {
  InitializeMainTexture();
  InitializeMainGridTexture();
}

void UICanvas::Draw() {
  if (color_buffer_ != nullptr) {
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
    UnloadImageColors(pixels);

    DrawTexturePro(
      *main_texture_,
      Rectangle{
        0,
        0,
        static_cast<float>(main_texture_width_),
        static_cast<float>(main_texture_height_)
      },
      Rectangle({
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float>(height_)
      }),
      Vector2{0.0f, 0.0f},
      0.0f,
      WHITE
    );

    DrawTexturePro(
      show_grid_ ? *main_grid_texture_ : *main_grid_empty_texture_,
      Rectangle{
        0,
        0,
        static_cast<float>(width_),
        static_cast<float>(height_)
      },
      Rectangle({
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float>(height_)
      }),
      Vector2{0.0f, 0.0f},
      0.0f,
      UIColorThemeManager::GetInstance().GetTheme().ui_neutral_color
    );
  } 
}

void UICanvas::Update() {}

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



