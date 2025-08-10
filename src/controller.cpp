#include "controller.h"
#include "ui.h"
#include "field.h"
#include "game_objects_loader.h"

Controller::Controller() {
    ui = &UI::GetInstance();
    ui->SetController(this);
    field = &Field::GetInstance();
    field->SetController(this);
}

Controller::~Controller() {}

Controller& Controller::GetInstance() {
    static Controller obj;
    return obj;
}

const std::vector<std::string>& Controller::GetAllObjectsNames() {
   return GameObjectLoader::GetInstance().GetAllNames();
}

void Controller::SetObject(size_t ind) {
    ui->SetGameObject(GameObjectLoader::GetInstance().GetObjectById(ind));
}

void Controller::SetFieldPixel(int x, int y, uint8_t val) {
    field->SetPixelAt(x, y, val);
}

void Controller::SetFieldRule(size_t ind) {
    field->SetGameRule(ALL_RULES[ind]);
    ui->SetColorCount(ALL_RULES[ind]->maximum_age);
}

GameRule* Controller::GetFieldRule() {
    return field->GetGameRule();
}

void Controller::SetPalette(size_t ind) {
    field->SetColorPallette(&(ALL_PALLETTES[ind].pallette));
    ui->SetColorPallette(ALL_PALLETTES[ind].pallette);
}

void Controller::SetFieldSize(size_t x, size_t y) {
    field->SetNewDimensions(x, y);
}

void Controller::StartUI() {
    
    ui->InitializeElements();
    ui->SetColorBuffer(field->GetColorBuffer());


    auto gcp = GameColorBW();
    auto gr = ALL_RULES[0];

    ui->SetColorPallette(gcp);
    ui->SetColorCount(gr->maximum_age);

    ui->SetGameObject(ALL_OBJECTS[0]);
    // ui->InitPalette();
    
    ui->Start();
}

void Controller::SetFPS(size_t val) {
    field->SetFPS(val);
}

float Controller::GetFPS() {
    return field->GetFPS();
}

void Controller::SetPause(float val) {
    field->SetPause(val);
}


void Controller::Start() {

    auto gcp = GameColorBW();
    auto gr = ALL_RULES[0];
    field->SetColorPallette(&gcp);
    field->SetGameRule(gr);

    field->CreateUpdateThreads();

    /* To allow loading textures cause of raylib subtles*/
    ui->InitializeWindow();
    //GameObjectLoader::GetInstance();
    GameObjectLoader::GetInstance().LoadAllObjects("../GameObjects/all_objects.txt");

    std::thread t(&Field::MultiThreadUpdating, field);
   
    StartUI();
    t.join();
}

void Controller::SetNewColorBuffer(uint8_t* buffer) {
    ui->SetColorBuffer(buffer);
}