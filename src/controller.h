#pragma once
#include "stdafx.h"
#include "ui.h"
#include "field.h"

class Controller {
    private:
    Field& field;
    UI& ui;
    Controller();
    ~Controller();
    public:
    Controller& GetInstance();
    void StartUI();
};