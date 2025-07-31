#pragma once
#include "stdafx.h"
#include "ui.h"
#include "field.h"

class UI;
class Field;

class Controller {
    private:
    Field& field;
    UI& ui;
    Controller();
    ~Controller();
    public:
    static Controller& GetInstance();
    void SetFieldPixel(size_t x, size_t y, uint8_t val);
    void StartUI();
};