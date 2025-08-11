#pragma once
#include "raylib.h"
#include "stdafx.h"


class UITextureLoader {
 private:
  UITextureLoader();
  ~UITextureLoader();
  std::unordered_map<std::string, Texture2D> map_;

 public:
  static UITextureLoader& GetInstance();
  void LoadTextureFromFile(std::string name, std::string path);
  Texture2D* GetTexture(std::string name);
  void LoadAllTextures();
};