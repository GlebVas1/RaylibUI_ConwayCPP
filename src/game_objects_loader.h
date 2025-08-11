#pragma once
#include "game_objects.h"
#include "stdafx.h"

class GameObjectLoader {
 private:
  static const size_t max_size_to_show_grid = 20;
  GameObjectLoader();
  std::vector<GameObject> objects_;
  std::vector<std::string> names_;
  void LoadObject(const std::string& name, const std::string& path);

 public:
  static GameObjectLoader& GetInstance();
  void AddGameObject(const GameObject& obj);
  void LoadAllObjects(const std::string& path);

  const GameObject& GetObjectById(size_t id);
  const std::vector<std::string>& GetAllNames();
};