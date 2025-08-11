#include "ui_shadow_effect.h"


UIShadowEffect::UIShadowEffect(int x, int y, int width, int height, float roundness, int iterations) : x(x), y(y), height(height), width(width) {
    const int new_height = (height / 1);
    const int new_width = (width / 1);
   
    RenderTexture2D rend_shadow = LoadRenderTexture(new_width, new_height);
    SetTextureFilter(rend_shadow.texture, TEXTURE_FILTER_TRILINEAR);

    BeginTextureMode(rend_shadow);
    for (int i = 0; i < iterations; ++i) {
        DrawRectangleRounded(
        Rectangle{
                static_cast<float>(i),
                static_cast<float>(i),
                static_cast<float>(new_width - 2 * i),
                static_cast<float>(new_height - 2 * i)
            },
            roundness,
            0,
            Fade(BLACK, 0.25f)
        );
    }

    EndTextureMode();
    
    shadow = std::make_shared<Texture2D>(rend_shadow.texture);

    SetTextureFilter(*shadow, TEXTURE_FILTER_TRILINEAR);
}

UIShadowEffect::~UIShadowEffect() {
    UnloadTexture(*shadow);
}

void UIShadowEffect::Draw() {
    DrawTexture(*shadow, x, y, WHITE);
}