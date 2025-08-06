#include "game_rule.h"

GameRule::GameRule() {}

GameRule::GameRule(
  const std::string& name, 
  size_t neight_to_die, 
  size_t neight_to_arrive, 
  size_t neigh_to_getting_older, 
  uint8_t maximum_age, 
  size_t radius,
  bool count_central) :
  name(name),
  neigh_to_die(neight_to_die),
  neigh_to_arrive(neight_to_arrive),
  neigh_to_getting_older(neigh_to_getting_older),
  maximum_age(maximum_age),
  radius(radius),
  count_central(count_central)
{}


GameRuleInterval::GameRuleInterval(
    const std::string& name0, 
    std::vector<std::pair<size_t, size_t>> neight_to_die_v, 
    std::vector<std::pair<size_t, size_t>> neight_to_arrive_v, 
    std::vector<std::pair<size_t, size_t>> neigh_to_getting_older_v, 
    uint8_t maximum_age0, 
    size_t radius0,
    bool count_central0
  ) : 
  //GameRule::name(name), 
  neight_to_die(std::vector<bool>((2 * radius0 + 1) * (2 * radius0 + 1), false)),
  neight_to_arrive(std::vector<bool>((2 * radius0 + 1) * (2 * radius0 + 1), false)),
  neigh_to_getting_older(std::vector<bool>((2 * radius0 + 1) * (2 * radius0 + 1), true))
  //GameRule::maximum_age(maximum_age), 
  //GameRule::radius(radius)
  {
    GameRule::name = name0;
    GameRule::maximum_age = maximum_age0;
    GameRule::radius = radius0;
    count_central = count_central0;

    for (const auto& pair : neight_to_die_v) {
      for (size_t i = pair.first; i <= pair.second; ++i) {
        neight_to_die[i] = true;
      }
    }

    for (const auto& pair : neight_to_arrive_v) {
      for (size_t i = pair.first; i <= pair.second; ++i) {
        neight_to_arrive[i] = true;
      }
    }

    for (const auto& pair : neigh_to_getting_older_v) {
      for (size_t i = pair.first; i <= pair.second; ++i) {
        neigh_to_getting_older[i] = false;
      }
    }
  }

bool GameRuleInterval::is_arriving(size_t neigh_count) {
  return neight_to_arrive[neigh_count];
}
bool GameRuleInterval::is_getting_older(size_t neigh_count) {
  return neigh_to_getting_older[neigh_count];
}
bool GameRuleInterval::is_dying(size_t neigh_count) {
  return neight_to_die[neigh_count];
}


bool GameRule::is_dying(size_t neigh_count) { return neigh_to_die & (1ul << (neigh_count)); }
bool GameRule::is_arriving(size_t neigh_count) { return neigh_to_arrive & (1ul << (neigh_count)); }
bool GameRule::is_getting_older(size_t neigh_count) { return neigh_to_getting_older & (1ul << (neigh_count)); }
const std::string& GameRule::GetName() { return name; } 

//https://habr.com/ru/articles/719324/
GameRule GameRule_STATIC = GameRule {"Static", 0, 0, 0, 1};
GameRule GameRule_DEFAULT = GameRule {"Default", 0, 0b000001000, 0b111110011, 1};
GameRule GameRule_DEFAULT100GEN = GameRule {"Default 100 gen", 0, 0b000001000, 0b111110011, 100};

GameRule GameRule_DIAMEB = GameRule {"Diameba", 0, 0b111101000, 0b000011111, 1};
GameRule GameRule_TREE = GameRule {"Tree", 0, 0b000000010, 0b000000000, 1};
GameRule GameRule_TREEGENER = GameRule {"Tree gen", 0, 0b000000010, 0b101010100, 15};

GameRule GameRule_FREESTAR = GameRule {"Freestar", 0, 0b000000100, 0b111000110, 9};
GameRule GameRule_STARWARS = GameRule {"Starwars", 0, 0b000000100, 0b111000111, 3};

