#include "controller.h"
#include "ui.h"
#include "field.h"

Controller::Controller() {
    std::cout << "A " << std::endl;
    ui = &UI::GetInstance();
    ui->SetController(this);
    std::cout << "B " << std::endl;
    field = &Field::GetInstance();
    field->SetController(this);
    std::cout << "C " << std::endl;
}

Controller::~Controller() {}

Controller& Controller::GetInstance() {
    static Controller obj;
    return obj;
}

void Controller::StartUI() {
    std::cout << "AAAA" << std::endl;
    ui->SetColorBuffer(field->GetColorBuffer());
    ui->InitializeElements();
    std::cout << "BBB" << std::endl;
    ui->Start();
}

void Controller::SetFieldPixel(size_t x, size_t y, uint8_t val) {
    field->SetPixelAt(x, y, val);
}

void Controller::StartField() {
    auto gcp = GameColorBW();
    auto gr = GameRule_STATIC;

    field->SetColorPallette(&gcp);
    field->SetGameRule(&gr);

    field->CreateUpdateThreads();

    std::thread t(&Field::MultiThreadUpdating, field);
    t.join();
}