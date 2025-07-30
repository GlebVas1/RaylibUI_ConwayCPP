#include "ui.h"

UI::UI() {};

UI& UI::GetInstance() {
    static UI obj;
    return obj;
}

UI::~UI() {
    CloseWindow();
}

void UI::Start() {

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    
    InitWindow(window_width, window_height, ".");

    canvas_ = std::make_shared<UICanvas>();
    canvas_->SetPosition(0, 0);
    canvas_->SetDimensions(400, 400);
    canvas_->SetCanvasTextureDimensions(20, 20);
    canvas_->SetShowGrid(true);

    canvas_->Init();

    SetTargetFPS(60);
    ClearBackground(WHITE);
    while (!WindowShouldClose()) {
        //f->UpdateField();
        BeginDrawing();
        canvas_->Draw();
        EndDrawing();
    }
}



void UI::SetColorBuffer(uint8_t* new_color_buffer) {
    canvas_->SetColorBuffer(new_color_buffer);
}