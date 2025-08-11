#pragma once
#include "stdafx.h"


struct GameColor {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

struct ColorElement {
  std::string name;
  std::vector<GameColor> pallette;
};

extern std::vector<ColorElement> ALL_PALLETTES;