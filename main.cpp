#include <iostream>

#include "exceptions.h"
#include "image.h"
#include "parse.h"
#include "processor.h"

int main(int argc, char** argv) {
    try {
        auto parser_results = Parse(argc, argv);
        if (parser_results.filter_params.empty()) {
            return 0;
        }
        auto image = ReadImage(parser_results.input_path);
        auto filters = CreateFilters(parser_results.filter_params);
        ApplyFilters(filters, image);
        WriteImage(parser_results.output_path, image);
        return 0;
    } catch (ImageProcessorException& exc) {
        std::cerr << exc.what();
        return 1;
    }
}
