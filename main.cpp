#include "stdafx.h"
#include "ui.h"
/* #include "field.h" */
#include "game_colors.h"
#include "game_rule.h"
#include "controller.h"

#include "UI_Tools/ui_tools.h"
/* class A {
    public:
    A() {}
    A(int ) {}
    virtual void f() {}
};

class B : public A {
    public:
    virtual void f() {
        std::cout << "f2" << std::endl;
    }
};

class C : public B {
    public:
    void f() {
        std::cout << "f3" << std::endl;
    }
}; */

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

  ChangeDirectory(GetApplicationDirectory());
  
  srand(time(NULL));
  Controller& main_controller = Controller::GetInstance();
  std::cout << "II " << std::endl;
  main_controller.Start();
  std::cout << "III " << std::endl;

  
  //auto a = std::make_shared<C>();
}

