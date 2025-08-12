#pragma once
#include "UI_elements/ui_check_box.h"
#include "UI_elements/ui_dual_textured_button.h"
#include "UI_elements/ui_element_class.h"
#include "UI_elements/ui_label.h"
#include "UI_elements/ui_label_print_value.h"
#include "UI_elements/ui_list.h"
#include "UI_elements/ui_main_canvas.h"
#include "UI_elements/ui_object_canvas.h"
#include "UI_elements/ui_palette.h"
#include "UI_elements/ui_panel.h"
#include "UI_elements/ui_slider.h"
#include "UI_elements/ui_spinbox.h"
#include "UI_elements/ui_text_button.h"
#include "UI_elements/ui_text_fromat.h"
#include "UI_elements/ui_texture_button.h"
#include "UI_elements/ui_toogle.h"
#include "stdafx.h"


class UIElementsStorage {
 protected:
  std::shared_ptr<UIPanel> main_canvas_panel_ = nullptr;
  std::shared_ptr<UIMainCanvas> main_canvas_ = nullptr;

  std::shared_ptr<UIPanel> game_control_panel_ = nullptr;
  std::shared_ptr<UIDualTextureButton> game_control_play_button_ = nullptr;
  std::shared_ptr<UIHorizontalSlider<size_t>> game_control_slider_ = nullptr;
  std::shared_ptr<UILabelPrintValue<float>> game_control_panel_fps_label_ = nullptr;

  std::shared_ptr<UIPanel> field_control_panel_ = nullptr;
  std::shared_ptr<UILabel> field_control_label_ = nullptr;

  std::shared_ptr<UILabel> field_control_size_H_label_ = nullptr;
  std::shared_ptr<UILabel> field_control_size_W_label_ = nullptr;

  std::shared_ptr<UISpinBox<size_t>> field_width_spinbox_ = nullptr;
  std::shared_ptr<UISpinBox<size_t>> field_height_spinbox_ = nullptr;
  std::shared_ptr<UIToggle> field_grid_toogle_ = nullptr;
  std::shared_ptr<UIDualTextureButton> field_dim_lock_button_ = nullptr;

  std::shared_ptr<UITextButton> field_set_button_ = nullptr;

  std::shared_ptr<UISpinBox<int>> brush_size_spinbox_ = nullptr;
  std::shared_ptr<UICheckbox> brush_round_checkbox_ = nullptr;
  std::shared_ptr<UICheckbox> brush_random_checkbox_ = nullptr;
  std::shared_ptr<UIPanel> brush_settings_panel_ = nullptr;
  std::shared_ptr<UIToggle> brush_object_toogle_ = nullptr;
  std::shared_ptr<UILabel> brush_settings_label_ = nullptr;
  std::shared_ptr<UILabel> brush_settings_size_label_ = nullptr;

  std::shared_ptr<UIPanel> game_object_panel_ = nullptr;
  std::shared_ptr<UIList> game_object_list_ = nullptr;
  std::shared_ptr<UILabel> game_object_label_ = nullptr;
  std::shared_ptr<UIObjectCanvas> game_object_canvas_ = nullptr;
  std::shared_ptr<UITextureButton> game_object_clockwise_button_ = nullptr;
  std::shared_ptr<UITextureButton> game_object_counter_clockwise_button_ = nullptr;
  std::shared_ptr<UITextureButton> game_object_mirror_v_button_ = nullptr;
  std::shared_ptr<UITextureButton> game_object_mirror_h_button_ = nullptr;
  std::shared_ptr<UITextureButton> game_object_invert_button_ = nullptr;

  std::shared_ptr<UIPanel> game_rule_panel_ = nullptr;
  std::shared_ptr<UIList> game_rule_list_ = nullptr;
  std::shared_ptr<UILabel> game_rule_label_ = nullptr;

  std::shared_ptr<UIPalette> pallete_ = nullptr;

  std::shared_ptr<UIPanel> palette_panel_ = nullptr;
  std::shared_ptr<UIList> palette_list_ = nullptr;
  std::shared_ptr<UILabel> palette_label_ = nullptr;

  std::shared_ptr<UIPanel> random_rule_panel_ = nullptr;
  std::shared_ptr<UILabel> random_rule_label_ = nullptr;
  std::shared_ptr<UISpinBox<int>> random_rule_survive_prob_ = nullptr;
  std::shared_ptr<UILabel> random_rule_survive_label_ = nullptr;
  std::shared_ptr<UISpinBox<int>> random_rule_arrive_prob_ = nullptr;
  std::shared_ptr<UILabel> random_rule_arrive_label_ = nullptr;
  std::shared_ptr<UISpinBox<int>> random_rule_generation_ = nullptr;
  std::shared_ptr<UILabel> random_rule_generation_label_ = nullptr;
  std::shared_ptr<UISpinBox<int, false>> random_rule_radius_ = nullptr;
  std::shared_ptr<UILabel> random_rule_radius_label_ = nullptr;
  std::shared_ptr<UICheckbox> random_central_ = nullptr;
  std::shared_ptr<UITextureButton> random_rule_set_ = nullptr;

  std::shared_ptr<UIPanel> color_theme_panel_ = nullptr;
  std::shared_ptr<UILabel> color_theme_label_ = nullptr;
  std::shared_ptr<UISpinBox<UIColorThemeIterator, false>> color_theme_spinbox_ = nullptr;
  std::shared_ptr<UICheckbox> color_theme_from_palette_ = nullptr;
};