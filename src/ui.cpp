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
    canvas_->SetDimensions(600, 600);
    canvas_->SetCanvasTextureDimensions(20, 20);
    canvas_->SetShowGrid(true);

    canvas_->Init();

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
}

void UI::AddUIElement(UIElement* elem_ptr) {
    elements_.push_back(elem_ptr);
}