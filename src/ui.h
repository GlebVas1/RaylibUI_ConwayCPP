#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "UI_elements/ui_canvas.h"
// #include "UI_elements/ui_button.h"

#include "controller.h"
#include "UI_elements/ui_element_class.h"

class Controller;

class UI {
    private:
    UI();
    ~UI();

    Controller& controller_;
    int window_width = 1200;
    int window_height = 600;

    uint8_t val_to_set_ = 255;
    std::shared_ptr<UICanvas> canvas_ = nullptr;
    public: 

    static UI& GetInstance();

    void Start();

    void SetColorBuffer(uint8_t* new_color_buffer);

    void SetPixel(size_t x, size_t y);
    

};