#include "raylib.h"
#include "game_objects_loader.h"

GameObjectLoader::GameObjectLoader() {}

void GameObjectLoader::LoadObject(const std::string& name, const std::string& path) {
    std::cout << "GameObjectLoader start load " << name << " on path " << path << std::endl;
    Texture2D texture = LoadTexture(path.c_str());
    
    if (texture.width != texture.height) {
        return;
        std::cerr << "GameObjectLoader bad texture" << std::endl;
    }

    size_t size = texture.width;
    Image object_image = LoadImageFromTexture(texture);
    Color* pixels = LoadImageColors(object_image);

    std::cout << "GameObjectLoader start fill" << std::endl;
    GameObject obj;
    obj.array = std::vector<std::vector<uint8_t>>(size, std::vector<uint8_t>(size, 0));
    for (size_t x = 0; x < size; ++x) {
        for (size_t y = 0; y < size; ++y) {
            if (pixels[x * size + y].r > 50 &&
                pixels[x * size + y].g > 50 && 
                pixels[x * size + y].b > 50) { 
                obj.array[x][y] = 1; 
            }
        }
    }

    UnloadImage(object_image);
    UnloadImageColors(pixels);

    obj.should_grid_show = size < max_size_to_show_grid;
    obj.name = name;
    obj.size = size;

    names_.push_back(obj.name);
    objects_.push_back(obj);

    std::cout << "GameObjectLoader success " << name << " on path " << path << std::endl;
}

GameObjectLoader& GameObjectLoader::GetInstance() {
    static GameObjectLoader obj;
    return obj;
}

void GameObjectLoader::AddGameObject(const GameObject& obj) {
    objects_.push_back(obj);
    names_.push_back(obj.name);
}

void GameObjectLoader::LoadAllObjects(const std::string& path) {

    std::ifstream all_objects_file(path);
    std::string object_name;
    std::string object_path;
    
    while (!all_objects_file.eof()){
        all_objects_file >> object_name >> object_path;
        LoadObject(object_name, object_path); 
    }
    all_objects_file.close();
}

const GameObject& GameObjectLoader::GetObjectById(size_t id) {
    return objects_[id];
}

const std::vector<std::string>& GameObjectLoader::GetAllNames() {
    return names_;
}
