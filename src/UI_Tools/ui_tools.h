#pragma once
#include "stdafx.h"
#include "raylib.h"

namespace UITools {
    void DrawRectangle(int x, int y, int width, int height, float thikness, float corner_radius, Color background, Color line);
    void DrawTextDefault(int x, int y, const std::string& str, int font_size, Color col);
    std::pair<int, int> MeasureTextDefault(const std::string& str, int font_size);
    Font& GetMainFont();
}