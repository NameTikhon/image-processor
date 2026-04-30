#include "read_and_write/BMPProcessor.h"
#include <fstream>
#include <stdexcept>

Image BMPProcessor::ReadBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(BMPFileHeader));
    file.read(reinterpret_cast<char*>(&infoHeader), sizeof(BMPInfoHeader));

    if (fileHeader.signature != 0x4D42) {
        throw std::runtime_error("Not a BMP file");
    }

    int width = infoHeader.width;
    int height = infoHeader.height;
    Image image(width, height);

    int rowSize = ((width * 3 + 3) / 4) * 4;
    file.seekg(fileHeader.dataOffset);

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            unsigned char b, g, r;
            file.read(reinterpret_cast<char*>(&b), 1);
            file.read(reinterpret_cast<char*>(&g), 1);
            file.read(reinterpret_cast<char*>(&r), 1);
            Color color(r / 255.0, g / 255.0, b / 255.0);
            color.Clamp();
            image.SetPixel(x, y, color);
        }
        file.seekg(rowSize - width * 3, std::ios::cur);
    }
    return image;
}

void BMPProcessor::WriteBMP(Image& image, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    
    if (!file) {
        throw std::runtime_error("Cannot create file: " + filename);
    }

    int width = image.GetWidth();
    int height = image.GetHeight();

    BMPFileHeader fileHeader{};
    BMPInfoHeader infoHeader{};

    fileHeader.signature = 0x4D42;
    fileHeader.fileSize = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + width * height * 3;
    fileHeader.dataOffset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    infoHeader.headerSize = 40;
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPixel = 24;
    infoHeader.imageSize = width * height * 3;

    file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(BMPFileHeader));
    file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(BMPInfoHeader));

    int rowSize = ((width * 3 + 3) / 4) * 4;
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            Color color = image.GetPixel(x, y);
            unsigned char r = static_cast<unsigned char>(color.R * 255);
            unsigned char g = static_cast<unsigned char>(color.G * 255);
            unsigned char b = static_cast<unsigned char>(color.B * 255);
            file.write(reinterpret_cast<const char*>(&b), 1);
            file.write(reinterpret_cast<const char*>(&g), 1);
            file.write(reinterpret_cast<const char*>(&r), 1);
        }
        if (rowSize > width * 3) {
            std::string padding(rowSize - width * 3, '\0');
            file.write(padding.data(), padding.size());
        }
    }
}