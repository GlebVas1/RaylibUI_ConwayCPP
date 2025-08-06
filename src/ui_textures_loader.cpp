#include "ui_textures_loader.h"

    private:
    UITextureLoader();
    std::unordered_map<std::string, Texture2D> map_;
    public:
    UITextureLoader& GetInstance();
    void LoadTexture(std::string name, std::string path);
    Texture2D* GetTexture(std::string name);
    void LoadAllTextures();