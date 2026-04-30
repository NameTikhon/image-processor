#pragma once

#include "filters/FilterBase.h"

class SharpeningFilter : public FilterBase {
public:
    void Apply(Image& image) const override;
};