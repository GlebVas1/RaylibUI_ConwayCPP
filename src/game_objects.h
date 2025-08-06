#pragma once
#include "stdafx.h"

class GameObject {
    public:
    std::string name;
    bool should_grid_show = true;
    size_t size;
    std::vector<std::vector<uint8_t>> array;
    GameObject();
    GameObject(const std::string& name);
    GameObject(size_t size, const std::string& name);
    GameObject(const std::vector<std::vector<uint8_t>>& array, const std::string& name, bool should_grid_show);

};

extern GameObject vertical3;

extern std::vector<GameObject> ALL_OBJECTS;