#include "game_palette_loader.h"
#include "raylib.h"

GamePaletteLoader::GamePaletteLoader() {}

void GamePaletteLoader::LoadPalette(const std::string& name, const std::string& path) {
    std::cout << "GamePaletteLoader start load " << name << " on path " << path << std::endl;
    Texture2D texture = LoadTexture(path.c_str());
    
    if (texture.width != 256 && texture.height != 1) {
        return;
        std::cerr << "GamePaletteLoader bad texture" << std::endl;
    }

    size_t size = texture.width;
    Image palette_image = LoadImageFromTexture(texture);
    Color* pixels = LoadImageColors(palette_image);

    std::cout << "GamePaletteLoader start fill" << std::endl;
    
    std::vector<GameColor> palette(256);

    for (size_t i = 0; i < 256; ++i) {
        palette[i] = GameColor{pixels[i].r, pixels[i].g, pixels[i].b};
    }

    UnloadImage(palette_image);
    UnloadImageColors(pixels);

    names_.push_back(name);
    palettes_.push_back(palette);

    std::cout << "GamePaletteLoader success " << name << " on path " << path << std::endl;
}

GamePaletteLoader& GamePaletteLoader::GetInstance() {
    static GamePaletteLoader obj;
    return obj;
}

void GamePaletteLoader::AddPaletteObject(const ColorElement& obj) {
    palettes_.push_back(obj.pallette);
    names_.push_back(obj.name);
}

void GamePaletteLoader::LoadAllPalettes(const std::string& path) {

    std::ifstream all_objects_file(path);
    std::string palette_name;
    std::string palette_path;
    
    while (!all_objects_file.eof()){
        all_objects_file >> palette_name >> palette_path;
        LoadPalette(palette_name, palette_path); 
    }

    palettes_.push_back(GameColorPinkGreen());
    names_.push_back("SHO");
    
}

std::vector<GameColor>& GamePaletteLoader::GetPaleteeById(size_t id) {
    return palettes_[id];
}

const std::vector<std::string>& GamePaletteLoader::GetAllNames() {
    return names_;
}
