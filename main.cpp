#include "stdafx.h"
#include "raylib.h"
#include "controller.h"

#include "game_rule.h"

int main() {
  ChangeDirectory(GetApplicationDirectory());
  srand(time(NULL));
/*   SaveAllRulesToFiles("../GameRules"); */
  Controller& main_controller = Controller::GetInstance();
  main_controller.Start();
}

