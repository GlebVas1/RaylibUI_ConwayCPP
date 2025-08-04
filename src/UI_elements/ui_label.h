#pragma once
#include "stdafx.h"
#include "ui_element_class.h"

class UILabel : public UIElement {
    std::string text_;
    public:
    UILabel();
    UILabel(int x, int y, const std::string& text);
    void Draw() override;
};