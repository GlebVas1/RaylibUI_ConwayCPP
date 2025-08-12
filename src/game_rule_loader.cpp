#include "game_rule_loader.h"


GameRuleLoader::GameRuleLoader() {}

GameRuleLoader::~GameRuleLoader() {}

GameRuleLoader& GameRuleLoader::GetInstance() {
  static GameRuleLoader obj;
  return obj;
}

const std::vector<std::string>& GameRuleLoader::GetAllNames() {
  return names_;
}

void GameRuleLoader::LoadRuleFromFile(const std::string& name, const std::string& path) {
  std::ifstream in(path);
  std::string type;
  in >> type;
  if (type == "DEFAULT") {
    std::bitset<sizeof(size_t) * 8> neigh_to_arrive_bit;
    in >> neigh_to_arrive_bit;
    std::bitset<sizeof(size_t) * 8> neight_to_survive_bit;
    in >> neight_to_survive_bit;
    int max_age;
    in >> max_age;
    size_t radius;
    in >> radius;
    bool count_central;
    in >> count_central;
    default_rules_.push_back(GameRule(
      name,
      neigh_to_arrive_bit.to_ullong(),
      neight_to_survive_bit.to_ullong(),
      static_cast<uint8_t>(max_age),
      radius,
      count_central
    ));
  } else {
    size_t pair_count;
    in >> pair_count;
    std::vector<std::pair<size_t, size_t>> neigh_to_arrive_vect(pair_count);
    for (size_t i = 0; i < pair_count; ++i) {
      in >> neigh_to_arrive_vect[i].first >> neigh_to_arrive_vect[i].second;
    }
    in >> pair_count;
    std::vector<std::pair<size_t, size_t>> neigh_to_survive_vect(pair_count);
    for (size_t i = 0; i < pair_count; ++i) {
      in >> neigh_to_survive_vect[i].first >> neigh_to_survive_vect[i].second;
    }
    int max_age;
    in >> max_age;
    size_t radius;
    in >> radius;
    bool count_central;
    in >> count_central;
    interval_rules_.push_back(GameRuleInterval(
      name,
      neigh_to_arrive_vect,
      neigh_to_survive_vect,
      static_cast<uint8_t>(max_age),
      radius,
      count_central
    ));
  }
}

void GameRuleLoader::LoadAllRules(const std::string& path) {
  std::ifstream all_rules_file(path);
  std::string rule_name;
  std::string rule_path;

  while (!all_rules_file.eof()){
    all_rules_file >> rule_name >> rule_path;
    LoadRuleFromFile(rule_name, rule_path); 
  }

  all_rules_file.close();

  for (auto& rule : default_rules_) {
    all_rules_.push_back(&rule);
    names_.push_back(rule.name);
  }

  for (auto& rule : interval_rules_) {
    all_rules_.push_back(&rule);
    names_.push_back(rule.name);
  }
}

GameRule* GameRuleLoader::GetRandomRule(
    int arrive_probability,
    int survive_probability,
    int max_age,
    int radius,
    bool count_central
) 
{
  std::bitset<sizeof(size_t) * 8> neigh_to_arrive;
  for (size_t i = 0; i < 64; ++i) {
    neigh_to_arrive[i] = (rand() % 100) < arrive_probability; 
  }

  std::bitset<sizeof(size_t) * 8> neigh_to_survive;
  for (size_t i = 0; i < 64; ++i) {
    neigh_to_survive[i] = (rand() % 100) < survive_probability; 
  }

  this_rule_ = GameRule(
    "rand",
    neigh_to_arrive.to_ullong(),
    neigh_to_survive.to_ullong(),
    static_cast<uint8_t>(max_age),
    radius,
    count_central
  );

  return &this_rule_;
}

GameRule* GameRuleLoader::GetRuleById(size_t ind) {
  return all_rules_[ind];
}