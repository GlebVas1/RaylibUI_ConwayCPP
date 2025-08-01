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

    canvas_->SetPosition(0, 0);
    canvas_->SetDimensions(1280, 1280);
    canvas_->SetCanvasTextureDimensions(50, 50);
    canvas_->SetShowGrid(true);

    canvas_->Init();
    pallete_->Init();

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        UpdateUIElements();
        BeginDrawing();
        ClearBackground(WHITE);
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
    controller_->SetFieldPixel(x, y, val_to_set_);
}

void UI::SetController(Controller* controller) {
    controller_ = controller;
}

void UI::InitializeElements() {
    canvas_ = std::make_shared<UICanvas>();
    pallete_ = std::make_shared<UIPallete>();
    pallete_->SetXPosition(1100);
    pallete_->SetYPosition(20);
}

void UI::AddUIElement(UIElement* elem_ptr) {
    elements_.push_back(elem_ptr);
}

void UI::SetBrushValue(uint8_t val) {
    val_to_set_ = val;
}

void UI::SetColorPallette(const std::vector<GameColor>& pallette) {
    pallete_->SetColorPallette(pallette);
}

void UI::SetColorCount(size_t color_count) {
    pallete_->SetColorCount(color_count);
}
    
void UI::SetSelectedColor(uint8_t val) {
    pallete_->SetSelectedColor(0);
}
