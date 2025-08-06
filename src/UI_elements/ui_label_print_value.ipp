#include "../UI_Tools/ui_tools.h"

template<typename T>
UILabelPrintValue<T>::UILabelPrintValue(int x, int y, const std::string& text_format, std::function<T()> func) :
    UIElement(x, y, 10, 10) {
    text_format_ = text_format;
    get_value_ = func;
}

template<typename T>
void UILabelPrintValue<T>::Draw() {
    std::cout << get_value_() << std::endl;
    UITools::DrawTextDefault(
        GetAbsoluteXPosition(), 
        GetAbsoluteYPosition(), 
        TextFormat(text_format_.c_str(), get_value_()),
        18,
        ui.ui_text_dark
    );
}