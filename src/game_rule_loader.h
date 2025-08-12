#pragma once
#include "game_rule.h"
#include "stdafx.h"

class GameRuleLoader {
 private:
  GameRuleLoader();
  std::vector<std::string> names_;
  std::vector<GameRule*> all_rules_;
  std::vector<GameRule> default_rules_;
  std::vector<GameRuleInterval> interval_rules_;
  GameRule* this_rule_;

 public:
  static GameRuleLoader& GetInstance();
  void LoadDefaultRule(const std::string& path);
  void LoadIntervalRule(const std::string& path);
  void LoadAllRules();
};