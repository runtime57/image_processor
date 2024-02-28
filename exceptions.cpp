#include "exceptions.h"

bool IsCorrectDouble(const std::string_view s) {
    if (s.empty() || s.size() > exceptions_const::MAX_SIZE) {
        return false;
    }
    auto dot_position = s.find('.');
    if (dot_position == std::string::npos) {
        return IsCorrectInt(s);
    }
    std::string_view integer = s.substr(0, dot_position);
    std::string_view fractional = s.substr(dot_position + 1, s.size() - dot_position - 1);
    return IsCorrectInt(integer) + IsCorrectInt(fractional);
}

bool IsCorrectInt(const std::string_view s) {
    if (s.empty() || s.size() > exceptions_const::MAX_SIZE) {
        return false;
    }
    for (size_t i = 0; i < s.size(); ++i) {
        if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}