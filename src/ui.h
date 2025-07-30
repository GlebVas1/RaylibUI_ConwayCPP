#pragma once
#include "stdafx.h"
#include "raylib.h"
#include "field.h"

#include "UI_elements/ui_canvas.h"

class UI {
    private:
    UI();
    ~UI();
    int window_width = 600;
    int window_height = 600;

    std::shared_ptr<UICanvas> canvas_ = nullptr;
    public: 

    static UI& GetInstance();

    void Start();

    void SetColorBuffer(uint8_t* new_color_buffer);

};