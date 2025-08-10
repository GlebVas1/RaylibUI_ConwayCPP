#pragma once
#include "stdafx.h"

#include "UI_elements/ui_main_canvas.h"
#include "UI_elements/ui_palette.h"
#include "UI_elements/ui_panel.h"

#include "UI_elements/ui_spinbox.h"
#include "UI_elements/ui_label.h"


#include "UI_elements/ui_check_box.h"
#include "UI_elements/ui_toogle.h"


#include "ui_color_theme.h"

#include "UI_elements/ui_text_fromat.h"
#include "UI_elements/ui_list.h"
#include "UI_elements/ui_object_canvas.h"

#include "UI_elements/ui_texture_button.h"
#include "UI_elements/ui_dual_textured_button.h"

#include "UI_elements/ui_slider.h"
#include "UI_elements/ui_label_print_value.h"

class UIBrushSettings {
    protected:
    int brush_radius_ = 45;
    bool brush_round_ = false;
    bool brush_random_ = false;
    bool brush_object_mode_ = false;
    std::shared_ptr<UISpinBox<int>> brush_size_spinbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_round_checkbox_ = nullptr;
    std::shared_ptr<UICheckbox> brush_random_checkbox_ = nullptr;
    std::shared_ptr<UIPanel> brush_settings_panel_ = nullptr;
    std::shared_ptr<UIToggle> brush_object_toogle_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_label_ = nullptr;
    std::shared_ptr<UILabel> brush_settings_size_label_ = nullptr;
    void InitializeBrushSettingsPanel(UIElement* null_widget);
};
