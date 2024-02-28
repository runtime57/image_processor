#include <cmath>

#include "blur.h"

double Blur::CountCoeff(size_t x, double sigma) const {
    double divisor = std::sqrt(2 * filters_const::PI * sigma * sigma);
    double power = -(std::pow(static_cast<double>(x) / sigma, 2) / 2);
    double e = std::exp(power);
    return e / divisor;
}

std::pair<size_t, size_t> Blur::GetBounds(size_t x0, size_t max) const {
    auto x = static_cast<double>(x0);
    size_t left = static_cast<size_t>(std::max(0.0, x - filters_const::SIGMA_MULTIPLIER * sigma_ - 1));
    size_t right =
        static_cast<size_t>(std::min(static_cast<double>(max), x + filters_const::SIGMA_MULTIPLIER * sigma_ + 1));
    return std::make_pair(left, right);
}

void Blur::Apply(Image &image) const {
    Image copy = image;
    auto height = image.GetHeight();
    auto width = image.GetWidth();
    for (size_t x0 = 0; x0 < height; ++x0) {
        for (size_t y0 = 0; y0 < width; ++y0) {
            RGB color{0, 0, 0};
            auto [lx, rx] = GetBounds(x0, height);  // x0 - 3 * sigma, x0 + 3*sigma
            double coeff_sum = 0;
            for (size_t x = lx; x < rx; ++x) {
                double cur_coeff = CountCoeff(std::max(x, x0) - std::min(x, x0), sigma_);
                color += copy.GetPixel(x, y0) * cur_coeff;
                coeff_sum += cur_coeff;
            }
            image.SetPixel(x0, y0, color * (1 / coeff_sum));
        }
    }

    copy = image;
    for (size_t x0 = 0; x0 < height; ++x0) {
        for (size_t y0 = 0; y0 < width; ++y0) {
            RGB color{0, 0, 0};
            auto [ly, ry] = GetBounds(y0, width);  // y0 - 3 * sigma, y0 + 3*sigma
            double coeff_sum = 0;
            for (size_t y = ly; y < ry; ++y) {
                double cur_coeff = CountCoeff(std::max(y, y0) - std::min(y, y0), sigma_);
                color += copy.GetPixel(x0, y) * cur_coeff;
                coeff_sum += cur_coeff;
            }
            image.SetPixel(x0, y0, color * (1 / coeff_sum));
        }
    }
}