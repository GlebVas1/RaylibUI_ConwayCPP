#pragma once
#include "game_colors.h"
#include "game_objects.h"
#include "stdafx.h"
#include "ui_canvas.h"

class UIObjectCanvas : public UICanvas {
 private:
  GameObject this_object_;
  size_t BufferIndex(size_t size, size_t x, size_t y);
  void DrawObject();

 public:
  UIObjectCanvas();
  ~UIObjectCanvas();

  void Init() override;
  void Update() override;

  void SetObject(const GameObject& object);
  const GameObject& GetObject();

  void UpdatePalette(const std::vector<GameColor>& palette);

  void SetPixel(size_t x, size_t y, uint8_t val);
  uint8_t GetPixel(size_t x, size_t y);

  void GameObjectRotateClockwise();
  void GameObjectRotateCounterClockwise();
  void GameObjectMirrorVertical();
  void GameObjectMirrorHorizontal();
  void GameObjectInvert();
};