#include "read_and_write/BMPProcessor.h"
#include "pipeline/Pipeline.h"
#include "parse/Parser.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        auto parsed = Parser::ParseArgs(argc, argv);
        Image image = BMPProcessor::ReadBMP(parsed.inputPath);
        Pipeline pipeline;
        for (auto& filter : parsed.filters) {
            pipeline.AddFilter(std::move(filter));
        }
        pipeline.Run(image);
        BMPProcessor::WriteBMP(image, parsed.outputPath);
        std::cout << "Processing completed successfully!\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}