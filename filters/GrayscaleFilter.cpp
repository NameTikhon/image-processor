#include "filters/GrayscaleFilter.h"

void GrayscaleFilter::Apply(Image& image) const {
    for (int y = 0; y < image.GetHeight(); y++) {
        for (int x = 0; x < image.GetWidth(); x++) {
            Color& pixel = image.GetPixel(x, y);
            double gray = 0.299 * pixel.R + 0.587 * pixel.G + 0.114 * pixel.B;
            pixel.R = pixel.G = pixel.B = gray;
            pixel.Clamp();
        }
    }
}