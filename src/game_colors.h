#pragma once
#include "stdafx.h"

struct GameColor {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
};

std::vector<GameColor> GameColorBW();
std::vector<GameColor> GameColorFlame();