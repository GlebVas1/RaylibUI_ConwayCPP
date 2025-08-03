#include "ui.h"
#include "controller.h"
#include "game_rule.h"
#include "UI_Tools/ui_tools.h"
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
    
    InitWindow(window_width, window_height, "Conway");

    UITools::GetMainFont();
    
    

    //Font font = LoadFontEx("../resources/fonts/jaipur.ttf", 32, 0, 250);
    SetTextLineSpacing(2); 

    main_canvas_->SetPosition(10, 10);
    main_canvas_->SetDimensions(1060, 1060);
    main_canvas_->SetCanvasTextureDimensions(1060, 1060);
    // canvas_->SetShowGrid(true);
    
    main_canvas_panel_->Init();
    main_canvas_->Init();
    pallete_->Init();
    brush_settings_panel_->Init();
    game_rule_panel_->Init();
    
    std::vector<std::string> game_rule_names;
    for (const auto& elem : ALL_RULES) {
        game_rule_names.push_back(elem.name);
    }
    game_rule_list_->SetVector(game_rule_names);
    game_rule_list_->Init();

    SetTargetFPS(100);
    
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

    brush_settings_panel_ = std::make_shared<UIPanel>(1100, 40, 145, 160, 0.1f);
    brush_settings_panel_->SetParrent(null_widget_.get());
    


    brush_settings_label_ = std::make_shared<UILabel>(10, 10, "Brush settings");
    brush_settings_label_->SetParrent(brush_settings_panel_.get());

    brush_size_spinbox_ = std::make_shared<UISpinBox<int>>(10, 40, &brush_radius_, 1.0f);
    brush_size_spinbox_->SetMaxValue(100);
    brush_size_spinbox_->SetMinValue(1);
    brush_size_spinbox_->SetParrent(brush_settings_panel_.get());


    brush_settings_size_label_ = std::make_shared<UILabel>(80, 43, "Size");
    brush_settings_size_label_->SetParrent(brush_settings_panel_.get());

    brush_round_checkbox_ = std::make_shared<UICheckbox>(10, 70, &brush_round_, "Round");
    brush_round_checkbox_->SetParrent(brush_settings_panel_.get());

    brush_random_checkbox_ = std::make_shared<UICheckbox>(10, 100, &brush_random_, "Random");
    brush_random_checkbox_->SetParrent(brush_settings_panel_.get());

    brush_object_toogle_ = std::make_shared<UIToggle>(10, 130, &brush_object_mode_, "Object");
    brush_object_toogle_->SetParrent(brush_settings_panel_.get());

    game_rule_panel_ = std::make_shared<UIPanel>(1100, 200, 145, 160, 0.1f);
    game_rule_panel_->SetParrent(null_widget_.get());

    game_rule_list_ = std::make_shared<UIList>(10, 10, 175, 180, &game_rule_selected_);
    game_rule_list_->SetParrent(game_rule_panel_.get());
    
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
            uint8_t val_to_set = brush_random_ ? pallete_->GetRandomVal() : pallete_->GetSelectedVal();
            if (brush_round_) {
                if (x1 * x1 + y1 * y1 < brush_radius_ * brush_radius_) {
                    controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), val_to_set);
                }
            } else {
                controller_->SetFieldPixel(x1 + static_cast<int>(x), y1 + static_cast<int>(y), val_to_set);
            }
        }
    }
}

void UI::SetRule() {
    controller_->SetFieldRule(game_rule_selected_);
}