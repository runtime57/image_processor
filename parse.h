#pragma once

#include <compare>
#include <string>
#include <vector>

struct FilterParams {
    std::string filter_name;
    std::vector<std::string> filter_arguments;
};

struct ParserResults {
    std::string input_path;
    std::string output_path;
    std::vector<FilterParams> filter_params;
};

ParserResults Parse(int argc, char** argv);