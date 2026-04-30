#pragma once

#include "filters/FilterBase.h"
#include <vector>

class GaussianBlurFilter : public FilterBase {
private:
    double sigma_;
    std::vector<double> GenerateGaussianKernel1D() const;

public:
    GaussianBlurFilter(double sigma);
    void Apply(Image& image) const override;
};