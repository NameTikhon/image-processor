#pragma once

#include "filters/FilterBase.h"

class NegativeFilter : public FilterBase {
public:
    void Apply(Image& image) const override;
};