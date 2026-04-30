#pragma once

#include "image/Image.h"
#include <vector>

class FilterBase {
public:
    virtual ~FilterBase() = default;
    virtual void Apply(Image& image) const = 0;

protected:
    Color GetPixelSafe(Image& img, int x, int y) const;
    void ApplyMatrixFilter(Image& image, const std::vector<std::vector<double>>& matrix) const;
    void ToGrayscale(Color& c) const;
};