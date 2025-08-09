
#pragma once
#include "stdafx.h"
#include "raylib.h"

#include "ui_brush_settings.h"
#include "ui_game_object_settings.h"

#include "UI_elements/ui_element_class.h"

#include "UI_elements/ui_main_canvas.h"
#include "UI_elements/ui_palette.h"
#include "UI_elements/ui_panel.h"

#include "UI_elements/ui_spinbox.h"
#include "UI_elements/ui_label.h"


#include "UI_elements/ui_check_box.h"
#include "UI_elements/ui_toogle.h"
#include "UI_elements/ui_text_button.h"

#include "ui_color_theme.h"

#include "UI_elements/ui_text_fromat.h"
#include "UI_elements/ui_list.h"
#include "UI_elements/ui_object_canvas.h"

#include "UI_elements/ui_texture_button.h"
#include "UI_elements/ui_dual_textured_button.h"

#include "UI_elements/ui_slider.h"
#include "UI_elements/ui_label_print_value.h"

#include "game_objects.h"

class GameRule;

class Controller;

class UI : public UIColorTheme {
    private:

    const size_t default_field_width_ = 512;
    const size_t default_field_height_ = 512;

    UI();
    ~UI();
    std::vector<UIElement*> elements_;

    std::shared_ptr<UIElement> null_widget_;

    Controller* controller_ = nullptr;
    int window_width = 1920;
    int window_height = 1080;

    
    std::shared_ptr<UIPanel> main_canvas_panel_ = nullptr;
    std::shared_ptr<UIMainCanvas> main_canvas_ = nullptr;


    std::shared_ptr<UIPanel> game_control_panel_ = nullptr;
    std::shared_ptr<UIDualTextureButton> game_control_play_button_ = nullptr;
    std::shared_ptr<UIHorizontalSlider<size_t>> game_control_slider_ = nullptr;
    std::shared_ptr<UILabelPrintValue<float>> game_control_panel_fps_label_ = nullptr;

    std::shared_ptr<UIPanel> field_control_panel_ = nullptr;
    std::shared_ptr<UILabel> field_control_label_ = nullptr;

    std::shared_ptr<UISpinBox<size_t>> field_width_spinbox_ = nullptr;
    std::shared_ptr<UISpinBox<size_t>> field_height_spinbox_ = nullptr;
    std::shared_ptr<UIToggle> field_grid_toogle_ = nullptr;
    std::shared_ptr<UIToggle> field_dim_lock_toogle_ = nullptr;

    std::shared_ptr<UITextButton> field_set_button_ = nullptr;

    std::shared_ptr<UISpinBox<int>> brush_size_spinbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_round_checkbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_random_checkbox_ = nullptr;
    std::shared_ptr<UIPanel> brush_settings_panel_ = nullptr;
    std::shared_ptr<UIToggle> brush_object_toogle_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_label_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_size_label_ = nullptr;


    std::shared_ptr<UIPanel> game_object_panel_ = nullptr;
    std::shared_ptr<UIList> game_object_list_ = nullptr;
    std::shared_ptr<UILabel> game_object_label_ = nullptr;
    std::shared_ptr<UIObjectCanvas> game_object_canvas_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_clockwise_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_counter_clockwise_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_mirror_v_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_mirror_h_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_invert_button_ = nullptr;


    std::shared_ptr<UIPanel> game_rule_panel_ = nullptr;
    std::shared_ptr<UIList> game_rule_list_ = nullptr;


    std::shared_ptr<UIPalette> pallete_ = nullptr;


    std::shared_ptr<UIPanel> palette_panel_ = nullptr;
    std::shared_ptr<UIList> palette_list_ = nullptr;
    std::shared_ptr<UILabel> palette_label_ = nullptr;


    void UpdateUIElements();

    void DrawElement(UIElement* root);

    void DrawUIElements();

   

    public: 

    static UI& GetInstance();

    void Start();

    void SetColorBuffer(uint8_t* new_color_buffer);

    void SetPixel(size_t x, size_t y);
    
    void SetController(Controller* controller);

    void InitializeElements();

    void AddUIElement(UIElement* elen_ptr);

    void SetColorPallette(const std::vector<GameColor>& pallette);

    const std::vector<GameColor>& GetCurrentPalette();

    void SetColorCount(size_t color_count);

    void InitializeWindow();

    void InitPalette();

    void SetSelectedColor(uint8_t val);

    void DrawBrush(size_t x, size_t y);

    void SetRule(size_t ind);

    void UpdatePalette(size_t ind);

    

    void SetGameObject(size_t ind);

    void SetGameObject(const GameObject& game_object);

    void GameObjectRotateClockwise();

    void GameObjectRotateCounterClockwise();

    void SetFPS(size_t val);

    float GetFPS();

    void SetFieldSize();

};