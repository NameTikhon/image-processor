#include "filters/GaussianBlurFilter.h"
#include <cmath>

GaussianBlurFilter::GaussianBlurFilter(double sigma) : sigma_(sigma) {}

std::vector<double> GaussianBlurFilter::GenerateGaussianKernel1D() const {
    int size = static_cast<int>(std::ceil(sigma_ * 3)) * 2 + 1;

    if (size < 1) {
        size = 1;
    }

    std::vector<double> kernel(size);
    double sum = 0;
    int off = size / 2;
    
    for (int i = -off; i <= off; ++i) {
        double val = std::exp(-(i*i) / (2 * sigma_ * sigma_));
        kernel[i + off] = val;
        sum += val;
    }
    
    for (auto& v : kernel) {
        v /= sum;
    }
    return kernel;
}

void GaussianBlurFilter::Apply(Image& image) const {
    if (sigma_ <= 0.01) {
        return;
    }
    
    auto kernel = GenerateGaussianKernel1D();
    int w = image.GetWidth();
    int h = image.GetHeight();
    int ksize = static_cast<int>(kernel.size());
    int offset = ksize / 2;
    
    Image temp(w, h);
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double rSum = 0, gSum = 0, bSum = 0;
            for (int dx = -offset; dx <= offset; ++dx) {
                int nx = x + dx;

                if (nx < 0) {
                    nx = 0;
                }
                if (nx >= w) {
                    nx = w - 1;
                }

                double coeff = kernel[dx + offset];
                Color p = image.GetPixel(nx, y);
                rSum += p.R * coeff;
                gSum += p.G * coeff;
                bSum += p.B * coeff;
            }
            temp.SetPixel(x, y, Color(rSum, gSum, bSum));
        }
    }
    
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double rSum = 0, gSum = 0, bSum = 0;
            for (int dy = -offset; dy <= offset; ++dy) {
                int ny = y + dy;

                if (ny < 0) {
                    ny = 0;
                }
                if (ny >= h) {
                    ny = h - 1;
                }

                double coeff = kernel[dy + offset];
                Color p = temp.GetPixel(x, ny);
                rSum += p.R * coeff;
                gSum += p.G * coeff;
                bSum += p.B * coeff;
            }
            Color newColor(rSum, gSum, bSum);
            newColor.Clamp();
            image.SetPixel(x, y, newColor);
        }
    }
}