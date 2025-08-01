#pragma once
#include "stdafx.h"

#include "ui_element_class.h"
#include "game_colors.h"
#include "raylib.h"

#include "ui_mouse_state.h"

class UIPallete : public UIElement {
    private:
    class UIPalleteButton : public UIMouseState {
        int width_ = 0;
        int height_ = 0;
        int x_position_ = 0;
        int y_position_ = 0;
        float roundness_ = 0.3f;
        Color default_c_;
        Color covered_c_;
        Color pressed_c_;
        size_t id_;
        UIPallete* this_pallete;
        public: 
        void SetDimensions(int x, int y);
        void SetPosition(int x, int y);

        void SetXPosition(int x);
        void SetYPosition(int y);

        void Draw();
        void Update();
        
        void SetColors(GameColor c);
        void SetId(size_t id);
        void SetPallete(UIPallete* pallette);
    };

    friend UIPalleteButton;

    std::vector<UIPalleteButton> buttons_;
    size_t colors_count_ = 0;
    std::vector<GameColor> color_pallete_;
    std::vector<uint8_t> color_pallete_val_;
    size_t selected_color_ = 0;
    size_t selected_button = 0;

    int button_width_ = 30;
    int button_height_ = 30;
    int button_width_spacing_= 5;
    int button_height_spacing_ = 5;
    
    float button_roundness_ = 0.4f;

    float roundness_ = 0.1;

    Color background_color_ = {120, 130, 130, 255 };

    void InitializeButtons();
    public:
    void Update() override;
    void Draw() override;
    void Init() override;

    void SetColorPallette(const std::vector<GameColor>& pallette);
    void SetColorCount(size_t color_count);
    void SetSelectedColor(uint8_t val);

    uint8_t GetSelectedColor();

};