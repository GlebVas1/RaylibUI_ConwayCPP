#include "ui.h"
#include "controller.h"
#include "game_rule.h"
#include "ui_color_theme.h"


void UI::InitializeElements() {
  const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();

  null_widget_ = std::make_shared<UIElement>();

  right_upper_null_widget_ = std::make_shared<UIElement>(0, 0, 0, 0);
  right_upper_null_widget_->SetParrent(null_widget_.get());

  panel_null_widget_ = std::make_shared<UIElement>(-420, 40, 0, 0);
  panel_null_widget_->SetParrent(right_upper_null_widget_.get());
  
  main_canvas_panel_ = std::make_shared<UIPanel>(20, 0, 1080, 1080, this_theme.panel_corner_radius);
  main_canvas_panel_->SetParrent(null_widget_.get());
  main_canvas_panel_->Init();

  main_canvas_ = std::make_shared<UIMainCanvas>();
  main_canvas_->SetParrent(main_canvas_panel_.get());
  main_canvas_->SetPosition(5, 5);
  main_canvas_->SetDimensions(1070, 1070);

  game_control_panel_ = std::make_shared<UIPanel>(0, 0, 385, 50, this_theme.panel_corner_radius);
  game_control_panel_->SetParrent(panel_null_widget_.get());
  game_control_panel_->Init();
  
  game_control_play_button_ = std::make_shared<UIDualTextureButton>(
    5, 
    5, 
    40, 
    40, 
    this_theme.elements_corner_radius,
    [this](bool val) { controller_->SetPause(val); },
    "pause",
    "play",
    false
  );
  game_control_play_button_->SetParrent(game_control_panel_.get());

  game_control_slider_ = std::make_shared<UIHorizontalSlider<size_t>>(
    60, 
    10, 
    200, 
    30, 
    [this](size_t val) {
      SetFrameDelayMilliseconds(val);
  });
  game_control_slider_->SetParrent(game_control_panel_.get());
  
  game_control_panel_fps_label_ = std::make_shared<UILabelPrintValue<float>>(
    275,
    16,
    "FPS: %3.02f",
    [this]() -> float { return GetFPS(); }
  );
  game_control_panel_fps_label_->SetParrent(game_control_panel_.get());

  field_control_panel_ = std::make_shared<UIPanel>(0, 70, 385, 70, this_theme.panel_corner_radius);
  field_control_panel_->SetParrent(panel_null_widget_.get());
  field_control_panel_->Init();

  field_control_label_ = std::make_shared<UILabel>(10, 8, "Field settings");
  field_control_label_->SetParrent(field_control_panel_.get());

  field_grid_toogle_ = std::make_shared<UIToggle>(
    10, 
    40, 
    [this](bool val){ main_canvas_->SetShowGrid(val); }, 
    "Grid"
  );
  field_grid_toogle_->SetParrent(field_control_panel_.get());

  field_dim_lock_button_ = std::make_shared<UIDualTextureButton>(
    265, 
    25, 
    20,
    20,
    this_theme.elements_corner_radius,
    [this](bool val){}, 
    "lock",
    "unlock",
    true
  );
  field_dim_lock_button_->SetParrent(field_control_panel_.get());

  field_width_spinbox_ = std::make_shared<UISpinBox<size_t>>(
    315, 
    10, 
    [this](size_t val) {
      if (field_dim_lock_button_->GetState()) {
        float ratio = static_cast<float>(main_canvas_->GetWidth()) / main_canvas_->GetHeight();
        field_height_spinbox_->SetValue(static_cast<int>(ratio * field_width_spinbox_->GetValue()));
      }
    }, 
    10
  );

  field_width_spinbox_->SetMinValue(30);
  field_width_spinbox_->SetMaxValue(1060);
  field_width_spinbox_->SetValue(default_field_width_);
  field_width_spinbox_->SetParrent(field_control_panel_.get());
  field_width_spinbox_->Init();

  field_control_size_H_label_ = std::make_shared<UILabel>(295, 12, "H:");
  field_control_size_H_label_->SetParrent(field_control_panel_.get());

  field_height_spinbox_ = std::make_shared<UISpinBox<size_t>>(
    315, 
    40, 
    [this](size_t val) {
      if (field_dim_lock_button_->GetState()) {
        float ratio = static_cast<float>(main_canvas_->GetHeight()) / main_canvas_->GetWidth();
        field_width_spinbox_->SetValue(static_cast<int>(ratio * field_height_spinbox_->GetValue()));
      }
    }, 
    10
  );

  field_height_spinbox_->SetMinValue(30);
  field_height_spinbox_->SetMaxValue(1060);
  field_height_spinbox_->SetValue(default_field_height_);
  field_height_spinbox_->SetParrent(field_control_panel_.get());
  field_height_spinbox_->Init();

  field_control_size_W_label_ = std::make_shared<UILabel>(295, 42, "W:");
  field_control_size_W_label_->SetParrent(field_control_panel_.get());

  field_set_button_ = std::make_shared<UITextButton>(
    180, 
    25, 
    70, 
    20, 
    this_theme.elements_corner_radius, 
    [this](){ SetFieldSize(); }, 
    "Resize"
  );
  field_set_button_->SetParrent(field_control_panel_.get());


  brush_settings_panel_ = std::make_shared<UIPanel>(180, 160, 145, 160, this_theme.panel_corner_radius);
  brush_settings_panel_->SetParrent(panel_null_widget_.get());
  brush_settings_panel_->Init();

  brush_settings_label_ = std::make_shared<UILabel>(10, 10, "Brush settings");
  brush_settings_label_->SetParrent(brush_settings_panel_.get());

  brush_size_spinbox_ = std::make_shared<UISpinBox<int>>(
    10, 
    40, 
    [this](int value){ }, 
    1.0f
  );

  brush_size_spinbox_->SetMaxValue(100);
  brush_size_spinbox_->SetMinValue(1);
  brush_size_spinbox_->SetValue(1);
  brush_size_spinbox_->SetParrent(brush_settings_panel_.get());
  brush_size_spinbox_->Init();

  brush_settings_size_label_ = std::make_shared<UILabel>(80, 43, "Size");
  brush_settings_size_label_->SetParrent(brush_settings_panel_.get());

  brush_round_checkbox_ = std::make_shared<UICheckbox>(
    10, 
    70, 
    [this](bool val) { }, 
    "Round"
  );
  brush_round_checkbox_->SetParrent(brush_settings_panel_.get());

  brush_random_checkbox_ = std::make_shared<UICheckbox>(
    10, 
    100, 
    [this](bool val) { }, 
    "Random"
  );
  brush_random_checkbox_->SetParrent(brush_settings_panel_.get());

  brush_object_toogle_ = std::make_shared<UIToggle>(
    10, 
    130, 
    [this](bool val) { }, 
    "Object"
  
  );
  brush_object_toogle_->SetParrent(brush_settings_panel_.get());

  pallete_ = std::make_shared<UIPalette>();
  pallete_->SetXPosition(345);
  pallete_->SetYPosition(160);
  pallete_->SetParrent(panel_null_widget_.get());

  palette_panel_ = std::make_shared<UIPanel>(180, 340, 145, 290, this_theme.panel_corner_radius);
  palette_panel_->SetParrent(panel_null_widget_.get());
  palette_panel_->Init();

  palette_list_ = std::make_shared<UIList>(
    10, 
    40, 
    135, 
    240, 
    [this](size_t ind) { UpdatePalette(ind); }
  );

  palette_list_->SetParrent(palette_panel_.get());
  palette_list_->SetVector(controller_->GetAllPalettesNames());
  palette_list_->Init();

  palette_label_ = std::make_shared<UILabel>(10, 10, "Palette");
  palette_label_->SetParrent(palette_panel_.get());

  game_object_panel_ = std::make_shared<UIPanel>(0, 160, 160, 470, this_theme.panel_corner_radius);
  game_object_panel_->SetParrent(panel_null_widget_.get());
  game_object_panel_->Init();

  game_object_label_ = std::make_shared<UILabel>(10, 10, "Game objects");
  game_object_label_->SetParrent(game_object_panel_.get());

  game_object_list_ = std::make_shared<UIList>(
    10, 
    40, 
    150, 
    200, 
    [this](size_t ind){ SetGameObjectByIndex(ind); }
  );

  game_object_list_->SetParrent(game_object_panel_.get());
  game_object_list_->SetVector(controller_->GetAllObjectsNames());
  game_object_list_->Init();

  game_object_canvas_ = std::make_shared<UIObjectCanvas>();
  game_object_canvas_->SetParrent(game_object_panel_.get());
  game_object_canvas_->SetPosition(5, 315);
  game_object_canvas_->SetDimensions(150, 150); 

  game_object_clockwise_button_ = std::make_shared<UITextureButton>(
    10, 
    250, 
    25, 
    25, 
    this_theme.elements_corner_radius, 
    [this](){ game_object_canvas_->GameObjectRotateClockwise(); }, 
    "clock_wise");
  game_object_clockwise_button_->SetParrent(game_object_panel_.get());

  game_object_counter_clockwise_button_ = std::make_shared<UITextureButton>(
    40, 
    250, 
    25, 
    25, 
    this_theme.elements_corner_radius, 
    [this](){ game_object_canvas_->GameObjectRotateCounterClockwise(); }, 
    "counter_clock_wise");
  game_object_counter_clockwise_button_->SetParrent(game_object_panel_.get());

  game_object_mirror_v_button_ = std::make_shared<UITextureButton>(
    10, 
    280, 
    25, 
    25, 
    this_theme.elements_corner_radius, 
    [this](){ game_object_canvas_->GameObjectMirrorVertical(); }, 
    "mirror_v");
  game_object_mirror_v_button_->SetParrent(game_object_panel_.get());

  game_object_mirror_h_button_ = std::make_shared<UITextureButton>(
    40, 
    280, 
    25, 
    25, 
    this_theme.elements_corner_radius, 
    [this](){ game_object_canvas_->GameObjectMirrorHorizontal(); }, 
    "mirror_h");
  game_object_mirror_h_button_->SetParrent(game_object_panel_.get());

  game_object_invert_button_ = std::make_shared<UITextureButton>(
    70, 
    250, 
    55, 
    55, 
    this_theme.elements_corner_radius, 
    [this](){ game_object_canvas_->GameObjectInvert(); }, 
    "invert");
  game_object_invert_button_->SetParrent(game_object_panel_.get());

  game_rule_panel_ = std::make_shared<UIPanel>(0, 650, 180, 200, this_theme.panel_corner_radius);
  game_rule_panel_->SetParrent(panel_null_widget_.get());
  game_rule_panel_->Init();

  game_rule_list_ = std::make_shared<UIList>(10, 40, 170, 150, [this](size_t ind) { SetRule(ind); });
  game_rule_list_->SetParrent(game_rule_panel_.get());

  game_rule_label_ = std::make_shared<UILabel>(10, 8, "Game rule settings");
  game_rule_label_->SetParrent(game_rule_panel_.get());

  game_rule_list_->SetVector(controller_->GetAllRuleNames());
  game_rule_list_->Init();

  random_rule_panel_ = std::make_shared<UIPanel>(200, 650, 185, 200, this_theme.panel_corner_radius);
  random_rule_panel_->SetParrent(panel_null_widget_.get());
  random_rule_panel_->Init();

  random_rule_label_ = std::make_shared<UILabel>(10, 8, "Random rule");
  random_rule_label_->SetParrent(random_rule_panel_.get());

  random_rule_survive_prob_ = std::make_shared<UISpinBox<int>>(
    10,
    50,
    [](int){},
    1
  );
  random_rule_survive_prob_->SetMinValue(0);
  random_rule_survive_prob_->SetMaxValue(100);
  random_rule_survive_prob_->SetValue(50);
  random_rule_survive_prob_->SetParrent(random_rule_panel_.get());
  random_rule_survive_prob_->Init();

  random_rule_survive_label_ = std::make_shared<UILabel>(80, 52, "Survive %");
  random_rule_survive_label_->SetParrent(random_rule_panel_.get());

  random_rule_arrive_prob_ = std::make_shared<UISpinBox<int>>(
    10,
    80,
    [](int){},
    1
  );
  random_rule_arrive_prob_->SetMinValue(0);
  random_rule_arrive_prob_->SetMaxValue(100);
  random_rule_arrive_prob_->SetValue(50);
  random_rule_arrive_prob_->SetParrent(random_rule_panel_.get());
  random_rule_arrive_prob_->Init();

  random_rule_arrive_label_ = std::make_shared<UILabel>(80, 82, "Arrive %");
  random_rule_arrive_label_->SetParrent(random_rule_panel_.get());

  random_rule_generation_ = std::make_shared<UISpinBox<int>>(
    10,
    110,
    [](int){},
    1
  );
  random_rule_generation_->SetMinValue(1);
  random_rule_generation_->SetValue(1);
  random_rule_generation_->SetMaxValue(250);
  random_rule_generation_->SetParrent(random_rule_panel_.get());
  random_rule_generation_->Init();

  random_rule_generation_label_ = std::make_shared<UILabel>(80, 112, "Max. age");
  random_rule_generation_label_->SetParrent(random_rule_panel_.get());

  random_rule_radius_ = std::make_shared<UISpinBox<int, false>>(
    10,
    140,
    [](int){},
    1
  );
  random_rule_radius_->SetMinValue(1);
  random_rule_radius_->SetMaxValue(6);
  random_rule_radius_->SetValue(1);
  random_rule_radius_->SetParrent(random_rule_panel_.get());
  random_rule_radius_->Init();

  random_rule_radius_label_ = std::make_shared<UILabel>(80, 142, "Radius");
  random_rule_radius_label_->SetParrent(random_rule_panel_.get());

  random_rule_set_ = std::make_shared<UITextureButton>(
    145,
    10,
    30,
    30,
    this_theme.elements_corner_radius,
    [this](){
      controller_->SetRandomRule(
        random_rule_arrive_prob_->GetValue(),
        random_rule_survive_prob_->GetValue(),
        random_rule_generation_->GetValue(),
        random_rule_radius_->GetValue(),
        random_central_->GetValue()
      );
    },
    "load"
  );
  random_rule_set_->SetParrent(random_rule_panel_.get());

  random_central_ = std::make_shared<UICheckbox>(
    10,
    170,
    [](bool){},
    "Count self"
  );
  random_central_->SetParrent(random_rule_panel_.get());

  color_theme_panel_ = std::make_shared<UIPanel>(0, 870, 240, 60, this_theme.panel_corner_radius);
  color_theme_panel_->SetParrent(panel_null_widget_.get());
  color_theme_panel_->Init();

  color_theme_label_ = std::make_shared<UILabel>(10, 8, "UI Theme");
  color_theme_label_->SetParrent(color_theme_panel_.get());
  color_theme_spinbox_ = std::make_shared<UISpinBox<UIColorThemeIterator, false>>(
    10, 
    30, 
    [this](UIColorThemeIterator iter){ 
      if (!color_theme_from_palette_->GetValue()) {
        UIColorThemeManager::GetInstance().SetTheme(iter.GetValue());
      }
    }
  );
  color_theme_spinbox_->SetWidth(100);
  color_theme_spinbox_->SetParrent(color_theme_panel_.get());
  color_theme_spinbox_->Init();
  
  color_theme_from_palette_ = std::make_shared<UICheckbox>(
    120,
    30,
    [this](bool val){ 
      if (val) {
        UIColorThemeManager::GetInstance().LoadFromPalette(pallete_->GetColorPalette());
      } else {
        UIColorThemeManager::GetInstance().SetTheme(color_theme_spinbox_->GetValue().GetValue());
      }
    },
    "Adaptive"
  );
  color_theme_from_palette_->SetParrent(color_theme_panel_.get());
}