#pragma once

#include "image/Image.h"
#include <string>
#include <cstdint>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;
};

struct BMPInfoHeader {
    uint32_t headerSize;
    int32_t width, height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    int32_t xPixelsPerM, yPixelsPerM;
    uint32_t colorsUsed, colorsImportant;
};
#pragma pack(pop)

class BMPProcessor {
public:
    static Image ReadBMP(const std::string& filename);
    static void WriteBMP(Image& image, const std::string& filename);
};