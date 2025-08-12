#include "game_rule.h"


GameRule::GameRule() {}

GameRule::GameRule(
  const std::string& name, 
  size_t neight_to_arrive, 
  size_t neigh_to_survive, 
  uint8_t maximum_age, 
  size_t radius,
  bool count_central) :

  name(name),
  neigh_to_arrive(neight_to_arrive),
  neight_to_survive(neigh_to_survive),
  maximum_age(maximum_age),
  radius(radius),
  count_central(count_central)
{}


bool GameRule::is_arriving(size_t neigh_count) { return neigh_to_arrive & (1ul << (neigh_count)); }

bool GameRule::is_surviving(size_t neigh_count) { return neight_to_survive & (1ul << (neigh_count)); }

const std::string& GameRule::GetName() { return name; } 

void GameRule::SafeRuleToFile(const std::string& path) {
  std::ofstream out(path + "/" + name + ".txt");
  out << "DEFAULT" << std::endl;
  std::bitset<sizeof(size_t)> neigh_to_arrive_bit(neigh_to_arrive);
  std::bitset<sizeof(size_t)> neigh_to_getting_older_bit(neight_to_survive);
  out << neigh_to_arrive_bit << std::endl;
  out << neigh_to_getting_older_bit << std::endl;
  out << maximum_age;
  out << radius;
  out << count_central;
}


GameRuleInterval::GameRuleInterval(
    const std::string& name0, 
    std::vector<std::pair<size_t, size_t>> neight_to_arrive_v, 
    std::vector<std::pair<size_t, size_t>> neigh_to_survive_v, 
    uint8_t maximum_age0, 
    size_t radius0,
    bool count_central0
  ) : 
  //GameRule::name(name), 
  neight_to_arrive(std::vector<bool>((2 * radius0 + 1) * (2 * radius0 + 1), false)),
  neigh_to_survive(std::vector<bool>((2 * radius0 + 1) * (2 * radius0 + 1), false))
  //GameRule::maximum_age(maximum_age), 
  //GameRule::radius(radius)
  {
    GameRule::name = name0;
    GameRule::maximum_age = maximum_age0;
    GameRule::radius = radius0;
    count_central = count_central0;

    for (const auto& pair : neight_to_arrive_v) {
      for (size_t i = pair.first; i <= pair.second; ++i) {
        neight_to_arrive[i] = true;
      }
    }

    for (const auto& pair : neigh_to_survive_v) {
      for (size_t i = pair.first; i <= pair.second; ++i) {
        neigh_to_survive[i] = true;
      }
    }
  }

bool GameRuleInterval::is_arriving(size_t neigh_count) {
  if (neigh_count >= neight_to_arrive.size()) {
    return false;
  }
  return neight_to_arrive[neigh_count];
}
bool GameRuleInterval::is_surviving(size_t neigh_count) {
  if (neigh_count >= neigh_to_survive.size()) {
    return false;
  }
  return neigh_to_survive[neigh_count];
}




//https://habr.com/ru/articles/719324/
GameRule GameRule_STATIC = GameRule {"Static", 0, 0, 1};
GameRule GameRule_DEFAULT = GameRule {"Default", 0b000001000, 0b000001100, 1};
GameRule GameRule_DEFAULT100GEN = GameRule {"Default 100 gen", 0b000001000, 0b000001100, 100};

GameRule GameRule_DIAMEB = GameRule {"Diameba", 0b111101000, 0b111100000, 1};
GameRule GameRule_TREE = GameRule {"Tree", 0b000000010, 0b111111111, 1};
GameRule GameRule_TREEGENER = GameRule {"Tree gen", 0b000000010, 0b010101011, 15};

GameRule GameRule_FREESTAR = GameRule {"Freestar", 0b000000100, 0b000111001, 9};
GameRule GameRule_STARWARS = GameRule {"Starwars", 0b000000100, 0b000111000, 3};

GameRule GameRule_STICKS = GameRule {"Sticks", 0b000000100, 0b001111000, 5};
GameRule GameRule_FADES = GameRule {"Fades", 0b000000100, 0b000000100, 24};
GameRule GameRule_SPIRALS = GameRule {"Spirals", 0b001111100, 0b001110010, 15};
GameRule GameRule_REPLS = GameRule {"Replicators", 0b010001000, 0b000111000, 3};
GameRule GameRule_TR_GR = GameRule {"Thrill Grill", 0b000011000, 0b000111110, 47};
GameRule GameRule_INF = GameRule {"Inf", 0b000001000, 0b000111110, 1};
GameRule GameRule_LINES = GameRule {"Lines", 0b100110000, 0b000111111, 2};

GameRule GameRule_TRANSERSI = GameRule {"transers I", 0b001000100, 0b000111001, 5};
GameRule GameRule_TRANSERSII = GameRule {"transers II", 0b001000100, 0b000111000, 4};


GameRule GameRule_MODERNART = GameRule {"Modern art", 0b000001000, 0b000000110, 255, 10};
GameRule GameRule_MODERNART1 = GameRule {"Modern art 2", 0b000000100, 0b000000110, 255, 10};
GameRule GameRule_MODERNART2 = GameRule {"Modern art 3", 0b00001000, 0b000000110, 9, 10};

GameRule GameRule_BOSCO = GameRule {"Bosco default", 0x3FFC00000000ull, 0x3FF'FFFE'0000'0000ull, 1, 5 };
GameRule GameRule_BOSCO2 = GameRule {"Bosco 2", 0x3FFC00000000ull, 0x3FF'FFFE'0000'0000ull, 2, 6 };
GameRule GameRule_BOSCO3 = GameRule {"Bosco 3", 0x3FFFC0000000ull, 0x3FF'FFF0'0000'0000ull, 5, 7 };
GameRule GameRule_BOSCO4 = GameRule {"Bosco 4", 0x4FFFA0000000ull, 0x6FF'FFF'E0000'0000ull, 7, 7 };
GameRule GameRule_TEST1 = GameRule {"Test", 0b010101010, 0b100110011, 8};

GameRuleInterval GameRule_LIQUIDMS = GameRuleInterval ("Liquid methuseblob soup", {{52, 60}}, {{58, 90}}, 1, 6, true);
GameRuleInterval GameRule_GLOBE = GameRuleInterval ("Globe", {{74, 252}}, {{163, 223}}, 1, 8, false);


GameRuleInterval GameRule_DEFAULT_I = GameRuleInterval ("Default but Interval", {{3, 3}}, {{2, 3}}, 1, 1, false);
GameRuleInterval GameRule_BOSCO_I = GameRuleInterval ("BOSCO but Interval", {{34, 45}}, {{33, 57}}, 1, 5, false);

GameRuleInterval GameRule_BUGS = GameRuleInterval ("Bugs", {{63, 82}}, {{64, 109}}, 4, 7, false);

GameRuleInterval GameRule_BUGSR3 = GameRuleInterval ("Bugs radius = 3", {{14, 18}}, {{14, 23}}, 1, 3, false);


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

void SafeAllRulesToFiles(const::std::string& path) {

}