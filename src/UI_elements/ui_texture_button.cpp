#include "ui_texture_button.h"
#include "../UI_Tools/ui_textures_loader.h"
#include "ui.h"

UITextureButton::UITextureButton(
    int x_pos, 
    int y_pos, 
    int width, 
    int height, 
    float roundness, 
    std::function<void()> func, 
    const std::string& texture) :
    UIButton(x_pos, y_pos, width, height, roundness, func) {
        texture_ = UITextureLoader::GetInstance().GetTexture(texture);
}

void UITextureButton::Draw() {
    UIButton::Draw();
    DrawTexturePro(
        *texture_,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(texture_->width),
            static_cast<float>(texture_->height)
        },
        Rectangle{
            static_cast<float>(GetAbsoluteXPosition() + 2),
            static_cast<float>(GetAbsoluteYPosition() + 2),
            static_cast<float>(width_ - 4),
            static_cast<float>(height_ - 4)
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        UIColorThemeManager::GetInstance().GetTheme().ui_dark_color
    );
}