#pragma once
#include "stdafx.h"


class UI;

class UIElement {
    protected:
    UI& ui;
    int width_ = 0;
    int height_ = 0;
    int x_position_ = 0;
    int y_position_ = 0;
    
    UIElement* parrent_ = nullptr;
    std::unordered_set<UIElement*> children_;

    public:
    // Don't want make it = 0, to not mandatory implement them
    virtual void Init();
    virtual void Draw();
    virtual void Update();

    void SetDimensions(int x, int y);
    void SetPosition(int x, int y);

    void SetXPosition(int x);
    void SetYPosition(int y);

    void SetWidth(int x);
    void SetHeight(int y);

    inline int GetWidth();
    inline int GetHeight();
    inline int GetXPosition();
    inline int GetYPosition();

    inline int GetAbsoluteXPosition();
    inline int GetAbsoluteYPosition();

    void SetParrent(UIElement* parrent);

    UIElement();
    UIElement(int width, int height);
    UIElement(int x_pos, int y_pos, int width, int height);

    // virtual ~UIElement() {}; 
    // isn't used because there no such cases
};
