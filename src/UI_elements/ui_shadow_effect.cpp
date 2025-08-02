#include "ui_shadow_effect.h"


UIShadowEffect::UIShadowEffect(int x, int y, int width, int height, float roundness, int iterations) : x(x), y(y), height(height), width(width) {
    const int new_height = (height / 1);
    const int new_width = (width / 1);
    uint8_t* data = static_cast<uint8_t*>(malloc(new_height * new_width * 4));
    // set all alpha to 255
    memset(data, 0, 4 * new_height * new_width);
    
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
    std::cout << " AAA " << (void*)shadow.get() << std::endl;
    SetTextureFilter(*shadow, TEXTURE_FILTER_TRILINEAR);

}

void UIShadowEffect::Draw() {
    // DrawTexturePro(*shadow,
    //     Rectangle{
    //         0,
    //         0, 
    //         static_cast<float>(shadow->width),
    //         static_cast<float>(shadow->height)
    //     },
    //     Rectangle{
    //         static_cast<float>(x), 
    //         static_cast<float>(y), 
    //         static_cast<float>(width), 
    //         static_cast<float>(height)
    //     },
    //     Vector2{static_cast<float>(0), static_cast<float>(0)},
    //     0.0f,
    //     BLACK
    // );
    DrawTexture(*shadow, x, y, WHITE);
}