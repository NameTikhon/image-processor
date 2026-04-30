#include "filters/FilterBase.h"

Color FilterBase::GetPixelSafe(Image& img, int x, int y) const {
    return img.GetPixel(x, y);
}

void FilterBase::ApplyMatrixFilter(Image& image, const std::vector<std::vector<double>>& matrix) const {
    int w = image.GetWidth();
    int h = image.GetHeight();
    int msize = static_cast<int>(matrix.size());
    int offset = msize / 2;

    Image result(w, h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double rSum = 0, gSum = 0, bSum = 0;
            for (int dy = -offset; dy <= offset; ++dy) {
                for (int dx = -offset; dx <= offset; ++dx) {
                    double coeff = matrix[dy + offset][dx + offset];
                    Color p = GetPixelSafe(image, x + dx, y + dy);
                    rSum += p.R * coeff;
                    gSum += p.G * coeff;
                    bSum += p.B * coeff;
                }
            }
            Color newColor(rSum, gSum, bSum);
            newColor.Clamp();
            result.SetPixel(x, y, newColor);
        }
    }
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            image.SetPixel(x, y, result.GetPixel(x, y));
        }
    }
}

void FilterBase::ToGrayscale(Color& c) const {
    double gray = 0.299 * c.R + 0.587 * c.G + 0.114 * c.B;
    c.R = c.G = c.B = gray;
}