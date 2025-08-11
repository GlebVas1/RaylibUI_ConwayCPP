#include "ui.h"
#include "controller.h"
#include "game_rule.h"
#include "UI_Tools/ui_tools.h"
#include "UI_Tools/ui_textures_loader.h"


//cause of UI elemnts structure elements cant be initialized only after some calls
UI::UI() { };

UI::~UI() {
  // CloseWindow();
}

void UI::DrawElement(UIElement* root) {
  if (root == nullptr) {
    return;
  }
  root->Draw();
  for (UIElement* elem : root->GetChildren()) {
    DrawElement(elem);
  }
}

void UI::DrawUIElements() {
  DrawElement(null_widget_.get());
}

void UI::ResizeMainField(int size_x, int size_y) {
  const float width_height_aspect = static_cast<float>(size_x) / size_y;
  int panel_height = window_height;
  float estimated_panel_width = width_height_aspect * panel_height;
  if (estimated_panel_width > GetScreenWidth() - 500) {
    estimated_panel_width = GetScreenWidth() - 500;
    panel_height = estimated_panel_width / width_height_aspect;
  }
  main_canvas_panel_->SetDimensions(static_cast<int>(estimated_panel_width), panel_height);
  main_canvas_->SetDimensions(static_cast<int>(estimated_panel_width) - 10, panel_height - 10);
  main_canvas_panel_->Init();
}

UI& UI::GetInstance() {
  static UI obj;
  return obj;
}

void UI::InitializeWindow() {
  std::cout << "Start window initializing" << std::endl;
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(window_width, window_height, "Conway");
  UITextureLoader::GetInstance().LoadAllTextures();
  UITools::GetMainFont();
  SetTextLineSpacing(2); 
  std::cout << "Window initialized" << std::endl;
}

void UI::SetController(Controller* controller) {
  controller_ = controller;
}

void UI::AddUIElement(UIElement* elem_ptr) {
  elements_.push_back(elem_ptr);
}

void UI::UpdateUIElements() {
  for (auto elem : elements_) {
    elem->Update();
  }
}

void UI::Start() {
  float pause = false;
  main_canvas_->SetCanvasTextureDimensions(default_field_width_, default_field_height_);
  main_canvas_->Init();
  pallete_->Init();

  SetTargetFPS(100);
  
  while (!WindowShouldClose()) {
    UpdateUIElements();
    right_upper_null_widget_->SetXPosition(GetScreenWidth());
    main_canvas_panel_->SetYPosition((GetScreenHeight() - main_canvas_panel_->GetHeight()) / 2);
    if (IsKeyPressed(KEY_SPACE)) {
      pause = game_control_play_button_->GetState();
      pause = !pause;
      game_control_play_button_->SetState(pause);
      controller_->SetPause(pause);
    }
    /* if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      std::cout << "Mouse x " << GetMousePosition().x << " y " << GetMousePosition().y << std::endl;
    } */
    BeginDrawing();
    ClearBackground(UIColorThemeManager::GetInstance().GetTheme().ui_background_color);
    DrawUIElements();
    EndDrawing();
  }
}

void UI::SetColorBuffer(uint8_t* new_color_buffer) {
  main_canvas_->SetColorBuffer(new_color_buffer);
}

void UI::SetPixel(size_t x, size_t y) {
  controller_->SetFieldPixel(x, y, pallete_->GetSelectedVal());
}

void UI::DrawBrush(size_t x, size_t y) {
  if (brush_object_toogle_->GetValue()) {
    const auto& array = game_object_canvas_->GetObject().array;
    const size_t size = game_object_canvas_->GetObject().size;
    for (int x1 = 0; x1 < size; ++x1) {
      for (int y1 = 0; y1 < size; ++y1) {
        controller_->SetFieldPixel(x1 + static_cast<int>(x) - size / 2, y1 + static_cast<int>(y) - size / 2, array[x1][y1] == 1 ? 255 : 0);
      }
    }
  } else {
    int brush_radius = brush_size_spinbox_->GetValue();
    for (int x1 = -brush_radius; x1 < brush_radius; ++x1){
      for (int y1 = -brush_radius; y1 < brush_radius; ++y1) {
        uint8_t val_to_set = brush_random_checkbox_->GetValue() ? pallete_->GetRandomVal() : pallete_->GetSelectedVal();
        if (brush_round_checkbox_->GetValue()) {
          if (x1 * x1 + y1 * y1 < brush_radius * brush_radius) {
            controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), val_to_set);
          }
        } else {
          controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), val_to_set);
        }
      }
    }
  }
}

void UI::SetColorPallette(const std::vector<GameColor>& palette) {
  pallete_->SetColorPallette(palette);
  pallete_->Init();
  game_object_canvas_->UpdatePalette(palette);
  if (color_theme_from_palette_->GetValue()) {
    UIColorThemeManager::GetInstance().LoadFromPalette(palette);
  }
}

const std::vector<GameColor>& UI::GetCurrentPalette() {
  return pallete_->GetColorPalette();
}

void UI::InitPalette() {
  pallete_->Init();
}

void UI::UpdatePalette(size_t ind) {
  controller_->SetPalette(ind);
}

void UI::SetColorCount(size_t color_count) {
  pallete_->SetColorCount(color_count);
  pallete_->Init();
}
  
void UI::SetSelectedColor(uint8_t val) {
  pallete_->SetSelectedVal(0);
}

void UI::SetRule(size_t ind) {
  controller_->SetFieldRule(ind);
}

void UI::SetGameObjectByIndex(size_t ind) {
  controller_->SetObject(ind);
}

void UI::SetGameObject(const GameObject& game_object) {
  game_object_canvas_->SetObject(game_object);
}

void UI::SetFrameDelayMilliseconds(size_t val) {
  controller_->SetFPS(val);
}

float UI::GetFPS() {
  return controller_->GetFPS();
}

void UI::SetFieldSize() {
  main_canvas_->SetColorBuffer(nullptr);
  ResizeMainField(field_height_spinbox_->GetValue(), field_width_spinbox_->GetValue());
  main_canvas_->SetCanvasTextureDimensions(field_height_spinbox_->GetValue(), field_width_spinbox_->GetValue());
  controller_->SetFieldSize(field_width_spinbox_->GetValue(), field_height_spinbox_->GetValue());
}