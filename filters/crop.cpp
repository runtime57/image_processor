#include "crop.h"

Crop::Crop() {
}
Crop::Crop(size_t new_height, size_t new_width) {
    SetParams(new_height, new_width);
}
void Crop::SetParams(size_t new_height, size_t new_width) {
    height_ = new_height;
    width_ = new_width;
}
void Crop::Apply(Image &image) const {
    size_t actual_width = std::min(width_, image.GetWidth());
    size_t actual_height = std::min(height_, image.GetHeight());
    std::vector<std::vector<RGB>> pixels(actual_height, std::vector<RGB>(actual_width));
    for (size_t x = 0; x < pixels.size(); ++x) {
        for (size_t y = 0; y < std::min(width_, image.GetWidth()); ++y) {
            pixels[x][y] = image.GetPixel(x, y);
        }
    }
    image.SetPixels(pixels);
}