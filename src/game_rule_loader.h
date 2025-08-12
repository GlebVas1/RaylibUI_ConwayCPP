#pragma once
#include "game_rule.h"
#include "stdafx.h"


class GameRuleLoader {
 private:
  GameRuleLoader();
  ~GameRuleLoader();
  std::vector<std::string> names_;
  std::vector<GameRule*> all_rules_;
  std::vector<GameRule> default_rules_;
  std::vector<GameRuleInterval> interval_rules_;
  GameRule this_rule_;
 public:
  static GameRuleLoader& GetInstance();

  const std::vector<std::string>& GetAllNames();
  void LoadRuleFromFile(const std::string& name, const std::string& path);
  void LoadAllRules(const std::string& path);
  
  GameRule* GetRandomRule(
    int arrive_probability,
    int survive_probability,
    int max_age,
    int radius,
    bool count_central
  );

  GameRule* GetRuleById(size_t ind);
};