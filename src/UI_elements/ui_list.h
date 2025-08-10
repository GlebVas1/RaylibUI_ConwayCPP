#pragma once
#include "stdafx.h"
#include "ui_element_class.h"

class UIList : public UIElement {
    private:
    std::vector<std::string> elements_;
    std::shared_ptr<RenderTexture2D> list_render_texture_;

    int y_item_size_ = 22;
    
    static const int box_height = 200;
    static const int text_x_offset_ = 5;
    static const int text_y_offset_ = 2;

    void UpdateTexture();

    static const int vertical_offset = 0;

    // can change later
    int slider_height_= 10;
    
    static const int slider_width_= 15;

    static const int slider_box_x_space_ = 30;
    static const int slider_line_y_offset_ = 10;
    static const int slider_line_width_ = 5;


    float slider_position_ = 0.5f;

    size_t selected_ind_ = 0;

    std::function<void(size_t)> call_;

    public:
    void Init() override;
    UIList();
    UIList(int x, int y, int width, int height, std::function<void(size_t)> call_);
    void SetVector(const std::vector<std::string>& original);
    void Draw() override;
    void Update() override;
    //void Update() override;
};
