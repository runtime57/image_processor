#include "grayscale.h"

Grayscale::Grayscale() {
}

void Grayscale::Apply(Image &image) const {
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            RGB color = image.GetPixel(x, y);
            double result = color.red * filters_const::RED_MULTIPLIER + color.green * filters_const::GREEN_MULTIPLIER +
                            color.blue * filters_const::BLUE_MULTIPLIER;
            color.red = result;
            color.blue = result;
            color.green = result;
            image.SetPixel(x, y, color);
        }
    }
}