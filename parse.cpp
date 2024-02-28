#include <iostream>

#include "exceptions.h"
#include "parse.h"

void PrintDocumentation() {
    std::cout << "\n\n===== Welcome to Image Processor =====\n\n";
    std::cout << "Start program writing:\n./image_processor { path to input .bmp file } { path to output .bmp file } [ "
                 "{ filter1 }, { filter2 }, ...]\n\n\n";
    std::cout << "\\\\\\ Filters and their arguments: ///\n";
    std::cout << "Blur: -blur { sigma (unsigned double)}\n";
    std::cout << "Crop: -crop { height (unsigned integer) } { width (unsigned integer) }\n";
    std::cout << "Crystallize: -cryst { number of figures (unsigned integer) }  -- Advice: put number between { height "
                 "* width / "
                 "10000 } and { height * width / 100 }\n";
    std::cout << "Edge: -edge { threshold (unsigned double) }\n";
    std::cout << "Grayscale: -gs\n";
    std::cout << "Negative: -neg\n";
    std::cout << "Sharpening: -sharp\n\n\n";
    std::cout << "Have fun using it =) \n\n\n";
}

ParserResults Parse(int argc, char** argv) {
    if (argc == 1) {
        PrintDocumentation();
        return {};
    }
    if (argc < 4) {
        PrintDocumentation();
        throw ParserException("Not enough arguments");
    }
    std::string input_path(argv[1]);
    std::string output_path(argv[2]);
    std::vector<FilterParams> filter_params;
    int i = 3;
    while (i < argc) {
        filter_params.push_back({});
        if (argv[i][0] != '-') {
            PrintDocumentation();
            throw ParserException("Incorrect input arguments");
        }
        filter_params.back().filter_name = std::string(argv[i]).substr(1, std::string(argv[i]).size() - 1);
        ++i;
        while (i < argc && argv[i][0] != '-') {
            filter_params.back().filter_arguments.emplace_back(argv[i]);
            ++i;
        }
    }
    return {input_path, output_path, filter_params};
}
