#include "ui_palette.h"
#include "../UI_Tools/ui_tools.h"

void UIPalette::UIPaletteButton::SetId(size_t id) {
    id_ = id;
}

void UIPalette::UIPaletteButton::Draw() {

    const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();

    Rectangle main_field{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_line{
        static_cast<float>(x_position_ + 1),
        static_cast<float>(y_position_ + 1),
        static_cast<float>(width_ - 1),
        static_cast<float> (height_ - 1)
    };

    Color background_color;
    switch (state_)
    {
    case MouseState::MOUSE_CLEAR:
        background_color = default_c_;
        break;
    case MouseState::MOUSE_HOVERED:
        background_color = covered_c_;
        break;   
    case MouseState::MOUSE_PRESSED:
        background_color = pressed_c_;
        break;
    }

    UITools::DrawRectangle(
        x_position_,
        y_position_,
        width_,
        height_,
        this_pallete->selected_button_ == id_ ? this_theme.line_thick_thikness : this_theme.line_narrow_thikness,
        this_theme.elements_corner_radius,
        background_color,
        this_theme.ui_line_color
    );
}

void UIPalette::UIPaletteButton::SetXPosition(int x) {
    
    x_position_ = x;
    //std::cout << " x pos " << x_position_ << std::endl;
}

void UIPalette::UIPaletteButton::SetYPosition(int y) {
    
    y_position_ = y;
    //std::cout << " y pos " << y_position_ << std::endl;
}

void UIPalette::UIPaletteButton::SetDimensions(int x, int y) {
    width_ = x;
    height_ = y;
}

void UIPalette::UIPaletteButton::Update() {

    bool mouse_on_button = CheckCollisionPointRec(GetMousePosition(), Rectangle{
        static_cast<float>(x_position_),
        static_cast<float>(y_position_),
        static_cast<float>(width_),
        static_cast<float>(height_)
    });
    
    if (mouse_on_button) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            state_ = MouseState::MOUSE_PRESSED;
            this_pallete->selected_val_ = this_pallete->color_pallete_val_[id_];
            this_pallete->selected_button_ = id_;
        } else {
            state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        state_ = MouseState::MOUSE_CLEAR;
    }
}

void UIPalette::UIPaletteButton::SetColors(GameColor c) {
    default_c_ = { c.r, c.g, c.b, 255 };
    /* covered_c_ = {
        std::max<uint8_t>(static_cast<int>(c.r - 10), 0),
        std::max<uint8_t>(static_cast<int>(c.g - 10), 0),
        std::max<uint8_t>(static_cast<int>(c.b - 10), 0),
        255
    };
    pressed_c_ = {
        std::max<uint8_t>(static_cast<int>(c.r - 50), 0),
        std::max<uint8_t>(static_cast<int>(c.g - 50), 0),
        std::max<uint8_t>(static_cast<int>(c.b - 50), 0),
        255
    }; */
    Color black_low = {0, 0, 0, 40};
    Color black_high = {0, 0, 0, 90};
    covered_c_ = ColorAlphaBlend(default_c_, black_low, WHITE);
    pressed_c_ = ColorAlphaBlend(default_c_, black_high, WHITE);
}

void UIPalette::UIPaletteButton::SetPalette(UIPalette* pallette) {
    this_pallete = pallette;
}

