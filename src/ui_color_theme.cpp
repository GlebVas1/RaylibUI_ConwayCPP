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

void UIColorThemeManager::SetTheme(size_t ind) {
    current_theme_ = themes_[ind];
}

const std::vector<UIColorTheme>& UIColorThemeManager::GetThemes() {
    return themes_;
}

void UIColorThemeManager::LoadThemeFromFile(const std::string& name, const std::string& path) {
    UIColorTheme theme;
    std::ifstream theme_file(path);
    struct {
        int r;
        int g;
        int b;
        int a;
    } true_color;

    auto load_color = [&true_color, &theme_file]() -> Color {
        theme_file >> true_color.r >> true_color.g >> true_color.b >> true_color.a;
        return {
            static_cast<uint8_t>(true_color.r),
            static_cast<uint8_t>(true_color.g),
            static_cast<uint8_t>(true_color.b),
            static_cast<uint8_t>(true_color.a)
        };
    };
    
    theme.ui_background_color = load_color();
    theme.ui_light_color = load_color();
    theme.ui_neutral_color = load_color();
    theme.ui_dark_color = load_color();
    
    theme.ui_color_hovered = load_color();
    theme.ui_color_pressed = load_color();
    
    theme.ui_line_color = load_color();
    theme_file >> theme.line_default_thikness;
    theme_file >> theme.line_narrow_thikness;
    theme_file >> theme.line_thick_thikness;

    theme.ui_text_dark = load_color();
    theme.ui_text_light = load_color();
    theme_file.close();

    theme.name = name;
    themes_.push_back(theme);

    theme_file.close();
    std::cout << "Loaded " << name << std::endl;
}

void UIColorThemeManager::LoadAllThemes(const std::string& path) {
    std::ifstream all_themes(path);
    std::string theme_name;
    std::string theme_path;
    
    while (!all_themes.eof()){
        all_themes >> theme_name >> theme_path;
        LoadThemeFromFile(theme_name, theme_path); 
    }

    all_themes.close();
}

void UIColorThemeManager::LoadFromPalette(const std::vector<GameColor>& palette) {
    auto load_color_from_palette = [&palette, this](size_t ind) -> Color {
        return {
            palette[ind].r, 
            palette[ind].g, 
            palette[ind].b, 
            255
        };
    };
    current_theme_.ui_background_color = load_color_from_palette(30);
    current_theme_.ui_light_color = load_color_from_palette(160);
    current_theme_.ui_neutral_color = load_color_from_palette(120);
    current_theme_.ui_dark_color = load_color_from_palette(80);
    
    current_theme_.ui_color_hovered = {200, 200, 200, 255};
    current_theme_.ui_color_pressed = {150, 150, 150, 255};
    
    current_theme_.ui_line_color = load_color_from_palette(10);
    current_theme_.line_default_thikness = 2;
    current_theme_.line_narrow_thikness = 1;
    current_theme_.line_thick_thikness = 2;

    current_theme_.ui_text_dark = load_color_from_palette(0);
    current_theme_.ui_text_light = load_color_from_palette(255);
}

UIColorThemeIterator::UIColorThemeIterator() {}
UIColorThemeIterator::UIColorThemeIterator(int) {}

UIColorThemeIterator& UIColorThemeIterator::operator+=(const UIColorThemeIterator&) {
    current_index_ = (current_index_ + 1) % UIColorThemeManager::GetInstance().GetThemes().size();
    return *this;
}

UIColorThemeIterator& UIColorThemeIterator::operator-=(const UIColorThemeIterator&) {
    current_index_ = (UIColorThemeManager::GetInstance().GetThemes().size() + current_index_ - 1) % UIColorThemeManager::GetInstance().GetThemes().size();
    return *this;
}

UIColorThemeIterator& UIColorThemeIterator::operator=(const UIColorThemeIterator&) {
    return *this;
}

bool UIColorThemeIterator::operator<(const UIColorThemeIterator& other) const {
    return current_index_ < other.current_index_;
}

const std::string& UIColorThemeIterator::GetName() const {
    return UIColorThemeManager::GetInstance().GetThemes()[current_index_].name;
}

size_t UIColorThemeIterator::GetValue() {
    return current_index_;
}