GameRule GameRule_STICKS = GameRule {"Sticks", 0, 0b000000100, 0b110000111, 5};
GameRule GameRule_FADES = GameRule {"Fades", 0, 0b000000100, 0b111111011, 24};
GameRule GameRule_SPIRALS = GameRule {"Spirals", 0, 0b001111100, 0b110001101, 15};
GameRule GameRule_REPLS = GameRule {"Replicators", 0, 0b010001000, 0b111000111, 3};
GameRule GameRule_TR_GR = GameRule {"Thrill Grill", 0, 0b000011000, 0b111000001, 47};
GameRule GameRule_INF = GameRule {"Inf", 0, 0b000001000, 0b111000001, 1};
GameRule GameRule_LINES = GameRule {"Lines", 0, 0b100110000, 0b111000000, 2};

GameRule GameRule_TRANSERSI = GameRule {"transers I", 0, 0b001000100, 0b111000110, 5};
GameRule GameRule_TRANSERSII = GameRule {"transers II", 0, 0b001000100, 0b111000111, 4};


GameRule GameRule_MODERNART = GameRule {"Modern art", 0, 0000001000, 0b111111001, 255, 10};
GameRule GameRule_MODERNART1 = GameRule {"Modern art 2", 0, 0000000100, 0b111111001, 255, 10};
GameRule GameRule_MODERNART2 = GameRule {"Modern art 3", 0, 000001000, 0b111111001, 9, 10};

GameRule GameRule_BOSCO = GameRule {"Bosco default", 0, 0x3FFC00000000ull, ~0x3FF'FFFE'0000'0000ull, 1, 5 };
GameRule GameRule_BOSCO2 = GameRule {"Bosco 2", 0, 0x3FFC00000000ull, ~0x3FF'FFFE'0000'0000ull, 2, 6 };
GameRule GameRule_BOSCO3 = GameRule {"Bosco 3", 0, 0x3FFFC0000000ull, ~0x3FF'FFF0'0000'0000ull, 5, 7 };
GameRule GameRule_BOSCO4 = GameRule {"Bosco 4", 0, 0x4FFFA0000000ull, ~0x6FF'FFF'E0000'0000ull, 7, 7 };
GameRule GameRule_TEST1 = GameRule {"Test", 0, 0b010101010, 0b100110011, 8};

GameRuleInterval GameRule_LIQUIDMS = GameRuleInterval ("Liquid methuseblob soup", {}, {{52, 60}}, {{58, 90}}, 1, 6, true);
GameRuleInterval GameRule_GLOBE = GameRuleInterval ("Globe", {}, {{74, 252}}, {{163, 223}}, 1, 8, false);


GameRuleInterval GameRule_DEFAULT_I = GameRuleInterval ("Default but Interval", {}, {{3, 3}}, {{2, 3}}, 1, 1, false);
GameRuleInterval GameRule_BOSCO_I = GameRuleInterval ("BOSCO but Interval", {}, {{34, 45}}, {{33, 57}}, 1, 5, false);

GameRuleInterval GameRule_BUGS = GameRuleInterval ("Bugs", {}, {{63, 82}}, {{64, 109}}, 4, 7, false);

GameRuleInterval GameRule_BUGSR3 = GameRuleInterval ("Bugs radius = 3", {}, {{14, 18}}, {{14, 23}}, 1, 3, false);


std::vector<GameRule*> ALL_RULES = std::vector<GameRule*>({
 &GameRule_STATIC,
 &GameRule_DEFAULT,
 &GameRule_DEFAULT100GEN,

 &GameRule_DIAMEB,
 &GameRule_TREE,
 &GameRule_TREEGENER,

 &GameRule_FREESTAR,
 &GameRule_STARWARS,

 &GameRule_STICKS,
 &GameRule_FADES,
 &GameRule_SPIRALS,
 &GameRule_REPLS,
 &GameRule_TR_GR,
 &GameRule_INF,
 &GameRule_LINES,
 &GameRule_TRANSERSI,
 &GameRule_TRANSERSII,

 &GameRule_MODERNART,
 &GameRule_MODERNART1,
 &GameRule_MODERNART2,

 &GameRule_BOSCO,
 &GameRule_BOSCO2,
 &GameRule_BOSCO3,
 &GameRule_BOSCO4,
 &GameRule_TEST1,
 &GameRule_LIQUIDMS,
 &GameRule_DEFAULT_I,
 &GameRule_BOSCO_I,
 &GameRule_GLOBE,
 &GameRule_BUGS,
 &GameRule_BUGSR3
});