#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"
#include "ui_text_component.h"

class UIButton : public UIElement, UIMouseState, UITextComponent {
    private:
        Color default_c_ = { 0, 0, 0, 255};
        Color covered_c_  = { 128, 128, 128, 255};
        Color pressed_c_  = { 0, 0, 0, 255};
        float roundness_;
        std::function<void()> binding;

    public: 
        UIButton();
        UIButton(int width, int height);
        UIButton(int x_pos, int y_pos, int width, int height);
        UIButton(int x_pos, int y_pos, int width, int height, const std::string& str);

        void Draw() override;
        void Update() override;

        void SetRoundness(float roundness);
};