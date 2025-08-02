#include "ui_pallete.h"

void UIPallete::UIPalleteButton::SetId(size_t id) {
    id_ = id;
}

void UIPallete::UIPalleteButton::Draw() {


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

    DrawRectangleRounded(main_field, roundness_, 0, background_color);
    DrawRectangleRoundedLinesEx(
        main_field_line,
        roundness_,
        0,
        id_ == this_pallete->selected_button ? 4 : 2,
        BLACK);
}

void UIPallete::UIPalleteButton::SetXPosition(int x) {
    
    x_position_ = x;
    std::cout << " x pos " << x_position_ << std::endl;
}

void UIPallete::UIPalleteButton::SetYPosition(int y) {
    
    y_position_ = y;
    std::cout << " y pos " << y_position_ << std::endl;
}

void UIPallete::UIPalleteButton::SetDimensions(int x, int y) {
    width_ = x;
    height_ = y;
}

void UIPallete::UIPalleteButton::Update() {

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
            this_pallete->selected_button = id_;
        } else {
            state_ = MouseState::MOUSE_HOVERED;
        }
    } else {
        state_ = MouseState::MOUSE_CLEAR;
    }
}

void UIPallete::UIPalleteButton::SetColors(GameColor c) {
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

void UIPallete::UIPalleteButton::SetPallete(UIPallete* pallette) {
    this_pallete = pallette;
}

void UIPallete::InitializeButtons() {
    buttons_ = std::vector<UIPalleteButton>(colors_count_, UIPalleteButton());
    color_pallete_val_ = std::vector<uint8_t>(colors_count_, 0);
    const uint8_t FULL_ = 255;
    const uint8_t EMPTY_ = 0;
    unsigned char offset = (FULL_ - EMPTY_) / colors_count_;
    for (size_t i = 0; i < colors_count_; ++i) {
        buttons_[i].SetId(i);
        buttons_[i].SetPallete(this);
        buttons_[i].SetDimensions(button_width_, button_height_);
        buttons_[i].SetXPosition(button_width_spacing_ + GetAbsoluteXPosition());
        buttons_[i].SetYPosition(button_height_spacing_ + GetAbsoluteYPosition() + (button_height_ + button_height_spacing_)  * i);
        buttons_[i].SetColors(color_pallete_[FULL_ - i * offset]);
        color_pallete_val_[i] = FULL_ - i * offset;
    }
}
void UIPallete::Init() {
    InitializeButtons();
    SetDimensions(button_width_ + 2 * button_width_spacing_,
                  button_height_spacing_ * (colors_count_ + 1) + button_height_ * colors_count_);
    shadow_ = std::make_shared<UIShadowEffect>(GetAbsoluteXPosition() - 5, GetAbsoluteYPosition() - 5, width_ + 10, height_ + 10, 0.5f, 3); 

}

void UIPallete::SetColorPallette(const std::vector<GameColor>& pallette) {
    color_pallete_ = pallette;
}

void UIPallete::SetColorCount(size_t color_count) {
    colors_count_ = color_count;
}

uint8_t UIPallete::GetSelectedVal() {
    return selected_val_;
}

void UIPallete::SetSelectedVal(uint8_t val) {
    selected_val_ = val;
}

void UIPallete::Update() {
    for (auto& button : buttons_) {
        button.Update();
    }
}

void UIPallete::Draw() {
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

    DrawRectangleRounded(main_field, roundness_, 0, background_color_);
    DrawRectangleRoundedLinesEx(main_field_line, roundness_, 0, 2, BLACK);



    for (auto& button : buttons_) {
        button.Draw();
    }
}