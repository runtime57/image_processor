#pragma once

#include "base.h"

class Blur : public BaseFilter {
public:
    explicit Blur(double sigma) {
        sigma_ = sigma;
    }

    void Apply(Image &image) const override;

private:
    double CountCoeff(size_t x, double sigma) const;
    std::pair<size_t, size_t> GetBounds(size_t x0, size_t max) const;
    double sigma_;
};