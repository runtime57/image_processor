#include "edge.h"
#include "grayscale.h"

void Edge::Apply(Image &image) const {
    Grayscale grayscale;
    grayscale.Apply(image);
    ApplyMatrix(image);
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            RGB color = image.GetPixel(x, y);
            if (color.red > threshold_) {
                color.red = color.blue = color.green = 1.0;
            } else {
                color.red = color.blue = color.green = 0.0;
            }
            image.SetPixel(x, y, color);
        }
    }
}