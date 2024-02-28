#pragma once

#include <vector>

#include "image.h"

namespace filters_const {
// matrixes with filters:
const std::vector<std::vector<double>> SHARPENING_MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
const std::vector<std::vector<double>> EDGE_MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

// blur
const double PI = 3.141592653589793238462643383279;
const int SIGMA_MULTIPLIER = 3;

// grayscale
const double RED_MULTIPLIER = 0.114;
const double GREEN_MULTIPLIER = 0.587;
const double BLUE_MULTIPLIER = 0.299;
}  // namespace filters_const

class BaseFilter {
public:
    virtual void Apply(Image& image) const = 0;

    virtual ~BaseFilter() = default;
};

class BaseFilterWithMatrix : public BaseFilter {
public:
    virtual void ApplyMatrix(Image& image) const;

protected:
    std::vector<std::vector<double>> matrix_;
};