#pragma once
#include "raylib.h"
#include "stdafx.h"

struct UIColorTheme {
    std::string name = "default";
    Color ui_background_color = {80, 90, 90, 255 };

    Color ui_light_color = {150, 170, 170, 255 }; // light
    Color ui_neutral_color = {120, 130, 130, 255 }; // neutral
    Color ui_dark_color = {50, 50, 50, 255 }; // dark

    Color ui_color_hovered = {0, 0, 0, 40};
    Color ui_color_pressed = {0, 0, 0, 90};

    Color ui_line_color = BLACK;
    int line_thikness = 2;

    Color ui_text_dark = BLACK;
    Color ui_text_light = WHITE;

    void LoadThemeFromFile(const std::string& path);

    void LoadMap(const std::string& path);
};

class UIColorThemeManager {
    private:
    std::unordered_map<std::string, std::string> map_;
    UIColorTheme current_theme_;
    UIColorThemeManager();

    public:
    static UIColorThemeManager& GetInstance();
    const UIColorTheme& GetTheme();
};

