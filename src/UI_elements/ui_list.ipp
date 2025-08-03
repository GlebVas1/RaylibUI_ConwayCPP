
template<typename T>
UIList<T>::UIList() {}

template<typename T>
UIList<T>::UIList(int x, int y) : UIElement(x, y, 200, 200) {

}

template<typename T>
void UIList<T>::SetVector(const std::vector<T>& original) {
    elements_ = original;
}

template <typename T>
void UIList<T>::Draw() {
    RenderTexture2D list_texture = LoadRenderTexture(box_width_, box_width_);
    BeginTextureMode(list_texture);
    ClearBackground({0, 0, 0, 0});
    for (int i = 0; i < elements_.size();  ++i) {
        
    }
}