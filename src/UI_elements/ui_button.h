#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"

class UIButton : public UIElement, public UIMouseState {
    protected:
        float roundness_;
        std::function<void()> binding;

    public: 
        UIButton(int x_pos, int y_pos, int width, int height, float roundness, std::function<void()> func);

        void Draw() override;
        void Update() override;

        void SetRoundness(float roundness);
};