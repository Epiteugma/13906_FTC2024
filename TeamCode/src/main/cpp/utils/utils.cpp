#include "utils.h"

std::string utils::sprintf(const char *format, ...) __overloadable {
    va_list args;

    va_start(args, format);
    int len = vsnprintf(nullptr, 0, format, args);
    va_end(args);

    va_start(args, format);
    char* buf = (char*) malloc(len + 1);
    vsnprintf(buf, len + 1, format, args);
    va_end(args);

    std::string out(buf);
    free(buf);

    return out;
}