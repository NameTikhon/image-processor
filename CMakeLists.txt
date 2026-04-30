cmake_minimum_required(VERSION 3.10)
project(image_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(image_processor
    main.cpp
    image/Color.cpp
    image/Image.cpp
    read_and_write/BMPProcessor.cpp
    filters/FilterBase.cpp
    filters/CropFilter.cpp
    filters/GrayscaleFilter.cpp
    filters/NegativeFilter.cpp
    filters/SharpeningFilter.cpp
    filters/EdgeDetectionFilter.cpp
    filters/GaussianBlurFilter.cpp
    filters/CrystallizeFilter.cpp
    pipeline/Pipeline.cpp
    parse/Parser.cpp
)

target_include_directories(image_processor PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)