#pragma once
#include "game_colors.h"
#include "raylib.h"
#include "stdafx.h"
#include "ui_element_class.h"
#include "ui_mouse_state.h"
#include "ui_shadow_effect.h"


class UIPalette : public UIElement {
 private:
  class UIPaletteButton : public UIMouseState {
    int width_ = 0;
    int height_ = 0;
    int x_position_ = 0;
    int y_position_ = 0;
    Color default_c_;
    Color covered_c_;
    Color pressed_c_;
    size_t id_ = 0;
    UIPalette* this_pallete_ = nullptr;

   public:
    void SetDimensions(int x, int y);

    void SetXPosition(int x);
    void SetYPosition(int y);

    void Draw();
    void Update();

    void SetColors(GameColor c);
    void SetId(size_t id);
    void SetPalette(UIPalette* pallette);
  };

  friend UIPaletteButton;

  std::shared_ptr<UIShadowEffect> shadow_;
  std::vector<UIPaletteButton> buttons_;
  size_t colors_count_ = 0;

  std::vector<GameColor> color_pallete_;
  std::vector<uint8_t> color_pallete_val_;
  size_t selected_val_ = 255;
  size_t selected_button_ = 0;

  static const int button_width_ = 30;
  static const int button_height_ = 26;
  static const int button_width_spacing_ = 5;
  static const int button_height_spacing_ = 5;
  static const int max_height_buttons_count = 15;

  void InitializeButtons();

 public:
  void Init() override;
  void Draw() override;
  void Update() override;

  void SetColorPallette(const std::vector<GameColor>& pallette);
  const std::vector<GameColor>& GetColorPalette();

  void SetColorCount(size_t color_count);

  void SetSelectedVal(uint8_t val);
  uint8_t GetRandomVal();
  uint8_t GetSelectedVal();
};