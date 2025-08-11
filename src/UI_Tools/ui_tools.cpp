#include "ui_tools.h"

namespace UITools {

    Font& GetMainFont() {
        static Font obj(LoadFontEx("../resources/fonts/Hasklig-Regular.ttf", 64, 0, 250));
        return obj;
    }

    void DrawRectangle(
        int x, 
        int y, 
        int width, 
        int height, 
        float thikness, 
        float corner_radius, 
        Color background, 
        Color line) 
        {
        Rectangle main_field{
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(width),
            static_cast<float> (height)
        };

        Rectangle main_field_line{
            static_cast<float>(x + 1),
            static_cast<float>(y + 1),
            static_cast<float>(width - 1),
            static_cast<float> (height - 1)
        };

        float roundness = corner_radius / std::min(width, height);

        DrawRectangleRounded(main_field, roundness, 4, background);
        
        if (thikness > 0) {
            DrawRectangleRoundedLinesEx(main_field_line, roundness, 4, thikness, line);
        }
    }

    void DrawTextDefault(int x, int y, const std::string& str, int font_size, Color col) {
        DrawTextEx(
            GetMainFont(), 
            str.c_str(), 
            Vector2{
                static_cast<float>(x), 
                static_cast<float>(y)
            }, 
            font_size, 
            0.8f, 
            col);
    }

    std::pair<int, int> MeasureTextDefault(const std::string& str, int font_size) {
        const auto size = MeasureTextEx(GetMainFont(), str.c_str(), font_size, 0.8f);
        return { static_cast<int>(size.x), static_cast<int>(size.y)};
    }
}