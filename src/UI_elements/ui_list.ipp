
template<typename T>
UIList<T>::UIList() {}

template<typename T>
UIList<T>::UIList(int x, int y, size_t* selected_ptr) : UIElement(x, y, 200, 200) {
    selected_ = selected_ptr;
}

template<typename T>
void UIList<T>::SetVector(const std::vector<T>& original) {
    elements_ = original;
}

template<typename T>
void UIList<T>::Init() {
    list_render_texture_ = std::make_shared<RenderTexture2D>(LoadRenderTexture(box_width_, elements_.size() * y_item_size_));
}

template <typename T>
void UIList<T>::Draw() {
    BeginTextureMode(*list_render_texture_);
    ClearBackground({0, 0, 0, 0});
    for (size_t i = 0; i < elements_.size();  ++i) {
        Color item_color = (i == *selected_) ? ui.ui_accent_color_2 : ui.ui_accent_color_3;
        Color text_color = (i == *selected_) ? ui.ui_text_dark : ui.ui_text_light;

        DrawRectangle(0, i * y_item_size_, box_width_, y_item_size_, item_color);
        DrawRectangleLines(0, i * y_item_size_, box_width_, y_item_size_, ui.ui_line_color);
        DrawText(elements_[i].GetName().c_str(), text_x_offset_ , i * y_item_size_ + text_y_offset_, 14, text_color);
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
}

template <typename T>
void UIList<T>::Update() {
    bool mouse_on_list = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(list_render_texture_->texture.width),
        static_cast<float>(list_render_texture_->texture.height)
    });

    if (mouse_on_list) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            size_t y = static_cast<size_t>(static_cast<float>(elements_.size()) * (GetMousePosition().y - GetAbsoluteYPosition()) / (float)list_render_texture_->texture.height);
            *selected_ = y;
            ui.SetRule();
        } 
    }

    
}