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

std::vector<ColorElement> ALL_PALLETTES {
    { "Flame", GameColorFlame() },
    { "Necron", GameColorNecron() },
    { "BW", GameColorBW() },
    { "Water", GameColorWater() },
    { "Pink&Green", GameColorPinkGreen() },
    { "Paint", GameColorPaint() },
    { "Sand", GameColorSand() }
};