#include "filters/CrystallizeFilter.h"
#include <cstdlib>
#include <algorithm>

CrystallizeFilter::CrystallizeFilter(int cellSize) : cellSize_(cellSize) {}

void CrystallizeFilter::Apply(Image& image) const {
    int w = image.GetWidth();
    int h = image.GetHeight();
    Image result(w, h);
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int cellX = (x / cellSize_) * cellSize_;
            int cellY = (y / cellSize_) * cellSize_;
            int offsetX = (x % cellSize_) * 2 - cellSize_;
            int offsetY = (y % cellSize_) * 2 - cellSize_;
            int srcX = std::clamp(cellX + offsetX, 0, w - 1);
            int srcY = std::clamp(cellY + offsetY, 0, h - 1);
            
            Color c = image.GetPixel(srcX, srcY);
            double noise = (static_cast<double>(rand()) / RAND_MAX - 0.5) * 0.2;
            c.R = std::clamp(c.R + noise, 0.0, 1.0);
            c.G = std::clamp(c.G + noise, 0.0, 1.0);
            c.B = std::clamp(c.B + noise, 0.0, 1.0);
            result.SetPixel(x, y, c);
        }
    }
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            image.SetPixel(x, y, result.GetPixel(x, y));
        }
    }
}