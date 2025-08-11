#pragma once
#include "stdafx.h"
#include "raylib.h"

template <typename T>
class UITextFormat {
    protected:
    const char* Format(const T&) { return " "; }
};

template <>
class UITextFormat<float> {
    protected:
    const char* Format(const float& val) {
        return TextFormat("%02.01f", val);
    }
};

template <>
class UITextFormat<int> {
    protected:
    const char* Format(const int& val) {
        return TextFormat("%d", val);
    }
};

template <>
class UITextFormat<size_t> {
    protected:
    const char* Format(const size_t& val) {
        return TextFormat("%zu", val);
    }
};
