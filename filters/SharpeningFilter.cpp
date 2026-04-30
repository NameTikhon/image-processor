#include "filters/SharpeningFilter.h"

void SharpeningFilter::Apply(Image& image) const {
    const std::vector<std::vector<double>> matrix = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
    };
    ApplyMatrixFilter(image, matrix);
}