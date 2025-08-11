#include "ui_main_canvas.h"
#include "ui.h"

void UIMainCanvas::Update() {
    bool mouse_on_canvas = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float>(height_)
    });

    if (mouse_on_canvas) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            size_t x = static_cast<size_t>(static_cast<float>(main_texture_width_) * (GetMousePosition().x - GetAbsoluteXPosition()) / width_);
            size_t y = static_cast<size_t>(static_cast<float>(main_texture_height_) * (GetMousePosition().y - GetAbsoluteYPosition()) / height_);
            UI::GetInstance().DrawBrush(y, x);
        } 
    }
}
