#include "image/Image.h"
#include <algorithm>

Image::Image(int w, int h) : width_(w), height_(h), pixels_(w * h) {}

int Image::GetWidth() const {
    return width_;
}

int Image::GetHeight() const {
    return height_;
}

Color& Image::GetPixel(int x, int y) {
    x = std::clamp(x, 0, width_ - 1);
    y = std::clamp(y, 0, height_ - 1);
    return pixels_[y * width_ + x];
}

void Image::SetPixel(int x, int y, const Color& color) {
    if (x >= 0 && x < width_ && y >= 0 && y < height_) {
        pixels_[y * width_ + x] = color;
    }
}

void Image::Fill(const Color& color) {
    std::fill(pixels_.begin(), pixels_.end(), color);
}