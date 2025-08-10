#pragma once
#include "stdafx.h"

template <typename T>
class UITextFormat {
    protected:
    const char* format_;
};

template <>
class UITextFormat<float> {
    protected:
    const char* format_ = "%02.01f";
};

template <>
class UITextFormat<int> {
    protected:
    const char* format_ = "%d";
};

template <>
class UITextFormat<size_t> {
    protected:
    const char* format_ = "%zu";
};
