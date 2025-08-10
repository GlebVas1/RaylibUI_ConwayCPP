#pragma once
#include "stdafx.h"
#include "ui_button.h"

class UITextButton : public UIButton {
    private: 
    std::string text_;
    
    public:
    UITextButton(
        int x_pos, 
        int y_pos, 
        int width, 
        int height, 
        float roundness, 
        std::function<void()> func, 
        const std::string& text
    );

    void Draw() override;
};