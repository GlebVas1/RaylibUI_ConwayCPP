#include "ui_color_theme.h"

UIColorThemeManager::UIColorThemeManager() {

}

UIColorThemeManager& UIColorThemeManager::GetInstance() {
    static UIColorThemeManager obj;
    return obj;
}

const UIColorTheme& UIColorThemeManager::GetTheme() {
    return current_theme_;
}

void UIColorTheme::LoadThemeFromFile(const std::string& path) {
    std::ifstream file(path);
    file >> ui_background_color.r >> ui_background_color.g >> ui_background_color.b >> ui_background_color.a;

    file >> ui_light_color.r >> ui_light_color.g >> ui_light_color.b >> ui_light_color.a;
    file >> ui_neutral_color.r >> ui_neutral_color.g >> ui_neutral_color.b >> ui_neutral_color.a;
    file >> ui_dark_color.r >> ui_dark_color.g >> ui_dark_color.b >> ui_dark_color.a;
    
    file >> ui_color_hovered.r >> ui_color_hovered.g >> ui_color_hovered.b >> ui_color_hovered.a;
    file >> ui_color_pressed.r >> ui_color_pressed.g >> ui_color_pressed.b >> ui_color_pressed.a;
    
    file >> ui_line_color.r >> ui_line_color.g >> ui_line_color.b >> ui_line_color.a;
    file >> line_thikness;

    file >> ui_text_dark.r >> ui_text_dark.g >> ui_text_dark.b >> ui_text_dark.a;
    file >> ui_text_light.r >> ui_text_light.g >> ui_text_light.b >> ui_text_light.a;
}

void UIColorTheme::LoadMap(const std::string& path) {

}