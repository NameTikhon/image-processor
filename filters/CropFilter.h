#pragma once

#include "filters/FilterBase.h"

class CropFilter : public FilterBase {
private:
    int newWidth_, newHeight_;

public:
    CropFilter(int width, int height);
    void Apply(Image& image) const override;
};