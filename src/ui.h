
#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "UI_elements/ui_element_class.h"

#include "UI_elements/ui_main_canvas.h"
#include "UI_elements/ui_pallete.h"
#include "UI_elements/ui_panel.h"

#include "UI_elements/ui_spinbox.h"
#include "UI_elements/ui_label.h"


#include "UI_elements/ui_check_box.h"
#include "UI_elements/ui_toogle.h"


#include "ui_color_theme.h"

#include "UI_elements/ui_text_fromat.h"

class Controller;


class UI : public UIColorTheme {
    private:

    UI();
    ~UI();
    std::vector<UIElement*> elements_;

    std::shared_ptr<UIElement> null_widget_;

    Controller* controller_ = nullptr;
    int window_width = 1920;
    int window_height = 1080;

    
    std::shared_ptr<UIPanel> main_canvas_panel_ = nullptr;
    std::shared_ptr<UIMainCanvas> main_canvas_ = nullptr;


    std::shared_ptr<UIPallete> pallete_ = nullptr;

    int brush_radius_ = 45;
    bool brush_round_ = false;
    bool brush_random_ = false;
    bool brush_object_mode_ = false;
    std::shared_ptr<UISpinBox<int>> brush_size_spinbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_round_checkbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_random_checkbox_ = nullptr;
    std::shared_ptr<UIPanel> brush_settings_panel_ = nullptr;
    std::shared_ptr<UIToggle> brush_object_toogle_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_label_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_size_label_ = nullptr;
    
    void UpdateUIElements();

    void DrawElement(UIElement* root);

    void DrawUIElements();

   

    public: 

    float asd = 232.12354f;

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