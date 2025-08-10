#include "game_objects.h"

GameObject::GameObject() {}
GameObject::GameObject(const std::string& name) : name(name) 
{}

GameObject::GameObject(size_t size, const std::string& name) : 
    name(name), 
    size(size), 
    array(std::vector<std::vector<uint8_t>>(size, std::vector<uint8_t>(size, 0))) 
{}

GameObject::GameObject(const std::vector<std::vector<uint8_t>>& array, const std::string& name, bool should_grid_show) : 
    name(name), 
    should_grid_show(should_grid_show),
    size(array.size()), 
    array(array)
{}
