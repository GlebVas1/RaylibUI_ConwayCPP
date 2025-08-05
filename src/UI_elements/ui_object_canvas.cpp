#include "ui_object_canvas.h"
 #include "ui.h"
void UIObjectCanvas::Init() {
    InitializeMainTexture();
    InitializeMainGridTexture();
}

void UIObjectCanvas::Update() {
    bool mouse_on_canvas = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float>(height_)
    });

    if (mouse_on_canvas) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            size_t x = static_cast<size_t>(static_cast<float>(main_texture_width_) * (GetMousePosition().x - GetAbsoluteXPosition()) / width_);
            size_t y = static_cast<size_t>(static_cast<float>(main_texture_height_) * (GetMousePosition().y - GetAbsoluteYPosition()) / height_);
            SetPixel(y, x, 1 - GetPixel(y, x));
        } 
    }
}

size_t UIObjectCanvas::BufferIndex(size_t size, size_t x, size_t y) {
    return (x * size + y) * 4;
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
    // std::cout << "AAVBAVA" << (void*)color_buffer_ <<  std::endl;
    for (size_t x = 0; x < object.size; ++x) {
        for (size_t y = 0; y < object.size; ++y) {
            GameColor this_color;
            if (object.array[x][y] == 1) {
                this_color = ui.GetCurrentPalette()[255];
            } else {
                this_color = ui.GetCurrentPalette()[0];
            }
            size_t this_ind = BufferIndex(object.size, x, y);
            color_buffer_[this_ind] = this_color.r;
            color_buffer_[this_ind + 1] = this_color.g;
            color_buffer_[this_ind + 2] = this_color.b;
            color_buffer_[this_ind + 3] = 255;
        }    
    }

    SetShowGrid(object.should_grid_show);
    SetCanvasTextureDimensions(object.size, object.size);
    
}

void UIObjectCanvas::UpdatePalette(const std::vector<GameColor>& palette) {

    if (color_buffer_ == nullptr) {
        std::cerr << "Empty buffer in UIObjectCanvas::UpdatePalette" << std::endl;
    }

    for (size_t x = 0; x < this_object_.size; ++x) {
        for (size_t y = 0; y < this_object_.size; ++y) {
            GameColor this_color;
            if (this_object_.array[x][y] == 1) {
                this_color = ui.GetCurrentPalette()[255];
            } else {
                this_color = ui.GetCurrentPalette()[0];
            }
            size_t this_ind = BufferIndex(this_object_.size, x, y);
            color_buffer_[this_ind] = this_color.r;
            color_buffer_[this_ind + 1] = this_color.g;
            color_buffer_[this_ind + 2] = this_color.b;
            color_buffer_[this_ind + 3] = 255;
        }    
    }
}

void UIObjectCanvas::SetPixel(size_t x, size_t y, uint8_t val) {
    std::cout << "UIObjectCanvas::SetPixel " << x << " " << y << " " << (int)val << std::endl;
    this_object_.array[x][y] = val;
    GameColor this_color = ui.GetCurrentPalette()[val == 1 ? 255 : 0];
    size_t this_ind = BufferIndex(this_object_.size, x, y);
    color_buffer_[this_ind] = this_color.r;
    color_buffer_[this_ind + 1] = this_color.g;
    color_buffer_[this_ind + 2] = this_color.b;
    color_buffer_[this_ind + 3] = 255;
}

uint8_t UIObjectCanvas::GetPixel(size_t x, size_t y) {
    return this_object_.array[x][y];
}

const GameObject& UIObjectCanvas::GetObject() {
    return this_object_;
}