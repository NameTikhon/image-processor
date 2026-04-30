#include "parse/Parser.h"
#include <iostream>
#include <stdexcept>

ParserOutput Parser::ParseArgs(int argc, char** argv) {
    ParserOutput result;
    
    if (argc == 1) {
        PrintHelp();
        throw std::runtime_error("No arguments provided");
    }
    
    if (argc < 3) {
        throw std::runtime_error("Input and output files are required");
    }
    
    result.inputPath = argv[1];
    result.outputPath = argv[2];

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-crop") {
            if (i + 2 >= argc) {
                throw std::runtime_error("Crop filter requires width and height");
            }
            int w = std::stoi(argv[++i]);
            int h = std::stoi(argv[++i]);
            result.filters.push_back(std::make_unique<CropFilter>(w, h));
        } else if (arg == "-gs") {
            result.filters.push_back(std::make_unique<GrayscaleFilter>());
        } else if (arg == "-neg") {
            result.filters.push_back(std::make_unique<NegativeFilter>());
        } else if (arg == "-sharp") {
            result.filters.push_back(std::make_unique<SharpeningFilter>());
        } else if (arg == "-edge") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Edge filter requires threshold");
            }
            double thr = std::stod(argv[++i]);
            result.filters.push_back(std::make_unique<EdgeDetectionFilter>(thr));
        } else if (arg == "-blur") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Blur filter requires sigma");
            }
            double sigma = std::stod(argv[++i]);
            result.filters.push_back(std::make_unique<GaussianBlurFilter>(sigma));
        } else if (arg == "-crystallize") {
            int cellSize = 8;
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                cellSize = std::stoi(argv[++i]);
            }
            result.filters.push_back(std::make_unique<CrystallizeFilter>(cellSize));
        } else {
            throw std::runtime_error("Unknown filter: " + arg);
        }
    }
    return result;
}

void Parser::PrintHelp() {
    std::cout << "Usage: image_processor <input.bmp> <output.bmp> [filters...]\n\n";
    std::cout << "Available filters:\n";
    std::cout << "  -crop width height         Crop image\n";
    std::cout << "  -gs                        Convert to grayscale\n";
    std::cout << "  -neg                       Invert colors\n";
    std::cout << "  -sharp                     Sharpen image\n";
    std::cout << "  -edge threshold            Edge detection\n";
    std::cout << "  -blur sigma                Gaussian blur\n";
    std::cout << "  -crystallize [cellSize]    Crystallize effect (additional filter)\n\n";
    std::cout << "Example:\n";
    std::cout << "  image_processor input.bmp output.bmp -crop 800 600 -gs -edge 0.5\n";
}