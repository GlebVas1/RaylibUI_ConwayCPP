#pragma once
#include "stdafx.h"

class UI;
class Field;

// there cycled dependences obviously cause crush;
class Controller {
    private:
    Field* field;
    UI* ui;
    Controller();
    ~Controller();
    public:
    static Controller& GetInstance();
    void SetFieldPixel(size_t x, size_t y, uint8_t val);
    void StartUI();
    void StartField();
};

