#pragma once

#include <exception>
#include <string>

#include "processor.h"

namespace exceptions_const {
const size_t MAX_SIZE = 10;
}

bool IsCorrectInt(const std::string_view s);

bool IsCorrectDouble(const std::string_view s);

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const std::string& message) : message_(message) {
    }

    const char* what() const noexcept override {
        return message_.c_str();
    }

protected:
    std::string message_;
};

class ParserException : public ImageProcessorException {
public:
    explicit ParserException(const std::string& message)
        : ImageProcessorException("Parser exception with message: " + message + '\n') {
    }
};

class ReadImageException : public ImageProcessorException {
public:
    explicit ReadImageException(const std::string& message)
        : ImageProcessorException("Read image exception with message: " + message + '\n') {
    }
};

class WriteImageException : public ImageProcessorException {
public:
    explicit WriteImageException(const std::string& message)
        : ImageProcessorException("Read image exception with message: " + message + '\n') {
    }
};
