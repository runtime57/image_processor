#pragma once

#include "base.h"

class Crop : public BaseFilter {
public:
    Crop();

    explicit Crop(size_t new_height, size_t new_width);

    void Apply(Image &image) const override;

    void SetParams(size_t new_height, size_t new_width);

private:
    size_t height_{0};
    size_t width_{0};
};