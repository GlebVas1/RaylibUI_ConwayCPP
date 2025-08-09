#pragma once
#include "stdafx.h"

#include "UI_elements/ui_main_canvas.h"
#include "UI_elements/ui_palette.h"
#include "UI_elements/ui_panel.h"

#include "UI_elements/ui_spinbox.h"
#include "UI_elements/ui_label.h"

#include "UI_elements/ui_check_box.h"
#include "UI_elements/ui_toogle.h"

#include "UI_elements/ui_text_fromat.h"
#include "UI_elements/ui_list.h"
#include "UI_elements/ui_object_canvas.h"

#include "UI_elements/ui_texture_button.h"
#include "UI_elements/ui_dual_textured_button.h"

#include "UI_elements/ui_slider.h"
#include "UI_elements/ui_label_print_value.h"

class UIGameObjectSettings {
    protected:
    std::shared_ptr<UIPanel> game_object_panel_ = nullptr;
    std::shared_ptr<UIList> game_object_list_ = nullptr;
    std::shared_ptr<UILabel> game_object_label_ = nullptr;
    std::shared_ptr<UIObjectCanvas> game_object_canvas_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_clockwise_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_counter_clockwise_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_mirror_v_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_mirror_h_button_ = nullptr;
    std::shared_ptr<UITextureButton> game_object_invert_button_ = nullptr;
    void InitializeGameObjectsSettingsPanel(UIElement* null_widget);
    void SetGameObject(const GameObject& game_object);
};