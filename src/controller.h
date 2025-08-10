#pragma once
#include "stdafx.h"
#include "game_rule.h"
#include "game_objects.h"


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

    const std::vector<std::string>& GetAllObjectsNames();
    void SetObject(size_t ind);

    void SetFieldPixel(int x, int y, uint8_t val);

    void SetFieldRule(size_t ind);
    GameRule* GetFieldRule();

    void SetPalette(size_t ind);
    
    void SetFieldSize(size_t x, size_t y);
    
    void SetFPS(size_t val);
    float GetFPS();
    void SetPause(float val);

    void SetNewColorBuffer(uint8_t* buffer);


    void ThreadsJoin();

    void StartUI();
    void Start();
};

