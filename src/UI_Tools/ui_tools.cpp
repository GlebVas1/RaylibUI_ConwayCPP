#include "ui_tools.h"

namespace UITools {

    Font& GetMainFont() {
        static Font obj(LoadFontEx("../resources/fonts/Hasklig-Regular.ttf", 64, 0, 250));
        return obj;
    }
    void DrawRectangle(int x, int y, int width, int height, int thikness, float roundness, Color background, Color line) {
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
        DrawRectangleRounded(main_field, roundness, 0, background);
        DrawRectangleRoundedLinesEx(main_field_line, roundness, 0, thikness, line);
    }

    void DrawTextDefault(int x, int y, const std::string& str, int font_size, Color col) {
        //DrawText(str.c_str(), x, y, font_size, col);
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
}