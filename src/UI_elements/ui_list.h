#pragma once
#include "stdafx.h"
#include "ui_element_class.h"

class UIList : public UIElement {
    private:
    std::vector<std::string> elements_;
    std::shared_ptr<RenderTexture2D> list_render_texture_;
    size_t* selected_ = nullptr;
    int y_item_size_ = 22;
    
    int box_height = 200;
    int text_x_offset_ = 5;
    int text_y_offset_ = 2;

    void UpdateTexture();

    int vertical_offset = 0;

    int slider_height_= 10;
    int slider_width_= 15;

    int slider_box_x_space_ = 30;
    int slider_line_y_offset_ = 10;
    int slider_line_width_ = 5;


    float slider_position_ = 0.5f;

    public:
    void Init() override;
    UIList();
    UIList(int x, int y, int width, int height, size_t* selected_ptr);
    void SetVector(const std::vector<std::string>& original);
    void Draw() override;
    void Update() override;
    //void Update() override;
};
