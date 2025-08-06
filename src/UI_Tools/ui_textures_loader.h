#pragma once
#include "stdafx.h"
#include "raylib.h"

class UITextureLoader {
    private:
    UITextureLoader();
    std::unordered_map<std::string, Texture2D> map_;
    public:
    static UITextureLoader& GetInstance();
    void LoadTextureFromFile(std::string name, std::string path);
    Texture2D* GetTexture(std::string name);
    void LoadAllTextures();
};