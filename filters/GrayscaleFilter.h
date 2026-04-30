#pragma once

#include "filters/FilterBase.h"

class GrayscaleFilter : public FilterBase {
public:
    void Apply(Image& image) const override;
};