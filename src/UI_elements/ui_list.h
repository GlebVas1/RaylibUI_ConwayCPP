#pragma once
#include "stdafx.h"
#include "ui_element_class.h"
#include "../UI_Tools/ui_tools.h"
#include "raylib.h"

template <typename T>
class UIList : public UIElement {
    private:
    std::vector<T> elements_;
    std::shared_ptr<RenderTexture2D> list_render_texture_;
    size_t* selected_ = nullptr;
    int y_item_size_ = 22;
    int box_width_ = 175;
    int box_height = 200;
    int text_x_offset_ = 5;
    int text_y_offset_ = 6;

    void UpdateTexture();

    public:
    void Init() override;
    UIList();
    UIList(int x, int y, size_t* selected_ptr);
    void SetVector(const std::vector<T>& original);
    void Draw() override;
    void Update() override;
    //void Update() override;
};

#include "ui_list.ipp"