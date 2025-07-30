#include "controller.h"

Controller::Controller() : field(Field::GetInstance()), ui(UI::GetInstance()) {}

Controller::~Controller() {}
Controller& Controller::GetInstance() {
    static Controller obj;
    return obj;
}

void Controller::StartUI() {

}