void UIPalette::InitializeButtons() {
    if (colors_count_ == 0) {
        return;
    }

    const size_t buttons_count = std::min<size_t>(colors_count_ + 1, max_height_buttons_count);

    buttons_ = std::vector<UIPaletteButton>(buttons_count, UIPaletteButton());
    color_pallete_val_ = std::vector<uint8_t>(buttons_count, 0);

    const uint8_t FULL_ = 255;
    const uint8_t EMPTY_ = 0;

    unsigned char offset = (FULL_ - EMPTY_) / colors_count_;
    size_t offset_mult = ((256 - 2) / offset) / (buttons_count - 1);

    buttons_.front().SetId(0);
    buttons_.front().SetPalette(this);
    buttons_.front().SetDimensions(button_width_, button_height_);
    buttons_.front().SetXPosition(button_width_spacing_ + GetAbsoluteXPosition());
    buttons_.front().SetYPosition(button_height_spacing_ + GetAbsoluteYPosition());
    buttons_.front().SetColors(color_pallete_[FULL_]);
    color_pallete_val_.front() = FULL_;

    for (size_t i = 1; i < buttons_count - 1; ++i) {
        buttons_[i].SetId(i);
        buttons_[i].SetPalette(this);
        buttons_[i].SetDimensions(button_width_, button_height_);
        buttons_[i].SetXPosition(button_width_spacing_ + GetAbsoluteXPosition());
        buttons_[i].SetYPosition(button_height_spacing_ + GetAbsoluteYPosition() + (button_height_ + button_height_spacing_) * i);
        buttons_[i].SetColors(color_pallete_[FULL_ - i * offset * offset_mult]);
        color_pallete_val_[i] = FULL_ - i * offset * offset_mult;
    }

    buttons_.back().SetId(buttons_count - 1);
    buttons_.back().SetPalette(this);
    buttons_.back().SetDimensions(button_width_, button_height_);
    buttons_.back().SetXPosition(button_width_spacing_ + GetAbsoluteXPosition());
    buttons_.back().SetYPosition(button_height_spacing_ + GetAbsoluteYPosition() + (button_height_ + button_height_spacing_) * (buttons_count - 1));
    buttons_.back().SetColors(color_pallete_[EMPTY_]);

    color_pallete_val_.back() = EMPTY_;
}
void UIPalette::Init() {
    InitializeButtons();
    const size_t buttons_count = std::min<size_t>(colors_count_ + 1, max_height_buttons_count);
    SetDimensions(button_width_ + 2 * button_width_spacing_,
                  button_height_spacing_ * (buttons_count + 1) + button_height_ * (buttons_count));
    std::cout << "UIPalleteInit() wh " << width_ + 10 << " " << height_ + 10 << std::endl;
    shadow_ = std::make_shared<UIShadowEffect>(
        GetAbsoluteXPosition() - 5, 
        GetAbsoluteYPosition() - 5, 
        width_ + 10, 
        height_ + 10,
        10.0 / std::min(width_, height_), 
        3); 

}

void UIPalette::SetColorPallette(const std::vector<GameColor>& pallette) {
    color_pallete_ = pallette;
    //colors_count_ = color_pallete_.size();
}

void UIPalette::SetColorCount(size_t color_count) {
    colors_count_ = color_count;
}

uint8_t UIPalette::GetSelectedVal() {
    return selected_val_;
}

void UIPalette::SetSelectedVal(uint8_t val) {
    selected_val_ = val;
}

void UIPalette::Update() {
    for (auto& button : buttons_) {
        button.Update();
    }
}

void UIPalette::Draw() {
    shadow_->Draw();
    Rectangle main_field{
        static_cast<float>(GetAbsoluteXPosition()),
        static_cast<float>(GetAbsoluteYPosition()),
        static_cast<float>(width_),
        static_cast<float> (height_)
    };

    Rectangle main_field_line{
        static_cast<float>(GetAbsoluteXPosition() + 1),
        static_cast<float>(GetAbsoluteYPosition() + 1),
        static_cast<float>(width_ - 1),
        static_cast<float> (height_ - 1)
    };

    const auto& this_theme = UIColorThemeManager::GetInstance().GetTheme();
    UITools::DrawRectangle(
        GetAbsoluteXPosition(),
        GetAbsoluteYPosition(),
        width_,
        height_,
        this_theme.line_default_thikness,
        this_theme.panel_corner_radius,
        this_theme.ui_neutral_color,
        this_theme.ui_line_color
    );



    for (auto& button : buttons_) {
        button.Draw();
    }
}

uint8_t UIPalette::GetRandomVal() {
    return color_pallete_val_[rand() % color_pallete_val_.size()];
}

const std::vector<GameColor>& UIPalette::GetColorPalette() {
    return color_pallete_;
}