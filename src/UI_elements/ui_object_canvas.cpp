#include "ui_object_canvas.h"
 #include "ui.h"
void UIObjectCanvas::Init() {
    InitializeMainTexture();
    InitializeMainGridTexture();
}

void UIObjectCanvas::Update() {

}

void UIObjectCanvas::SetObject(const GameObject& object) {
    this_object_ = object;
    if (color_buffer_ != nullptr) {
        free(color_buffer_);
    }

    if (object.size == 0) {
        std::cerr << "Empty object in UIObjectCanvas::SetObject" << std::endl;
    }

    color_buffer_ = static_cast<uint8_t*>(malloc(object.size * object.size * 4));

    for (size_t x = 0; x < object.size; ++x) {
        for (size_t y = 0; y < object.size; ++y) {
            if (object.array[x][y] == 1) {
                GameColor this_color = ui.GetCurrentPalette()[255];
                color_buffer_[x * object.size + y] = this_color.r;
                color_buffer_[x * object.size + y + 1] = this_color.g;
                color_buffer_[x * object.size + y + 2] = this_color.b;
                color_buffer_[x * object.size + y + 3] = 255;
            }
        }    
    }

    SetCanvasTextureDimensions(object.size, object.size);
    SetShowGrid(object.should_grid_show);
}

void UIObjectCanvas::UpdatePalette(const std::vector<GameColor>& palette) {

    if (color_buffer_ == nullptr) {
        std::cerr << "Empty buffer in UIObjectCanvas::UpdatePalette" << std::endl;
    }

    for (size_t x = 0; x < this_object_.size; ++x) {
        for (size_t y = 0; y < this_object_.size; ++y) {
            if (this_object_.array[x][y] == 1) {
                GameColor this_color = ui.GetCurrentPalette()[255];
                color_buffer_[x * this_object_.size + y] = this_color.r;
                color_buffer_[x * this_object_.size + y + 1] = this_color.g;
                color_buffer_[x * this_object_.size + y + 2] = this_color.b;
                color_buffer_[x * this_object_.size + y + 3] = 255;
            }
        }    
    }
}

void UIObjectCanvas::SetPixel(size_t x, size_t y, uint8_t val) {
    this_object_.array[x][y] = val;
    GameColor this_color = ui.GetCurrentPalette()[255];
    color_buffer_[x * this_object_.size + y] = this_color.r;
    color_buffer_[x * this_object_.size + y + 1] = this_color.g;
    color_buffer_[x * this_object_.size + y + 2] = this_color.b;
    color_buffer_[x * this_object_.size + y + 3] = 255;
}

uint8_t UIObjectCanvas::GetPixel(size_t x, size_t y) {
    return this_object_.array[x][y];
}

const GameObject& UIObjectCanvas::GetObject() {
    return this_object_;
}