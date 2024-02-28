#include "base.h"

RGB CountColor(std::vector<std::vector<RGB>> &p, const std::vector<std::vector<double>> &matrix) {
    RGB color{0, 0, 0};
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            color.red += p[i][j].red * matrix[i][j];
            color.green += p[i][j].green * matrix[i][j];
            color.blue += p[i][j].blue * matrix[i][j];
        }
    }
    const double one = 1;
    const double zero = 0;
    color.red = std::min(one, std::max(zero, color.red));
    color.green = std::min(one, std::max(zero, color.green));
    color.blue = std::min(one, std::max(zero, color.blue));
    return color;
}

void BaseFilterWithMatrix::ApplyMatrix(Image &image) const {
    auto p = image.GetPixels();
    size_t height = image.GetHeight();
    size_t width = image.GetWidth();
    for (size_t x = 0; x < height; ++x) {
        for (size_t y = 0; y < width; ++y) {
            std::vector<std::vector<RGB>> pixels(3, std::vector<RGB>(3, RGB()));
            pixels[0][0] = p[(x > 0 ? x - 1 : 0)][(y > 0 ? y - 1 : 0)];
            pixels[0][1] = p[(x > 0 ? x - 1 : 0)][y];
            pixels[0][2] = p[(x > 0 ? x - 1 : 0)][std::min(width - 1, y + 1)];

            pixels[1][0] = p[x][(y > 0 ? y - 1 : 0)];
            pixels[1][1] = p[x][y];
            pixels[1][2] = p[x][std::min(width - 1, y + 1)];

            pixels[2][0] = p[std::min(height - 1, x + 1)][(y > 0 ? y - 1 : 0)];
            pixels[2][1] = p[std::min(height - 1, x + 1)][y];
            pixels[2][2] = p[std::min(height - 1, x + 1)][std::min(width - 1, y + 1)];

            image.SetPixel(x, y, CountColor(pixels, matrix_));
        }
    }
}