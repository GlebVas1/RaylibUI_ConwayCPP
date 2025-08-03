#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "raylib.h"

template <typename T>
class UIList : public UIElement {
    private:
    std::vector<T> elements_;
    size_t* selected_ = 0;
    int y_size_ = 22;
    int box_width_ = 175;
    int box_height = 200;
    int text_x_offset_ = 5;
    int text_y_offset_ = 2;
    public:
    UIList();
    UIList(int x, int y);
    void SetVector(const std::vector<T>& original);
    void Draw() override;
    void Update() override;
};

#include "ui_list.ipp"