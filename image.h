#pragma once

#include <cstdint>
#include <string>
#include <vector>

struct RGB {
    double red;
    double green;
    double blue;

    RGB();

    RGB(double new_red, double new_green, double new_blue);

    RGB operator*(double a) const;

    RGB& operator+=(RGB a);

    RGB operator+(RGB a) const;
};

namespace bmp_const {
const size_t HEADER_SIZE = 14;
const size_t DIB_HEADER_SIZE = 40;
const double COLOR_DIVISOR = 255;
const size_t FOUR = 4;
const size_t BYTE = 8;
const size_t TEN = 10;

}  // namespace bmp_const

class Image {
public:
    Image();
    Image(size_t width, size_t height);

    void SetPixels(std::vector<std::vector<RGB>> new_pixels);

    void SetPixel(size_t x, size_t y, RGB color);

    std::vector<std::vector<RGB>> GetPixels() const;

    size_t GetHeight() const;

    size_t GetWidth() const;

    RGB GetPixel(size_t x, size_t y) const;

private:
    std::vector<std::vector<RGB>> pixels_;
};

size_t ReadSizeT(size_t start, unsigned char* arr, bool& was_negative);

void WriteSizeT(size_t value, size_t start, unsigned char* arr);

Image ReadImage(std::string input_path);

void ReadString(std::ifstream& f, size_t x, Image& image);

void WriteImage(std::string output_path, const Image& image);