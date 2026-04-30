#include "filters/EdgeDetectionFilter.h"
#include "filters/GrayscaleFilter.h"
#include <cmath>
#include <vector>
#include <stdexcept>
#include <algorithm>

EdgeDetectionFilter::EdgeDetectionFilter(double thr) : threshold_(thr) {
    if (threshold_ < 0.0 || threshold_ > 1.0) {
        throw std::runtime_error("edge threshold must be in [0, 1]");
    }
}

void EdgeDetectionFilter::Apply(Image& image) const {
    int w = image.GetWidth();
    int h = image.GetHeight();
    
    Image copy(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            copy.SetPixel(x, y, image.GetPixel(x, y));
        }
    }
    
    GrayscaleFilter().Apply(copy);
    
    const std::vector<std::vector<double>> kernel = {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
    };
    
    int msize = static_cast<int>(kernel.size());
    int offset = msize / 2;
    
    Image edges(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double val = 0;
            for (int dy = -offset; dy <= offset; ++dy) {
                for (int dx = -offset; dx <= offset; ++dx) {
                    double coeff = kernel[dy + offset][dx + offset];
                    Color p = copy.GetPixel(x + dx, y + dy);
                    val += p.R * coeff;
                }
            }
            val = std::clamp(val, 0.0, 1.0);
            edges.SetPixel(x, y, Color(val, val, val));
        }
    }
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            Color c = edges.GetPixel(x, y);
            if (c.R > threshold_) {
                image.SetPixel(x, y, Color(1.0, 1.0, 1.0));
            } else {
                image.SetPixel(x, y, Color(0.0, 0.0, 0.0));
            }
        }
    }
}