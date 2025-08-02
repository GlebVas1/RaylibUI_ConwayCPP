#include "game_rule.h"
int ABOBA = 1;

GameRule GameRule_STATIC = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0, .neigh_to_getting_older = 0, .maximum_age = 1};
GameRule GameRule_DEFAULT = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000001000, .neigh_to_getting_older = 0b111110011, .maximum_age = 1}; 
GameRule GameRule_FREESTAR = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b000000100, .neigh_to_getting_older = 0b111000110, .maximum_age = 9};
GameRule GameRule_SPIRALS = GameRule {.neigh_to_die = 0, .neigh_to_arrive = 0b001111100, .neigh_to_getting_older = 0b110001101, .maximum_age = 15};