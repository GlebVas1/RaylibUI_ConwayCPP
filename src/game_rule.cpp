#include "game_rule.h"

GameRule GameRule_STATIC = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0, .neigh_to_getting_older = 0, .maximum_age = 1};
GameRule GameRule_DEFAULT = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000001000, .neigh_to_getting_older = 0b111110011, .maximum_age = 1};
GameRule GameRule_DEFAULT100GEN = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000001000, .neigh_to_getting_older = 0b111110011, .maximum_age = 100};

GameRule GameRule_DIAMEB = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b111101000, .neigh_to_getting_older = 0b000011111, .maximum_age = 1};
GameRule GameRule_TREE = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000010, .neigh_to_getting_older = 0b000000000, .maximum_age = 1};
GameRule GameRule_TREEGENER = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000010, .neigh_to_getting_older = 0b101010100, .maximum_age = 15};


GameRule GameRule_FREESTAR = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000100, .neigh_to_getting_older = 0b111000110, .maximum_age = 9};
GameRule GameRule_STARWARS = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000100, .neigh_to_getting_older = 0b111000111, .maximum_age = 3};

GameRule GameRule_STICKS = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000100, .neigh_to_getting_older = 0b110000111, .maximum_age = 5};
GameRule GameRule_FADES = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000100, .neigh_to_getting_older = 0b111111011, .maximum_age = 24};
GameRule GameRule_SPIRALS = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b001111100, .neigh_to_getting_older = 0b110001101, .maximum_age = 15};
GameRule GameRule_REPLS = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b010001000, .neigh_to_getting_older = 0b111000111, .maximum_age = 3};
GameRule GameRule_TR_GR = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000011000, .neigh_to_getting_older = 0b111000001, .maximum_age = 47};
GameRule GameRule_INF = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000001000, .neigh_to_getting_older = 0b111000001, .maximum_age = 1};
GameRule GameRule_LINES = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b100110000, .neigh_to_getting_older = 0b111000000, .maximum_age = 2};

std::vector<GameRule> ALL_RULES = std::vector<GameRule>({
  GameRule_STATIC,
  GameRule_DEFAULT,
  GameRule_DEFAULT100GEN,

  GameRule_DIAMEB,
  GameRule_TREE,
  GameRule_TREEGENER,


  GameRule_FREESTAR,
  GameRule_STARWARS,

  GameRule_STICKS,
  GameRule_FADES,
  GameRule_SPIRALS,
  GameRule_REPLS,
  GameRule_TR_GR,
  GameRule_INF,
  GameRule_LINES
});