#include "ui_shadow_effect.h"


UIShadowEffect::UIShadowEffect(int width, int height, float roundness, int iterations) : height(height), width(width) {
    RenderTexture2D rend_shadow = LoadRenderTexture(width, height);
    SetTextureFilter(rend_shadow.texture, TEXTURE_FILTER_TRILINEAR);

    BeginTextureMode(rend_shadow);
    for (int i = 0; i < iterations; ++i) {
        DrawRectangleRounded(
        Rectangle{
                static_cast<float>(i),
                static_cast<float>(i),
                static_cast<float>(width - 2 * i),
                static_cast<float>(height - 2 * i)
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

void UIShadowEffect::Draw(int x_pos, int y_pos) {
    DrawTexture(*shadow, x_pos, y_pos, WHITE);
}