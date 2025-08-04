#include "game_colors.h"

std::vector<GameColor> GameColorFlame() {
    std::vector<GameColor> result(256, GameColor{.r = 0, .g = 0, .b = 0});
        for (size_t i = 0; i < 256; ++i) {
            result[i] = GameColor{.r = static_cast<unsigned char>(std::min<size_t>(i * i + i, 255)), .g = static_cast<unsigned char>(i) , .b = 0};
        }
    result[255] = {10, 5, 5};
    return result;
}

std::vector<GameColor> GameColorNecron() {
    std::vector<GameColor> result(256, GameColor{.r = 0, .g = 0, .b = 0});
        for (size_t i = 0; i < 256; ++i) {
            result[i] = GameColor{.r = static_cast<uint8_t>(240 - std::min<size_t>(240, i * i)), .g = 235 , .b = static_cast<uint8_t>(240 - std::min<size_t>(240, i * i))};
        }
        result[0] = GameColor{.r = 0, .g = 0, .b = 0};
    return result;
}



std::vector<GameColor> GameColorGradient(GameColor a, GameColor b) {
    std::vector<GameColor> result(256, GameColor{.r = 0, .g = 0, .b = 0});
    float offset_r = static_cast<float>(a.r - b.r) / 256.0f;
    float offset_g = static_cast<float>(a.g - b.g) / 256.0f;
    float offset_b = static_cast<float>(a.b - b.b) / 256.0f;
    for (size_t i = 0; i < 256; ++i) {
        result[i] = GameColor{
            .r = static_cast<uint8_t>(static_cast<float>(a.r) - offset_r * static_cast<float>(i)),
            .g = static_cast<uint8_t>(static_cast<float>(a.g) - offset_g * static_cast<float>(i)), 
            .b = static_cast<uint8_t>(static_cast<float>(a.b) - offset_b * static_cast<float>(i))};
    }
    return result;
}

std::vector<GameColor> GameColorBW() {
    return GameColorGradient({0, 0, 0}, {255, 255, 255});
}


std::vector<GameColor> GameColorGradient(std::vector<GameColor> clrs, std::vector<size_t> pos) {
    std::vector<GameColor> result(256, GameColor{.r = 0, .g = 0, .b = 0});
    for (size_t i = 0; i < clrs.size() - 1; ++i) {
        GameColor s = clrs[i];
        GameColor f = clrs[i + 1];
        float offset_r = static_cast<float>(s.r - f.r) / static_cast<float>(pos[i + 1] - pos[i]);
        float offset_g = static_cast<float>(s.g - f.g) / static_cast<float>(pos[i + 1] - pos[i]);
        float offset_b = static_cast<float>(s.b - f.b) / static_cast<float>(pos[i + 1] - pos[i]);
        for (size_t j = pos[i]; j <= pos[i + 1]; ++j) {
            result[j] = GameColor{
                .r = static_cast<uint8_t>(static_cast<float>(s.r) - offset_r * static_cast<float>(j - pos[i])),
                .g = static_cast<uint8_t>(static_cast<float>(s.g) - offset_g * static_cast<float>(j - pos[i])), 
                .b = static_cast<uint8_t>(static_cast<float>(s.b) - offset_b * static_cast<float>(j - pos[i]))};
        }
    }
    return result;
}


std::vector<GameColor> GameColorWater() {
    std::vector<GameColor> clrs{
        {7, 19, 33}, 
        {37, 78, 139},
        {21, 118, 155},
        {171, 243, 254}};
    return GameColorGradient(clrs, {0, 78, 150, 255});
}

std::vector<GameColor> GameColorPinkGreen() {
    std::vector<GameColor> clrs{
        {0, 0, 0}, 
        {106, 254, 18},
        {255, 17, 32},
        {0, 0, 0}};
    return GameColorGradient(clrs, {0, 78, 150, 255});
}

std::vector<GameColor> GameColorPaint() {
    std::vector<GameColor> clrs{
        {240, 240, 235}, 
        {30, 153, 67},
        {180, 79, 3},
        {7, 16, 175}};
    return GameColorGradient(clrs, {0, 78, 150, 255});
}

std::vector<GameColor> GameColorSand() {
    std::vector<GameColor> clrs{
        {0, 0, 0}, 
        {123, 67, 36},
        {243, 179, 90},
        {148, 106, 56}};
    return GameColorGradient(clrs, {0, 78, 150, 255});
}

std::vector<GameColor> GameColorAqua() {
    std::vector<GameColor> clrs{
        {0, 0, 0}, 
        {34, 40, 65}, 
        {34, 62, 102}, 
        {34, 104, 139}, 
        {28, 184, 189}, 
        {38, 226, 163}};
    return GameColorGradient(clrs, {0, 30, 78, 100, 150, 255});
}

std::vector<GameColor> GameColorCoral() {
    std::vector<GameColor> clrs{
        {113, 115, 100},
        {111, 134, 157},
        {242, 99, 90},
        {90, 166, 242}};
    return GameColorGradient(clrs, {0, 78, 150, 255});
}

std::vector<GameColor> GameColorRed() {
    std::vector<GameColor> clrs{
        {70, 48, 46},
        {112, 60, 56}, 
        {115, 58, 52}, 
        {197, 44, 33}, 
        {240, 18, 1}};
    return GameColorGradient(clrs, {0, 78, 130, 180, 255});
}

std::vector<GameColor> GameColorFuxia() {
    std::vector<GameColor> clrs{
        {0, 0, 0}, 
        {69, 54, 66}, 
        {113, 43, 69}, 
        {169, 12, 85}, 
        {250, 0, 117}};
    return GameColorGradient(clrs, {0, 78, 130, 180, 255});
}

std::vector<GameColor> GameColorHighContrast() {
    std::vector<GameColor> clrs{
        {0, 0, 0},
        {85, 73, 128},
        {121, 73, 128},
        {123, 128, 73},
        {228, 18, 255},
        {61, 0, 255},
        {234, 255, 18}};
    return GameColorGradient(clrs, {0, 78, 90, 120, 150, 190, 255});
}

std::vector<GameColor> GameColorElf() {
    std::vector<GameColor> clrs{
        {0, 0, 0},
        {40, 87, 87}, 
        {23, 204, 204}, 
        {154, 194, 224}, 
        {167, 207, 237}, 
        {233, 182, 210}, 
        {245, 182, 210}, 
        {255, 194, 214}};
    return GameColorGradient(clrs, {0, 78, 90, 120, 150, 170, 220, 255});
}


std::vector<ColorElement> ALL_PALLETTES {
    { "Flame", GameColorFlame() },
    { "Necron", GameColorNecron() },
    { "BW", GameColorBW() },
    { "Water", GameColorWater() },
    { "Pink&Green", GameColorPinkGreen() },
    { "Paint", GameColorPaint() },
    { "Sand", GameColorSand() },
    { "Aqua", GameColorAqua() },
    { "Coral", GameColorCoral() },
    { "Red", GameColorRed() },
    { "Fuxia", GameColorFuxia() },
    { "HC", GameColorHighContrast() },
    { "Elf", GameColorElf() }
};