#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "UI_elements/ui_canvas.h"
#include "UI_elements/ui_pallete.h"
// #include "UI_elements/ui_button.h"

#include "UI_elements/ui_element_class.h"
#include "ui_color_theme.h"

class Controller;

class UI : public UIColorTheme {
    private:
    UI();
    ~UI();
    std::vector<UIElement*> elements_;

    Controller* controller_ = nullptr;
    int window_width = 1920;
    int window_height = 1080;

    std::shared_ptr<UICanvas> canvas_ = nullptr;
    std::shared_ptr<UIPallete> pallete_ = nullptr;

    void UpdateUIElements();
    void DrawUIElements();

    int brush_radius_ = 45;

    public: 

    static UI& GetInstance();

    void Start();

    void SetColorBuffer(uint8_t* new_color_buffer);

    void SetPixel(size_t x, size_t y);
    
    void SetController(Controller* controller);

    void InitializeElements();

    void AddUIElement(UIElement* elen_ptr);

    void SetColorPallette(const std::vector<GameColor>& pallette);

    void SetColorCount(size_t color_count);

    void SetSelectedColor(uint8_t val);

    void DrawBrush(size_t x, size_t y);
};