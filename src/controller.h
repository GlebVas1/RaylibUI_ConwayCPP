#pragma once
#include "stdafx.h"
#include "game_rule.h"
#include "game_objects.h"


class UI;
class Field;

// there cycled dependences obviously cause crush;
class Controller {
 private:
  Field* field;
  UI* ui;
  Controller();
  ~Controller();
  std::thread* field_multi_thread_ = nullptr;

 public:
  static Controller& GetInstance();

  const std::vector<std::string>& GetAllObjectsNames();
  void SetObject(size_t ind);

  void SetFieldPixel(int x, int y, uint8_t val);

  const std::vector<std::string>& GetAllRuleNames();
  void SetFieldRule(size_t ind);
  void SetRandomRule(
    int arrive_probability,
    int survive_probability,
    int max_age,
    int radius,
    bool count_central
  );
  GameRule* GetFieldRule();
  

  const std::vector<std::string>& GetAllPalettesNames();
  void SetPalette(size_t ind);
  
  void SetFieldSize(size_t x, size_t y);
  
  void SetFPS(size_t val);
  float GetFPS();
  void SetPause(float val);

  void SetNewColorBuffer(uint8_t* buffer);

  void StartUI();
  void Start();
};

