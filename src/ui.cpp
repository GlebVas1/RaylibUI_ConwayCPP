#include "ui.h"
#include "controller.h"
#include "game_rule.h"
#include "UI_Tools/ui_tools.h"
#include "UI_Tools/ui_textures_loader.h"

//cause of UI elemnts structure elemnts arent crated there
UI::UI() { };

UI& UI::GetInstance() {
    static UI obj;
    return obj;
}

UI::~UI() {
    // CloseWindow();
}

void UI::InitializeWindow() {
    std::cout << "Start window initializing" << std::endl;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(window_width, window_height, "Conway");
    UITextureLoader::GetInstance().LoadAllTextures();
    UITools::GetMainFont();
    SetTextLineSpacing(2); 
    std::cout << "Window initialized" << std::endl;
}

void UI::Start() {
    
    float pause = false;


    main_canvas_->SetCanvasTextureDimensions(default_field_width_, default_field_height_);
    
    
    main_canvas_->Init();
    pallete_->Init();

    SetTargetFPS(100);
    
    while (!WindowShouldClose()) {
        UpdateUIElements();
        if (IsKeyPressed(KEY_SPACE)) {
            pause = game_control_play_button_->GetState();
            pause = !pause;
            game_control_play_button_->SetState(pause);
            controller_->SetPause(pause);
        }
        /* if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            std::cout << "Mouse x " << GetMousePosition().x << " y " << GetMousePosition().y << std::endl;
        }  */
        BeginDrawing();
        ClearBackground(UIColorThemeManager::GetInstance().GetTheme().ui_background_color);
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

    main_canvas_panel_ = std::make_shared<UIPanel>(0, 0, 1080, 1080, 5.0f);
    main_canvas_panel_->SetParrent(null_widget_.get());
    main_canvas_panel_->Init();

    game_control_panel_ = std::make_shared<UIPanel>(1120, 40, 385, 50, 5.0f);
    game_control_panel_->SetParrent(null_widget_.get());
    game_control_panel_->Init();
    

    game_control_play_button_ = std::make_shared<UIDualTextureButton>(
        5, 
        5, 
        40, 
        40, 
        0.1f,
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
            SetFPS(val);
    });
    game_control_slider_->SetParrent(game_control_panel_.get());
    
    game_control_panel_fps_label_ = std::make_shared<UILabelPrintValue<float>>(
        275,
        16,
        "FPS: %3.02f",
        [this]() -> float { return GetFPS(); }
    );
    game_control_panel_fps_label_->SetParrent(game_control_panel_.get());

    field_control_panel_ = std::make_shared<UIPanel>(1120, 110, 385, 70, 5.0f);
    field_control_panel_->SetParrent(null_widget_.get());
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
        0.1f,
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
                field_height_spinbox_->SetValue(field_width_spinbox_->GetValue());
            }
        }, 
        10
    );

    field_width_spinbox_->SetMinValue(60);
    field_width_spinbox_->SetMaxValue(1060);
    field_width_spinbox_->SetValue(default_field_width_);
    field_width_spinbox_->SetParrent(field_control_panel_.get());

    field_control_size_H_label_ = std::make_shared<UILabel>(295, 12, "H:");
    field_control_size_H_label_->SetParrent(field_control_panel_.get());

    field_height_spinbox_ = std::make_shared<UISpinBox<size_t>>(
        315, 
        40, 
        [this](size_t val) {
            if (field_dim_lock_button_->GetState()) {
                field_width_spinbox_->SetValue(field_height_spinbox_->GetValue());
            }
        }, 
        10
    );

    field_height_spinbox_->SetMinValue(60);
    field_height_spinbox_->SetMaxValue(1060);
    field_height_spinbox_->SetValue(default_field_height_);
    field_height_spinbox_->SetParrent(field_control_panel_.get());

    field_control_size_W_label_ = std::make_shared<UILabel>(295, 42, "W:");
    field_control_size_W_label_->SetParrent(field_control_panel_.get());

    field_set_button_ = std::make_shared<UITextButton>(
        180, 
        25, 
        70, 
        20, 
        0.1f, 
        [this](){ SetFieldSize(); }, 
        "Resize"
    );
    field_set_button_->SetParrent(field_control_panel_.get());


    brush_settings_panel_ = std::make_shared<UIPanel>(1300, 200, 145, 160, 5.0f);
    brush_settings_panel_->SetParrent(null_widget_.get());
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

    brush_settings_size_label_ = std::make_shared<UILabel>(80, 43, "Size");
    brush_settings_size_label_->SetParrent(brush_settings_panel_.get());

    brush_round_checkbox_ = std::make_shared<UICheckbox>(
        10, 
        70, 
        [this](bool val) {  }, 
        "Round"
    );
    brush_round_checkbox_->SetParrent(brush_settings_panel_.get());

    brush_random_checkbox_ = std::make_shared<UICheckbox>(
        10, 
        100, 
        [this](bool val) {  }, 
        "Random"
    );
    brush_random_checkbox_->SetParrent(brush_settings_panel_.get());

    brush_object_toogle_ = std::make_shared<UIToggle>(
        10, 
        130, 
        [this](bool val) {  }, 
        "Object"
    
    );
    brush_object_toogle_->SetParrent(brush_settings_panel_.get());

    main_canvas_ = std::make_shared<UIMainCanvas>();
    main_canvas_->SetParrent(main_canvas_panel_.get());
    main_canvas_->SetPosition(5, 5);
    main_canvas_->SetDimensions(1070, 1070);

    

    pallete_ = std::make_shared<UIPalette>();
    pallete_->SetXPosition(1465);
    pallete_->SetYPosition(200);
    pallete_->SetParrent(null_widget_.get());


    palette_panel_ = std::make_shared<UIPanel>(1300, 380, 145, 290, 5.0f);
    palette_panel_->SetParrent(null_widget_.get());
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

    game_object_panel_ = std::make_shared<UIPanel>(1120, 200, 160, 470, 5.0f);
    game_object_panel_->SetParrent(null_widget_.get());
    game_object_panel_->Init();

    game_object_label_ = std::make_shared<UILabel>(10, 10, "Game objects");
    game_object_label_->SetParrent(game_object_panel_.get());

    game_object_list_ = std::make_shared<UIList>(
        10, 
        40, 
        150, 
        200, 
        [this](size_t ind){ SetGameObject(ind); }
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
        0.1f, 
        [this](){ game_object_canvas_->GameObjectRotateClockwise(); }, 
        "clock_wise");
    game_object_clockwise_button_->SetParrent(game_object_panel_.get());

    game_object_counter_clockwise_button_ = std::make_shared<UITextureButton>(
        40, 
        250, 
        25, 
        25, 
        0.1f, 
        [this](){ game_object_canvas_->GameObjectRotateCounterClockwise(); }, 
        "counter_clock_wise");
    game_object_counter_clockwise_button_->SetParrent(game_object_panel_.get());

    game_object_mirror_v_button_ = std::make_shared<UITextureButton>(
        10, 
        280, 
        25, 
        25, 
        0.1f, 
        [this](){ game_object_canvas_->GameObjectMirrorVertical(); }, 
        "mirror_v");
    game_object_mirror_v_button_->SetParrent(game_object_panel_.get());

    game_object_mirror_h_button_ = std::make_shared<UITextureButton>(
        40, 
        280, 
        25, 
        25, 
        0.1f, 
        [this](){ game_object_canvas_->GameObjectMirrorHorizontal(); }, 
        "mirror_h");
    game_object_mirror_h_button_->SetParrent(game_object_panel_.get());

    game_object_invert_button_ = std::make_shared<UITextureButton>(
        70, 
        250, 
        55, 
        55, 
        0.1f, 
        [this](){ game_object_canvas_->GameObjectInvert(); }, 
        "invert");
    game_object_invert_button_->SetParrent(game_object_panel_.get());

    game_rule_panel_ = std::make_shared<UIPanel>(1120, 690, 385, 200, 5.0f);
    game_rule_panel_->SetParrent(null_widget_.get());
    game_rule_panel_->Init();

    game_rule_list_ = std::make_shared<UIList>(10, 40, 375, 150, [this](size_t ind) { SetRule(ind); });
    game_rule_list_->SetParrent(game_rule_panel_.get());

    game_rule_label_ = std::make_shared<UILabel>(10, 8, "Game rule settings");
    game_rule_label_->SetParrent(game_rule_panel_.get());

    std::vector<std::string> game_rule_names;
    for (const auto& elem : ALL_RULES) {
        game_rule_names.push_back(elem->name);
    }
    game_rule_list_->SetVector(game_rule_names);
    game_rule_list_->Init();

    color_theme_panel_ = std::make_shared<UIPanel>(1120, 910, 150, 60, 5.0f);
    color_theme_panel_->SetParrent(null_widget_.get());
    color_theme_panel_->Init();

    color_theme_spinbox_ = std::make_shared<UISpinBox<UIColorThemeIterator, false>>(
        10, 
        10, 
        [](UIColorThemeIterator iter){ UIColorThemeManager::GetInstance().SetTheme(iter.GetValue()); });
    color_theme_spinbox_->SetParrent(color_theme_panel_.get());

}

