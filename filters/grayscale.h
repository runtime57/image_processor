#pragma once

#include "base.h"

class Grayscale : public BaseFilter {
public:
    Grayscale();
    void Apply(Image &image) const override;
};