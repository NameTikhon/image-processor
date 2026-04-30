#pragma once

#include "filters/FilterBase.h"
#include <memory>
#include <vector>

class Pipeline {
private:
    std::vector<std::unique_ptr<FilterBase>> filters_;

public:
    void AddFilter(std::unique_ptr<FilterBase> filter);
    void Run(Image& image);
};