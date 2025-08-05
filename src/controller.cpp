#include "controller.h"
#include "ui.h"
#include "field.h"

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

void Controller::StartUI() {
    ui->InitializeWindow();
    ui->InitializeElements();
    ui->SetColorBuffer(field->GetColorBuffer());


    auto gcp = GameColorBW();
    auto gr = GameRule_FREESTAR;

    ui->SetColorPallette(gcp);
    ui->SetColorCount(gr.maximum_age);

    ui->SetGameObject(ALL_OBJECTS[0]);
    // ui->InitPalette();
    
    ui->Start();
}

void Controller::SetFieldPixel(int x, int y, uint8_t val) {
    field->SetPixelAt(x, y, val);
}

void Controller::Start() {

    auto gcp = GameColorBW();
    auto gr = GameRule_FREESTAR;
    field->SetColorPallette(&gcp);
    field->SetGameRule(&gr);

    field->CreateUpdateThreads();

    std::thread t(&Field::MultiThreadUpdating, field);
   
    StartUI();
    t.join();
}

void Controller::SetFieldRule(size_t ind) {
    field->SetGameRule(&ALL_RULES[ind]);
    ui->SetColorCount(ALL_RULES[ind].maximum_age);
}

void Controller::SetPalette(size_t ind) {
    field->SetColorPallette(&(ALL_PALLETTES[ind].pallette));
    ui->SetColorPallette(ALL_PALLETTES[ind].pallette);
}

void Controller::SetPause(float val) {
    field->SetPause(val);
}