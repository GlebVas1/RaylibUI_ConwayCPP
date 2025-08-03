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
    std::thread* field_multi_thread_ = nullptr;
    public:
    static Controller& GetInstance();
    void SetFieldPixel(int x, int y, uint8_t val);
    void StartUI();
    void Start();
    void ThreadsJoin();

    void SetFieldRule(size_t);
    void SetPause(float val);
};

