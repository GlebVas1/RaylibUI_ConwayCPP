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

    canvas_->SetPosition(10, 10);
    canvas_->SetDimensions(1060, 1060);
    canvas_->SetCanvasTextureDimensions(600, 600);
    // canvas_->SetShowGrid(true);

    canvas_->Init();
    pallete_->Init();

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

void UI::DrawUIElements() {
    for (auto elem : elements_) {
        elem->Draw();
    }
}

void UI::SetColorBuffer(uint8_t* new_color_buffer) {
    canvas_->SetColorBuffer(new_color_buffer);
}

void UI::SetPixel(size_t x, size_t y) {
    controller_->SetFieldPixel(x, y, pallete_->GetSelectedVal());
}

void UI::SetController(Controller* controller) {
    controller_ = controller;
}

void UI::InitializeElements() {
    canvas_ = std::make_shared<UICanvas>();
    canvas_->SetCanvasGridColor(ui_background_color);

    pallete_ = std::make_shared<UIPallete>();
    pallete_->SetXPosition(1100);
    pallete_->SetYPosition(20);
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
            if (x1 * x1 + y1 * y1 < brush_radius_ * brush_radius_) {
                controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), pallete_->GetSelectedVal());
            }
        }
    }
}