
#include "../UI_Tools/ui_tools.h"
#include "raylib.h"
#include "ui_list.h"
#include "ui.h"

UIList::UIList() {}


UIList::UIList(int x, int y, int width, int height, size_t* selected_ptr) : UIElement(x, y, 200, 200) {
    selected_ = selected_ptr;
}


void UIList::SetVector(const std::vector<std::string>& original) {
    elements_ = original;
    slider_height_ = static_cast<int>((static_cast<float>(height_) / (y_item_size_ * elements_.size())) * (height_ - 2 * slider_line_y_offset_));
}


void UIList::Init() {
    list_render_texture_ = std::make_shared<RenderTexture2D>(LoadRenderTexture(width_ - slider_box_x_space_, height_));
}


void UIList::Draw() {

    


    BeginTextureMode(*list_render_texture_);
    ClearBackground({0, 0, 0, 0});
    DrawRectangleRounded(
        Rectangle {
            static_cast<float>(0),
            static_cast<float>(0),
            static_cast<float>(width_ - slider_box_x_space_),
            static_cast<float>(height_)
        },
        0.1f,
        0,
        WHITE
    );
    int full_list_height = elements_.size() * y_item_size_;
    int y_offset = static_cast<int>(slider_position_ * (full_list_height - height_));
    
    for (size_t i = 0; i < elements_.size();  ++i) {
        Color item_color = (i == *selected_) ? ui.ui_accent_color_2 : ui.ui_accent_color_3;
        Color text_color = (i == *selected_) ? ui.ui_text_dark : ui.ui_text_light;

        BeginBlendMode(BLEND_MULTIPLIED); 
        DrawRectangle(0, i * y_item_size_ - y_offset , width_ - slider_box_x_space_, y_item_size_ , item_color);
        DrawRectangleLines(0, i * y_item_size_ - y_offset, width_ - slider_box_x_space_, y_item_size_, ui.ui_line_color);
        EndBlendMode();
        UITools::DrawTextDefault(text_x_offset_ , i * y_item_size_ + text_y_offset_ - y_offset, elements_[i].c_str(), 18, text_color);
    }

    

    
    EndTextureMode();

    // https://www.reddit.com/r/raylib/comments/14lk8fx/texture_is_rendering_coordinates_with_flipped_y/
    DrawTexturePro(
        list_render_texture_->texture, 
        (Rectangle){ 0, 0, (float)list_render_texture_->texture.width, -(float)list_render_texture_->texture.height },
        (Rectangle){ GetAbsoluteXPosition(), GetAbsoluteYPosition(), (float)list_render_texture_->texture.width, (float)list_render_texture_->texture.height}, 
        (Vector2){ 0, 0 },
        0.0f, 
        WHITE);
    //DrawTexture(list_texture.texture, GetAbsoluteXPosition(), GetAbsoluteYPosition(), WHITE);

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + width_ - slider_box_x_space_ / 2 - slider_line_width_ / 2,
        GetAbsoluteYPosition() + slider_line_y_offset_,
        slider_line_width_,
        height_ - 2 * slider_line_y_offset_,
        0,
        1.0f,
        ui.ui_accent_color_3,
        BLACK
    );

    UITools::DrawRectangle(
        GetAbsoluteXPosition() + width_ - slider_box_x_space_ / 2 - slider_width_ / 2,
        GetAbsoluteYPosition() + slider_line_y_offset_ + static_cast<int>(slider_position_ * (height_ - 2 * slider_line_y_offset_ - slider_height_)),
        slider_width_,
        slider_height_,
        2,
        0.3f,
        ui.ui_accent_color_1,
        ui.ui_line_color
    );


}

void UIList::Update() {
    bool mouse_on_list = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(list_render_texture_->texture.width),
        static_cast<float>(list_render_texture_->texture.height)
    });

    int full_list_height = elements_.size() * y_item_size_;
    int y_offset = static_cast<int>(slider_position_ * (full_list_height - height_));

    if (mouse_on_list) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            size_t y = static_cast<size_t>(static_cast<float>(elements_.size()) * (GetMousePosition().y - GetAbsoluteYPosition() + y_offset) / full_list_height);
            *selected_ = y;
            ui.SetRule();
        }
        slider_position_ = std::max(0.0f, std::min(1.0f, slider_position_+ GetMouseWheelMove() * 0.16f));
    }

    bool mouse_on_slider = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition() + width_ - slider_box_x_space_ / 2 - slider_width_ / 2),
        static_cast<float>(GetAbsoluteYPosition() + slider_line_y_offset_),
        static_cast<float>(slider_width_),
        static_cast<float>(height_ - 2 * slider_line_y_offset_)
    });

    if (mouse_on_slider) {
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            int mouse_y_position_on_line = std::max<int>(GetAbsoluteYPosition() + slider_line_y_offset_, std::min<int>(GetAbsoluteYPosition() + height_ - 2 * slider_line_y_offset_, GetMousePosition().y));
            slider_position_ = static_cast<float>(mouse_y_position_on_line - (GetAbsoluteYPosition() + slider_line_y_offset_)) / (height_ - 2 * slider_line_y_offset_);
        }
    }
}