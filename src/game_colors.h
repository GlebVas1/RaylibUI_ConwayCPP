#pragma once
#include "stdafx.h"

struct GameColor {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

std::vector<GameColor> GameColorFlame();
std::vector<GameColor> GameColorNecron();
std::vector<GameColor> GameColorWater();
std::vector<GameColor> GameColorPinkGreen();
std::vector<GameColor> GameColorBW();
std::vector<GameColor> GameColorPaint();
std::vector<GameColor> GameColorSand();
std::vector<GameColor> GameColorAqua();
std::vector<GameColor> GameColorCoral();
std::vector<GameColor> GameColorRed();
std::vector<GameColor> GameColorFuxia();
std::vector<GameColor> GameColorHighContrast();
std::vector<GameColor> GameColorElf();

struct ColorElement {
  std::string name;
  std::vector<GameColor> pallette;
};

extern std::vector<ColorElement> ALL_PALLETTES;