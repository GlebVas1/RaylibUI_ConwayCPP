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
  bool count_central = false;
  
/* I've never thought that I'd code it like this */
  GameRule();
  GameRule(
    const std::string& name, 
    size_t neight_to_die, 
    size_t neight_to_arrive, 
    size_t neigh_to_getting_older, 
    uint8_t maximum_age = 6, 
    size_t radius = 1,
    bool count_central = false
  );

  virtual bool is_dying(size_t neigh_count);
  virtual bool is_arriving(size_t neigh_count);
  virtual bool is_getting_older(size_t neigh_count);
  const std::string& GetName();
};

struct GameRuleInterval : public GameRule {
  std::vector<bool> neight_to_die;
  std::vector<bool> neight_to_arrive;
  std::vector<bool> neigh_to_getting_older;
  GameRuleInterval(
    const std::string& name, 
    std::vector<std::pair<size_t, size_t>> neight_to_die_v, 
    std::vector<std::pair<size_t, size_t>> neight_to_arrive_v, 
    std::vector<std::pair<size_t, size_t>> neigh_to_getting_older_v, 
    uint8_t maximum_age = 6, 
    size_t radius = 1,
    bool count_central = false
  );
  bool is_arriving(size_t neigh_count) override;
  bool is_getting_older(size_t neigh_count) override;
  bool is_dying(size_t neight_count) override;
};

//https://habr.com/ru/articles/719324/
extern std::vector<GameRule*> ALL_RULES;