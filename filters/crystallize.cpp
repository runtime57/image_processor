#include <iostream>

#include "crystallize.h"

Crystallize::Crystallize(size_t number) {
    number_ = number;
}

Crystallize::Centers::Centers() {
}

Crystallize::Centers::Centers(size_t number, const Image& image) {
    height = image.GetHeight();
    width = image.GetWidth();
    number = std::min(number, height * width);
    size_t size = height * width;
    is_center = std::vector<bool>(size, false);
    for (size_t i = 0; i < number; ++i) {
        size_t current = static_cast<size_t>(gen_random()) % size;
        while (is_center[current]) {
            current = static_cast<size_t>(gen_random()) % size;
        }
        is_center[current] = true;
    }
}

bool Crystallize::Centers::IsCenter(size_t x, size_t y) {
    size_t coord = x * width + y;
    return is_center[coord];
}

RGB Crystallize::Centers::GetNearest(size_t x, size_t y, const Image& image) {
    size_t dist = 0;
    while (true) {
        for (size_t dx = 0; dx <= dist; ++dx) {
            size_t dy = dist - dx;

            if (dx <= x && dy <= y && IsCenter(x - dx, y - dy)) {
                return image.GetPixel(x - dx, y - dy);
            }
            if (dx <= x && y + dy < width && IsCenter(x - dx, y + dy)) {
                return image.GetPixel(x - dx, y + dy);
            }
            if (x + dx < height && dy <= y && IsCenter(x + dx, y - dy)) {
                return image.GetPixel(x + dx, y - dy);
            }
            if (x + dx < height && y + dy < width && IsCenter(x + dx, y + dy)) {
                return image.GetPixel(x + dx, y + dy);
            }
        }
        ++dist;
    }
}

void Crystallize::Apply(Image& image) const {
    Centers centers(number_, image);
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            auto color_of_nearest_center = centers.GetNearest(x, y, std::as_const(image));
            image.SetPixel(x, y, color_of_nearest_center);
        }
    }
}