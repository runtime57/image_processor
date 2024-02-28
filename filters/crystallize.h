#pragma once

#include "base.h"

#include <random>
#include <unordered_set>

class Crystallize : public BaseFilter {
public:
    explicit Crystallize(size_t number);

    void Apply(Image &image) const override;

    struct Centers {
        std::vector<bool> is_center;
        std::mt19937 gen_random;
        size_t height;
        size_t width;

        Centers();

        Centers(size_t number, const Image &image);

        bool IsCenter(size_t x, size_t y);

        RGB GetNearest(size_t x, size_t y, const Image &image);
    };

private:
    size_t number_;
};
