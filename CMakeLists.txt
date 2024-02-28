cmake_minimum_required(VERSION 3.21)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(image_processor
        filters/base.cpp
        filters/base.h
        filters/crop.cpp
        filters/crop.h
        filters/edge.cpp
        filters/edge.h
        filters/grayscale.cpp
        filters/grayscale.h
        filters/negative.cpp
        filters/negative.h
        filters/sharpening.cpp
        filters/sharpening.h
        filters/blur.h
        filters/blur.cpp
        filters/crystallize.h
        filters/crystallize.cpp
        exceptions.cpp
        exceptions.h
        image.cpp
        image.h
        main.cpp
        parse.cpp
        parse.h
        processor.cpp
        processor.h
        # test_script/test.cpp
        )

# add_catch(test_processor test_script/test.cpp filters/base.cpp
# filters/base.h
# filters/crop.cpp
# filters/crop.h
# filters/edge.cpp
# filters/edge.h
# filters/grayscale.cpp
# filters/grayscale.h
# filters/negative.cpp
# # filters/negative.h
# filters/sharpening.cpp
# filters/sharpening.h
# filters/blur.h
# filters/blur.cpp
# filters/crystallize.h
# filters/crystallize.cpp
# exceptions.cpp
# exceptions.h
# image.cpp
# image.h
# #main.cpp
# parse.cpp
# parse.h
# processor.cpp
# processor.h)

target_include_directories(image_processor PUBLIC .)