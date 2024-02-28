#include "processor.h"

std::shared_ptr<BaseFilter> CreateFilter(const FilterParams& filter_params) {
    if (filter_params.filter_name == "sharp") {
        if (!filter_params.filter_arguments.empty()) {
            throw ParserException("Incorrect number of arguments for Sharpening");
        }
        return std::make_shared<Sharpening>();
    }
    if (filter_params.filter_name == "neg") {
        if (!filter_params.filter_arguments.empty()) {
            throw ParserException("Incorrect number of arguments for Negative");
        }
        return std::make_shared<Negative>();
    }
    if (filter_params.filter_name == "gs") {
        if (!filter_params.filter_arguments.empty()) {
            throw ParserException("Incorrect number of arguments for Grayscale");
        }
        return std::make_shared<Grayscale>();
    }
    if (filter_params.filter_name == "crop") {
        if (filter_params.filter_arguments.size() != 2) {
            throw ParserException("Incorrect number of arguments for Crop");
        }
        if (!IsCorrectInt(filter_params.filter_arguments[0]) or !IsCorrectInt(filter_params.filter_arguments[1])) {
            throw ParserException("Incorrect type of arguments for Crop");
        }
        return std::make_shared<Crop>(static_cast<size_t>(std::stoi(filter_params.filter_arguments[0])),
                                      static_cast<size_t>(std::stoi(filter_params.filter_arguments[1])));
    }
    if (filter_params.filter_name == "edge") {
        if (filter_params.filter_arguments.size() != 1) {
            throw ParserException("Incorrect number of arguments for Edge");
        }
        if (!IsCorrectDouble(filter_params.filter_arguments[0])) {
            throw ParserException("Incorrect type of argument for Edge");
        }
        return std::make_shared<Edge>(std::stod(filter_params.filter_arguments[0]));
    }
    if (filter_params.filter_name == "blur") {
        if (filter_params.filter_arguments.size() != 1) {
            throw ParserException("Incorrect number of arguments for Blur");
        }
        if (!IsCorrectDouble(filter_params.filter_arguments[0])) {
            throw ParserException("Incorrect argument for Blur");
        }
        return std::make_shared<Blur>(std::stod(filter_params.filter_arguments[0]));
    }
    if (filter_params.filter_name == "cryst") {
        if (filter_params.filter_arguments.size() != 1) {
            throw ParserException("Incorrect number of arguments for Crystallize");
        }

        if (!IsCorrectInt(filter_params.filter_arguments[0])) {
            throw ParserException("Incorrect argument for Crystallize");
        }
        return std::make_shared<Crystallize>(static_cast<size_t>(std::stoi(filter_params.filter_arguments[0])));
    }
    throw ParserException("Incorrect name for filter -- " + filter_params.filter_name);
}

std::vector<std::shared_ptr<BaseFilter>> CreateFilters(const std::vector<FilterParams>& filter_params) {
    std::vector<std::shared_ptr<BaseFilter>> result(filter_params.size());
    for (size_t i = 0; i < filter_params.size(); ++i) {
        result[i] = CreateFilter(filter_params[i]);
    }
    return result;
}

void ApplyFilters(const std::vector<std::shared_ptr<BaseFilter>>& filters, Image& image) {
    for (const auto& filter : filters) {
        filter->Apply(image);
    }
}