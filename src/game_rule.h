#pragma once
#include "stdafx.h"


struct GameRule {
  std::string name = "DEFAULT";
/* 1 for this byte val
    0b010000100 means 7 and 2
 */
  size_t neigh_to_die = 0b111110011;
  size_t neigh_to_arrive = 0b000001000;
  size_t neight_to_survive = 0b111110011;
  unsigned char maximum_age = 6;
  size_t radius = 1;
  bool count_central = false;
  
/* I've never thought that I'd code it like this */
  GameRule();
  GameRule(
    const std::string& name, 
    size_t neight_to_arrive, 
    size_t neigh_to_survive, 
    uint8_t maximum_age = 6, 
    size_t radius = 1,
    bool count_central = false
  );

  virtual bool is_arriving(size_t neigh_count);
  virtual bool is_surviving(size_t neigh_count);
  const std::string& GetName();

  virtual void SafeRuleToFile(const std::string& path);
};

struct GameRuleInterval : public GameRule {
  std::vector<bool> neight_to_arrive;
  std::vector<bool> neigh_to_survive;
  GameRuleInterval(
    const std::string& name, 
    std::vector<std::pair<size_t, size_t>> neight_to_arrive_v, 
    std::vector<std::pair<size_t, size_t>> neigh_to_survive_v, 
    uint8_t maximum_age = 6, 
    size_t radius = 1,
    bool count_central = false
  );
  bool is_arriving(size_t neigh_count) override;
  bool is_surviving(size_t neigh_count) override;
  //void SafeRuleToFile(const std::string& path) override;
};

//https://habr.com/ru/articles/719324/
extern std::vector<GameRule*> ALL_RULES;

void SafeAllRulesToFiles(const std::string& path);