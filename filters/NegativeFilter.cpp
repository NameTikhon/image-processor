#include "filters/NegativeFilter.h"

void NegativeFilter::Apply(Image& image) const {
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            Color& c = image.GetPixel(x, y);
            c.R = 1 - c.R;
            c.G = 1 - c.G;
            c.B = 1 - c.B;
            c.Clamp();
        }
    }
}