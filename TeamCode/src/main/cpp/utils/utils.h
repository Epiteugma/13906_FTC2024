#pragma once
#include "string"

namespace utils {
    __printflike(1, 2)
    std::string sprintf(const char *format, ...) __overloadable;
}