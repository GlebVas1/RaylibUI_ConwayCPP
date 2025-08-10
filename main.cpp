#include "stdafx.h"
#include "raylib.h"
#include "controller.h"


int main() {
  ChangeDirectory(GetApplicationDirectory());
  srand(time(NULL));

  Controller& main_controller = Controller::GetInstance();
  main_controller.Start();
}

