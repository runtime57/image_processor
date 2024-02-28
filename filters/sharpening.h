#pragma once

#include "base.h"

class Sharpening : public BaseFilterWithMatrix {
public:
    Sharpening() {
        matrix_ = filters_const::SHARPENING_MATRIX;
    }

    void Apply(Image &image) const override;
};