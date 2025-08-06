#pragma once
#include "stdafx.h"

struct GameRule {
  std::string name = "DEFAULT";
/* 1 for this byte val
    0b010000100 means 7 and 2
 */
  size_t neigh_to_die = 0b111110011;
  size_t neigh_to_arrive = 0b000001000;
  size_t neigh_to_getting_older = 0b111110011;
  unsigned char maximum_age = 6;
  size_t radius = 1;
  
/* I've never thought that I'd code it like this */
  bool is_dying(size_t neigh_count) { return neigh_to_die & (1ul << (neigh_count)); }
  bool is_arriving(size_t neigh_count) { return neigh_to_arrive & (1ul << (neigh_count)); }
  bool is_getting_older(size_t neigh_count) { return neigh_to_getting_older & (1ul << (neigh_count)); }
  const std::string& GetName() { return name; } 
};

//https://habr.com/ru/articles/719324/
extern GameRule GameRule_STATIC;
extern GameRule GameRule_DEFAULT;
extern GameRule GameRule_DEFAULT100GEN;

extern GameRule GameRule_DIAMEB;
extern GameRule GameRule_TREE;
extern GameRule GameRule_TREEGENER;


extern GameRule GameRule_FREESTAR;
extern GameRule GameRule_STARWARS;

extern GameRule GameRule_STICKS;
extern GameRule GameRule_FADES;
extern GameRule GameRule_SPIRALS;
extern GameRule GameRule_REPLS;
extern GameRule GameRule_TR_GR;
extern GameRule GameRule_INF;
extern GameRule GameRule_LINES;

extern std::vector<GameRule> ALL_RULES;