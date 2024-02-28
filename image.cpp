#include <iostream>
#include <fstream>
#include <string>

#include "exceptions.h"
#include "image.h"

RGB::RGB() {
    red = green = blue = 0;
}
RGB RGB::operator*(double a) const {
    return RGB{red * a, green * a, blue * a};
}
RGB &RGB::operator+=(RGB a) {
    red += a.red;
    blue += a.blue;
    green += a.green;
    return *this;
}
RGB RGB::operator+(RGB a) const {
    return {red + a.red, green + a.green, blue + a.blue};
}

RGB::RGB(double new_red, double new_green, double new_blue) : red(new_red), green(new_green), blue(new_blue) {
}

Image::Image(size_t width, size_t height) {
    SetPixels(std::vector<std::vector<RGB>>(height, std::vector<RGB>(width, RGB())));
}

std::vector<std::vector<RGB>> Image::GetPixels() const {
    return pixels_;
}

size_t Image::GetHeight() const {
    return pixels_.size();
}

size_t Image::GetWidth() const {
    if (GetHeight() == 0) {
        return 0;
    }
    return pixels_[0].size();
}

void Image::SetPixel(size_t x, size_t y, RGB color) {
    pixels_[x][y] = color;
}

void Image::SetPixels(std::vector<std::vector<RGB>> new_pixels) {
    pixels_ = new_pixels;
}

RGB Image::GetPixel(size_t x, size_t y) const {
    return pixels_[x][y];
}

size_t ReadSizeT(size_t start, unsigned char *arr, bool &was_negative) {
    int x = arr[start] + (arr[start + 1] << bmp_const::BYTE) + (arr[start + 2] << (2 * bmp_const::BYTE)) +
            (arr[start + 3] << (3 * bmp_const::BYTE));  // reading 4-bytes integer
    if (x < 0) {
        was_negative = true;
    }
    return static_cast<size_t>(abs(x));
}

void WriteSizeT(size_t value, size_t start, unsigned char *arr) {
    arr[start] = value;
    arr[start + 1] = (value >> bmp_const::BYTE);
    arr[start + 2] = (value >> (2 * bmp_const::BYTE));
    arr[start + 3] = (value >> (3 * bmp_const::BYTE));
}

void ReadString(std::ifstream &reading_file, size_t x, Image &image) {
    for (size_t y = 0; y < image.GetWidth(); ++y) {
        unsigned char color[3];
        reading_file.read(reinterpret_cast<char *>(color), 3);
        if (reading_file.eof()) {
            throw ReadImageException(
                "Failed to read damaged BMP. The actual size of the image isn't equal to the one specified in Header\n"
                "Check if your file is BMP-24 format file with no compression and colors table");
        }
        image.SetPixel(image.GetHeight() - x - 1, y,
                       RGB(static_cast<double>(color[0]) / bmp_const::COLOR_DIVISOR,
                           static_cast<double>(color[1]) / bmp_const::COLOR_DIVISOR,
                           static_cast<double>(color[2]) / bmp_const::COLOR_DIVISOR));
    }
}

Image ReadImage(std::string input_path) {
    std::ifstream reading_file;
    reading_file.open(input_path, std::ios::binary);

    if (!reading_file.is_open()) {
        throw ReadImageException("Can't open file - incorrect input path");
    }

    unsigned char file_header[bmp_const::HEADER_SIZE];
    reading_file.read(reinterpret_cast<char *>(file_header), bmp_const::HEADER_SIZE);
    if (reading_file.eof()) {
        throw ReadImageException(
            "Failed to read damaged BMP. Contains only Header or part of it\n"
            "Check if your file is BMP-24 format file with no compression and colors table");
    }

    unsigned char information_header[bmp_const::DIB_HEADER_SIZE];
    reading_file.read(reinterpret_cast<char *>(information_header), bmp_const::DIB_HEADER_SIZE);
    if (reading_file.eof()) {
        throw ReadImageException(
            "Failed to read damaged BMP. Contains only Header and DIB Header or part of it\n"
            "Check if your file is BMP-24 format file with no compression and colors table");
    }

    bool negative_height = false;
    auto file_size = ReadSizeT(2, file_header, negative_height);
    auto width = ReadSizeT(4, information_header, negative_height);
    negative_height = false;
    auto height = ReadSizeT(bmp_const::BYTE, information_header, negative_height);

    std::cout << (file_size & (bmp_const::BYTE + 4 + 2 + 1)) << ' ' << height * width << '\n';

    Image image(width, height);

    const int padding = ((4 - (static_cast<int>(width) * 3) % 4) % 4);

    if (file_size != bmp_const::HEADER_SIZE + bmp_const::DIB_HEADER_SIZE) {
        throw ReadImageException("Incorrect type of fyle");
    }

    if (!negative_height) {
        for (size_t x = 0; x < height; ++x) {
            ReadString(reading_file, x, image);
            reading_file.ignore(padding);
        }
    } else {
        for (size_t x = height - 1; x >= 0; --x) {
            ReadString(reading_file, x, image);
            reading_file.ignore(padding);
            if (x == 0) {
                break;
            }
        }
    }
    reading_file.close();
    return image;
}

void WriteImage(std::string output_path, const Image &image) {
    std::ofstream writing_file;
    writing_file.open(output_path, std::ios::binary);

    if (!writing_file.is_open()) {
        throw WriteImageException("Incorrect output path");
    }

    unsigned char padding_array[3] = {0, 0, 0};
    const int padding = ((4 - (static_cast<int>(image.GetWidth()) * 3) % 4) % 4);

    const int file_size = static_cast<int>(bmp_const::HEADER_SIZE + bmp_const::DIB_HEADER_SIZE +
                                           image.GetHeight() * image.GetWidth() * 3 + padding * image.GetHeight());

    unsigned char header[bmp_const::HEADER_SIZE] = {};
    header[0] = 'B';
    header[1] = 'M';
    WriteSizeT(file_size, 2, header);
    WriteSizeT(bmp_const::HEADER_SIZE + bmp_const::DIB_HEADER_SIZE, bmp_const::TEN, header);

    unsigned char dib_header[bmp_const::DIB_HEADER_SIZE] = {};
    WriteSizeT(bmp_const::DIB_HEADER_SIZE, 0, dib_header);
    WriteSizeT(image.GetWidth(), bmp_const::FOUR, dib_header);
    WriteSizeT(image.GetHeight(), bmp_const::BYTE, dib_header);
    dib_header[bmp_const::BYTE + bmp_const::FOUR] = 1;
    dib_header[bmp_const::TEN + bmp_const::FOUR] = 3 * bmp_const::BYTE;

    writing_file.write(reinterpret_cast<char *>(header), bmp_const::HEADER_SIZE);
    writing_file.write(reinterpret_cast<char *>(dib_header), bmp_const::DIB_HEADER_SIZE);

    for (size_t x = 0; x < image.GetHeight(); ++x) {
        for (size_t y = 0; y < image.GetWidth(); ++y) {
            auto rgb_color = image.GetPixel(image.GetHeight() - x - 1, y);
            unsigned char color[3] = {static_cast<unsigned char>(rgb_color.red * bmp_const::COLOR_DIVISOR),
                                      static_cast<unsigned char>(rgb_color.green * bmp_const::COLOR_DIVISOR),
                                      static_cast<unsigned char>(rgb_color.blue * bmp_const::COLOR_DIVISOR)};
            writing_file.write(reinterpret_cast<char *>(color), 3);
        }
        writing_file.write(reinterpret_cast<char *>(padding_array), padding);
    }
    writing_file.close();
}