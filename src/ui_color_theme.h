#pragma once
#include "raylib.h"
#include "stdafx.h"
#include "game_colors.h"

struct UIColorTheme {
    std::string name = "default";
    Color ui_background_color = {80, 90, 90, 255 };

    Color ui_light_color = {150, 170, 170, 255 }; // light
    Color ui_neutral_color = {120, 130, 130, 255 }; // neutral
    Color ui_dark_color = {50, 50, 50, 255 }; // dark

    Color ui_color_hovered = {200, 200, 200, 255};
    Color ui_color_pressed = {100, 100, 100, 255};

    Color ui_line_color = BLACK;
    float line_default_thikness = 2;
    float line_narrow_thikness = 1;
    float line_thick_thikness = 2;

    Color ui_text_dark = BLACK;
    Color ui_text_light = WHITE;

    float panel_corner_radius = 5.0f;
    float elements_corner_radius = 2.0f;
};





class UIColorThemeManager {
    private:
    std::vector<UIColorTheme> themes_;
    UIColorTheme current_theme_;
    UIColorThemeManager();

    public:
    static UIColorThemeManager& GetInstance();
    const UIColorTheme& GetTheme();
    void SetTheme(size_t ind);

    void LoadThemeFromFile(const std::string& name, const std::string& path);
    void LoadAllThemes(const std::string& path);
    void LoadFromPalette(const std::vector<GameColor>& palette);



    const std::vector<UIColorTheme>& GetThemes();
};

// Just make for spinbox
struct UIColorThemeIterator {
    UIColorThemeIterator();
    UIColorThemeIterator(int);
    
    bool operator<(const UIColorThemeIterator& other) const;

    UIColorThemeIterator& operator+=(const UIColorThemeIterator&);
    UIColorThemeIterator& operator-=(const UIColorThemeIterator&);
    UIColorThemeIterator& operator=(const UIColorThemeIterator&);
    
    const std::string& GetName() const;
    size_t GetValue();

    private:
    size_t current_index_ = 0;
};