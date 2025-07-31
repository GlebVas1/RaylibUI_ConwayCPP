#include "stdafx.h"
#include "ui.h"
/* #include "field.h" */
#include "game_colors.h"
#include "game_rule.h"
#include "controller.h"
int main() {

  //std::cout << "A1" << std::endl;
  //UI& ui = UI::GetInstance();
  /* Field& f = Field::GetInstance();

  ui.SetColorBuffer(f.GetColorBuffer());
  f.SetPixels();

  auto gcp = GameColorBW();
  auto gr = GameRule_STATIC;
  
  f.SetColorPallette(&gcp);
  f.SetGameRule(&gr);

  f.CreateUpdateThreads();
  //f.MultiThreadUpdating();
  std::thread t(&Field::MultiThreadUpdating, &f);
  
 // std::thread t1(&Field::show_current_count, &f);
  ui.Start();
  t.join(); */
  /* t1.join(); */
  Controller& main_controller = Controller::GetInstance();
  std::cout << "II " << std::endl;
  main_controller.StartField();
  std::cout << "III " << std::endl;
  main_controller.StartUI();
}