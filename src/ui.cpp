#include "ui.h"
#include "controller.h"

//cause of UI elemnts structure elemnts arent crated there
UI::UI() { };

UI& UI::GetInstance() {
    static UI obj;
    return obj;
}

UI::~UI() {
    // CloseWindow();
}

void UI::Start() {

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(window_width, window_height, ".");

    main_canvas_->SetPosition(10, 10);
    main_canvas_->SetDimensions(1060, 1060);
    main_canvas_->SetCanvasTextureDimensions(600, 600);
    // canvas_->SetShowGrid(true);
    
    main_canvas_panel_->Init();
    main_canvas_->Init();
    pallete_->Init();
    brush_settings_panel_->Init();
    

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        UpdateUIElements();
        BeginDrawing();
        ClearBackground(ui_background_color);
        DrawUIElements();
        EndDrawing();
    }
}

void UI::UpdateUIElements() {
    for (auto elem : elements_) {
        elem->Update();
    }
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

void UI::SetColorBuffer(uint8_t* new_color_buffer) {
    main_canvas_->SetColorBuffer(new_color_buffer);
}

void UI::SetPixel(size_t x, size_t y) {
    controller_->SetFieldPixel(x, y, pallete_->GetSelectedVal());
}

void UI::SetController(Controller* controller) {
    controller_ = controller;
}

void UI::InitializeElements() {
    null_widget_ = std::make_shared<UIElement>();

    main_canvas_panel_ = std::make_shared<UIPanel>(0, 0, 1080, 1080, 0.015f);
    main_canvas_panel_->SetParrent(null_widget_.get());
    


    main_canvas_ = std::make_shared<UIMainCanvas>();
    main_canvas_->SetParrent(main_canvas_panel_.get());
    main_canvas_->SetCanvasGridColor(ui_background_color);

    pallete_ = std::make_shared<UIPallete>();
    pallete_->SetXPosition(1400);
    pallete_->SetYPosition(20);
    pallete_->SetParrent(null_widget_.get());

    brush_settings_panel_ = std::make_shared<UIPanel>(1100, 40, 180, 180, 0.1f);
    brush_settings_panel_->SetParrent(null_widget_.get());
    

    brush_size_spinbox_ = std::make_shared<UISpinBox>(20, 20, &brush_radius_, 1.0f);
    brush_size_spinbox_->SetMaxValue(100.0f);
    brush_size_spinbox_->SetParrent(brush_settings_panel_.get());

    brush_round_checkbox = std::make_shared<UICheckbox>(20, 50, &brush_round_, "Round");
    brush_round_checkbox->SetParrent(brush_settings_panel_.get());
    
}

void UI::AddUIElement(UIElement* elem_ptr) {
    elements_.push_back(elem_ptr);
}

void UI::SetColorPallette(const std::vector<GameColor>& pallette) {
    pallete_->SetColorPallette(pallette);
}

void UI::SetColorCount(size_t color_count) {
    pallete_->SetColorCount(color_count);
}
    
void UI::SetSelectedColor(uint8_t val) {
    pallete_->SetSelectedVal(0);
}

void UI::DrawBrush(size_t x, size_t y) {
    for (int x1 = -brush_radius_; x1 < brush_radius_; ++x1){
        for (int y1 = -brush_radius_; y1 < brush_radius_; ++y1) {
            if (brush_round_) {
                if (x1 * x1 + y1 * y1 < brush_radius_ * brush_radius_) {
                    controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), pallete_->GetSelectedVal());
                }
            } else {
                controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), pallete_->GetSelectedVal());
            }
        }
    }
}