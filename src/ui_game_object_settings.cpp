#include "ui_game_object_settings.h"

void UIGameObjectSettings::InitializeGameObjectsSettingsPanel(UIElement* null_widget) {
   /*  game_object_panel_ = std::make_shared<UIPanel>(1120, 140, 160, 470, 0.1f);
    game_object_panel_->SetParrent(null_widget);

    game_object_label_ = std::make_shared<UILabel>(10, 10, "Game objects");
    game_object_label_->SetParrent(game_object_panel_.get());

    // game_object_list_ = std::make_shared<UIList>(10, 40, 150, 200, [this](size_t ind){ SetGameObject(ind); });
    game_object_list_->SetParrent(game_object_panel_.get());

    game_object_canvas_ = std::make_shared<UIObjectCanvas>();
    game_object_canvas_->SetParrent(game_object_panel_.get());
    game_object_canvas_->SetCanvasGridColor(BLACK);
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
    game_object_invert_button_->SetParrent(game_object_panel_.get()); */
}

void UIGameObjectSettings::SetGameObject(const GameObject& game_object) {
    game_object_canvas_->SetObject(game_object);
}