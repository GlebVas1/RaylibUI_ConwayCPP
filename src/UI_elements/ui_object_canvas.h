#pragma once
#include "stdafx.h"
#include "ui_canvas.h"
#include "game_objects.h"
#include "game_colors.h"

class UIObjectCanvas : public UICanvas {
    GameObject this_object_;
    //uint8_t* color_buffer_ = nullptr;
    size_t BufferIndex(size_t size, size_t x, size_t y);
    public:
    void Init() override;
    void Update() override;
    
    void SetObject(const GameObject& object);
    void UpdatePalette(const std::vector<GameColor>& palette);
    
    void SetPixel(size_t x, size_t y, uint8_t val);

    uint8_t GetPixel(size_t x, size_t y);
    
    const GameObject& GetObject();
    
    
};