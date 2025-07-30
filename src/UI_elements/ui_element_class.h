#pragma once
#include "stdafx.h"

class UIElement {
    protected:
    int width_ = 0;
    int height_ = 0;
    int x_position_ = 0;
    int y_position_ = 0;
    public:
    // Don't want make it = 0, to not mandatory implement them
    virtual void Init();
    virtual void Draw();
    virtual void Update();
    void SetDimensions(int x, int y);
    void SetPosition(int x, int y);

    void SetXPosition(int x);
    void SetYPosition(int y);
    
    inline int GetWidth();
    inline int GetHeight();
    inline int GetXPosition();
    inline int GetYPosition();

    UIElement();
    UIElement(int width, int height);
    UIElement(int x_pos, int y_pos, int width, int height);

    // virtual ~UIElement(); 
    // isn't used because there no such cases
};