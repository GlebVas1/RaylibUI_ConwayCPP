#pragma once
#include "stdafx.h"
#include "raylib.h"

namespace UITools {
    void DrawRectangle(int x, int y, int width, int height,  int thikness, float roundness, Color background, Color line);
    void DrawText(int x, int y, const std::string& str, int font_size, Color col);
}