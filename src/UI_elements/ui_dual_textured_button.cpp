#include "ui_dual_textured_button.h"
#include "ui.h"
#include "../UI_Tools/ui_textures_loader.h"

UIDualTextureButton::UIDualTextureButton(
    int x, 
    int y, 
    int width, 
    int height, 
    float roundness,
    std::function<void(bool)> func, 
    const std::string& true_state, 
    const std::string& false_state,
    bool initial_state
    ) :
    UIButton(
        x, 
        y, 
        width, 
        height, 
        roundness,
    [](){}) 
{
    current_state_ = initial_state;
    UIButton::binding_ = [this, func]() {
        current_state_ = !current_state_;
        func(current_state_);
    };
    true_state_ = UITextureLoader::GetInstance().GetTexture(true_state);
    false_state_ = UITextureLoader::GetInstance().GetTexture(false_state);
}

void UIDualTextureButton::Draw() {
    UIButton::Draw();
    const Texture2D* this_texture = current_state_ ? true_state_ : false_state_;
    DrawTexturePro(
        *this_texture,
        Rectangle{
            0.0f,
            0.0f,
            static_cast<float>(this_texture->width),
            static_cast<float>(this_texture->height)
        },
        Rectangle{
            static_cast<float>(GetAbsoluteXPosition() + 2),
            static_cast<float>(GetAbsoluteYPosition() + 2),
            static_cast<float>(width_ - 4),
            static_cast<float>(height_ - 4)
        },
        Vector2{0.0f, 0.0f},
        0.0f,
        ui.ui_accent_color_3
    );
}

void UIDualTextureButton::SetState(bool val) {
    current_state_ = val;
}

bool UIDualTextureButton::GetState() {
    return current_state_;
}