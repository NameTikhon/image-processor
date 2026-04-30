#pragma once

#include "image/Color.h"
#include <vector>

class Image {
private:
    int width_;
    int height_;
    std::vector<Color> pixels_;

public:
    Image(int w = 0, int h = 0);
    int GetWidth() const;
    int GetHeight() const;
    Color& GetPixel(int x, int y);
    void SetPixel(int x, int y, const Color& color);
    void Fill(const Color& color);
};