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
    ui->InitializeElements();
    ui->SetColorBuffer(field->GetColorBuffer());

    auto gcp = GameColorBW();
    //auto gr = GameRule_STATIC;
    auto gr = GameRule_FREESTAR;
    field->SetColorPallette(&gcp);
    field->SetGameRule(&gr);

    ui->SetColorPallette(gcp);
    ui->SetColorCount(gr.maximum_age);

    ui->Start();
}

void Controller::SetFieldPixel(int x, int y, uint8_t val) {
    field->SetPixelAt(x, y, val);
}

void Controller::Start() {
    auto gcp = GameColorFlame();
    //auto gr = GameRule_STATIC;
    auto gr = GameRule_FREESTAR;
    field->SetColorPallette(&gcp);
    field->SetGameRule(&gr);

    field->CreateUpdateThreads();

    std::thread t(&Field::MultiThreadUpdating, field);
   
    StartUI();
    t.join();
}

