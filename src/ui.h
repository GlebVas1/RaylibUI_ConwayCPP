
#pragma once
#include "game_objects.h"

#include "raylib.h"
#include "stdafx.h"

#include "ui_color_theme.h"
#include "ui_elements_store.h"


class GameRule;

class Controller;

class UI : UIElementsStorage {
 private:
  const size_t default_field_width_ = 512;
  const size_t default_field_height_ = 512;

	const int window_width = 1920;
  const int window_height = 1080;

  UI();
  ~UI();

  std::vector<UIElement*> elements_;

  std::shared_ptr<UIElement> null_widget_;

  Controller* controller_ = nullptr;
  

  void UpdateUIElements();

  void DrawElement(UIElement* root);
  void DrawUIElements();

 public:
  static UI& GetInstance();
	void SetController(Controller* controller);
	void InitializeWindow();
	void InitializeElements();
	void AddUIElement(UIElement* elen_ptr);
  void Start();

  void SetColorBuffer(uint8_t* new_color_buffer);
  void SetPixel(size_t x, size_t y);
	void DrawBrush(size_t x, size_t y);
  
  void SetColorPallette(const std::vector<GameColor>& pallette);
  const std::vector<GameColor>& GetCurrentPalette();
  void InitPalette();
	void UpdatePalette(size_t ind);
  void SetColorCount(size_t color_count);
  void SetSelectedColor(uint8_t val);

  void SetRule(size_t ind);

  void SetGameObjectByIndex(size_t ind);
  void SetGameObject(const GameObject& game_object);

  void SetFrameDelayMilliseconds(size_t val);
  float GetFPS();

  void SetFieldSize();
};