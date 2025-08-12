#pragma once
#include "stdafx.h"
#include "ui_color_theme.h"


class UIElement {
 protected:
  int width_ = 0;
  int height_ = 0;
  int x_position_ = 0;
  int y_position_ = 0;

  UIElement* parrent_ = nullptr;
  std::unordered_set<UIElement*> children_;

 public:
  UIElement();
  UIElement(int width, int height);
  UIElement(int x_pos, int y_pos, int width, int height);

  // Don't want make it = 0, to not mandatory implement them after
  virtual void Init();
  virtual void Draw();
  virtual void Update();

  void SetDimensions(int x, int y);
  void SetPosition(int x, int y);

  void SetXPosition(int x);
  void SetYPosition(int y);

  void SetWidth(int x);
  void SetHeight(int y);

  int GetWidth() const;
  int GetHeight() const;
  int GetXPosition() const;
  int GetYPosition() const;

  int GetAbsoluteXPosition() const;
  int GetAbsoluteYPosition() const;

  void SetParrent(UIElement* parrent);
  UIElement* GetParrent() const;

  std::unordered_set<UIElement*> GetChildren() const;

  // virtual ~UIElement() {};
  // isn't used because there no such cases
};