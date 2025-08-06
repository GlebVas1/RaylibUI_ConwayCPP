#include "ui_textures_loader.h"

UITextureLoader::UITextureLoader() {}

UITextureLoader& UITextureLoader::GetInstance() {
    static UITextureLoader obj;
    return obj;
}
void UITextureLoader::LoadTextureFromFile(std::string name, std::string path) {
    //Texture text = ;
    map_[name] = LoadTexture(path.c_str());
}
Texture2D* UITextureLoader::GetTexture(std::string name) {
    auto iter = map_.find(name);
    if (iter == map_.end()) {
        return nullptr;
    }
    return &iter->second;

}

void UITextureLoader::LoadAllTextures() {
    LoadTextureFromFile("clock_wise", "../resources/textures/clockwise.png");
    LoadTextureFromFile("counter_clock_wise", "../resources/textures/counter_clockwise.png");
    LoadTextureFromFile("mirror_v", "../resources/textures/mirror_vertical.png");
    LoadTextureFromFile("mirror_h", "../resources/textures/mirror_horizontal.png");
    LoadTextureFromFile("invert", "../resources/textures/color_invert.png");
    LoadTextureFromFile("play", "../resources/textures/continue.png");
    LoadTextureFromFile("pause", "../resources/textures/pause.png");
}