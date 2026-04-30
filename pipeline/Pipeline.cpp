#include "pipeline/Pipeline.h"

void Pipeline::AddFilter(std::unique_ptr<FilterBase> filter) {
    filters_.push_back(std::move(filter));
}

void Pipeline::Run(Image& image) {
    for (auto& filter : filters_) {
        filter->Apply(image);
    }
}