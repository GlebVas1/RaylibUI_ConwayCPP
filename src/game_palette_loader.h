#pragma once
#include "game_colors.h"

class GamePaletteLoader {
    private: 
    static const size_t max_size_to_show_grid = 20;
    GamePaletteLoader();
    std::vector<std::vector<GameColor>> palettes_;
    std::vector<std::string> names_;
    void LoadPalette(const std::string& name, const std::string& path);

    public:
    static GamePaletteLoader& GetInstance();
    void AddPaletteObject(const ColorElement& obj);
    void LoadAllPalettes(const std::string& path);
   
    std::vector<GameColor>& GetPaleteeById(size_t id);
    const std::vector<std::string>& GetAllNames();
};