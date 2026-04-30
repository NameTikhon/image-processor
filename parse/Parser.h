#pragma once

#include "filters/FilterBase.h"
#include "filters/CropFilter.h"
#include "filters/GrayscaleFilter.h"
#include "filters/NegativeFilter.h"
#include "filters/SharpeningFilter.h"
#include "filters/EdgeDetectionFilter.h"
#include "filters/GaussianBlurFilter.h"
#include "filters/CrystallizeFilter.h"
#include <memory>
#include <string>
#include <vector>

struct ParserOutput {
    std::string inputPath, outputPath;
    std::vector<std::unique_ptr<FilterBase>> filters;
};

class Parser {
public:
    static ParserOutput ParseArgs(int argc, char** argv);
    static void PrintHelp();
};