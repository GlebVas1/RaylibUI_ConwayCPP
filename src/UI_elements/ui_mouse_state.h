#pragma once


enum MouseState {
  MOUSE_CLEAR,
  MOUSE_HOVERED,
  MOUSE_PRESSED
};

class UIMouseState {
 protected:
  MouseState state_ = MOUSE_CLEAR;
};