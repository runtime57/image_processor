#pragma once

#include "base.h"
#include "grayscale.h"

class Edge : public BaseFilterWithMatrix {
public:
    explicit Edge(double threshold) {
        threshold_ = threshold;
        matrix_ = filters_const::EDGE_MATRIX;
    }

    void Apply(Image &image) const override;

private:
    double threshold_;
};