void UI::AddUIElement(UIElement* elem_ptr) {
    elements_.push_back(elem_ptr);
}

void UI::SetColorPallette(const std::vector<GameColor>& palette) {
    pallete_->SetColorPallette(palette);
    pallete_->Init();
    game_object_canvas_->UpdatePalette(palette);
}

const std::vector<GameColor>& UI::GetCurrentPalette() {
    return pallete_->GetColorPalette();
}

void UI::SetColorCount(size_t color_count) {
    pallete_->SetColorCount(color_count);
    pallete_->Init();
}

void UI::InitPalette() {
    pallete_->Init();
}
    
void UI::SetSelectedColor(uint8_t val) {
    pallete_->SetSelectedVal(0);
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

void UI::SetRule(size_t ind) {
    controller_->SetFieldRule(ind);
}

void UI::UpdatePalette(size_t ind) {
    controller_->SetPalette(ind);
}

void UI::SetGameObject(size_t ind) {
    controller_->SetObject(ind);
}

void UI::SetGameObject(const GameObject& game_object) {
    game_object_canvas_->SetObject(game_object);
}

void UI::GameObjectRotateClockwise() {

}

void UI::GameObjectRotateCounterClockwise() {

}

void UI::SetFPS(size_t val) {
    controller_->SetFPS(val);
}

float UI::GetFPS() {
    return controller_->GetFPS();
}

void UI::SetFieldSize() {
    main_canvas_->SetColorBuffer(nullptr);
    main_canvas_->SetCanvasTextureDimensions(field_height_spinbox_->GetValue(), field_width_spinbox_->GetValue());
    controller_->SetFieldSize(field_height_spinbox_->GetValue(), field_width_spinbox_->GetValue());
}