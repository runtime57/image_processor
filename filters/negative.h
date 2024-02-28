#pragma once

#include "base.h"

class Negative : public BaseFilter {
public:
    Negative();

    void Apply(Image &image) const override;
};