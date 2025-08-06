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
    UIButton::binding = [this, func]() {
        current_state_ = !current_state_;
        func(current_state_);
    };
    true_state_ = UITextureLoader::GetInstance().GetTexture(true_state);
    false_state_ = UITextureLoader::GetInstance().GetTexture(false_state);
}

void UIDualTextureButton::Draw() {
    UIButton::Draw();
    if (current_state_) {
        DrawTexturePro(
            *true_state_,
            Rectangle{
                0.0f,
                0.0f,
                static_cast<float>(true_state_->width),
                static_cast<float>(true_state_->height)
            },
            Rectangle{
                static_cast<float>(GetAbsoluteXPosition() + 2),
                static_cast<float>(GetAbsoluteYPosition() + 2),
                static_cast<float>(width_ - 4),
                static_cast<float>(height_ - 4)
            },
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE
        );
    } else {
        DrawTexturePro(
            *false_state_,
            Rectangle{
                0.0f,
                0.0f,
                static_cast<float>(false_state_->width),
                static_cast<float>(false_state_->height)
            },
            Rectangle{
                static_cast<float>(GetAbsoluteXPosition() + 2),
                static_cast<float>(GetAbsoluteYPosition() + 2),
                static_cast<float>(width_ - 4),
                static_cast<float>(height_ - 4)
            },
            Vector2{0.0f, 0.0f},
            0.0f,
            WHITE
        );
    }
}

void UIDualTextureButton::SetState(bool val) {
    current_state_ = val;
}

bool UIDualTextureButton::GetState() {
    return current_state_;
}