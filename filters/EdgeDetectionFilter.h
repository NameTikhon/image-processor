#pragma once

#include "filters/FilterBase.h"

class EdgeDetectionFilter : public FilterBase {
private:
    double threshold_;

public:
    EdgeDetectionFilter(double thr);
    void Apply(Image& image) const override;
};