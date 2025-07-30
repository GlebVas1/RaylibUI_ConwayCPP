#include "stdafx.h"
#include "ui.h"
#include "field.h"
#include "game_colors.h"
#include "game_rule.h"

int main() {
  std::cout << "A";
  UI& ui = UI::GetInstance();
  Field& f = Field::GetInstance();

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
  t.join();
  /* t1.join(); */
}