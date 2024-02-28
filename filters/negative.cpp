#include "negative.h"

Negative::Negative() {
}

void Negative::Apply(Image &image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            RGB color = image.GetPixel(x, y);
            color.red = 1 - color.red;
            color.green = 1 - color.green;
            color.blue = 1 - color.blue;
            image.SetPixel(x, y, color);
        }
    }
}