#pragma once

#include "filters/FilterBase.h"

class CrystallizeFilter : public FilterBase {
private:
    int cellSize_;

public:
    CrystallizeFilter(int cellSize = 8);
    void Apply(Image& image) const override;
};