#pragma once
#include "stdafx.h"
#include "game_rule.h"

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

    void SetFieldRule(size_t ind);
    GameRule* GetFieldRule();

    void SetPalette(size_t ind);
    void SetObject(size_t ind);

    void SetFieldSize(size_t x, size_t y);
    
    void SetFPS(size_t val);
    float GetFPS();
    void SetPause(float val);

    void SetNewColorBuffer(uint8_t* buffer);
};

