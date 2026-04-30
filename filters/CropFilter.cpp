#include "filters/CropFilter.h"

CropFilter::CropFilter(int width, int height) : newWidth_(width), newHeight_(height) {}

void CropFilter::Apply(Image& image) const {
    if (newWidth_ <= 0 || newHeight_ <= 0) {
        return;
    }

    int oldWidth = image.GetWidth();
    int oldHeight = image.GetHeight();

    Image cropped(newWidth_, newHeight_);
    for (int y = 0; y < newHeight_ && y < oldHeight; ++y) {
        for (int x = 0; x < newWidth_ && x < oldWidth; ++x) {
            cropped.SetPixel(x, y, image.GetPixel(x, y));
        }
    }
    image = cropped;
}