#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
#include <algorithm>

namespace Utils {
    // String manipulation
    std::string trim(const std::string& str);
    std::string toLower(const std::string& str);
    bool caseInsensitiveFind(const std::string& haystack, const std::string& needle);

    // Date & Time helpers
    std::string getCurrentDateTime();
    std::string getCurrentDate();
    std::time_t parseDate(const std::string& dateStr);

    // Terminal colors
    namespace Colors {
        const std::string RESET       = "\033[0m";
        const std::string BOLD        = "\033[1m";
        const std::string DIM         = "\033[2m";
        const std::string RED         = "\033[31m";
        const std::string GREEN       = "\033[32m";
        const std::string YELLOW      = "\033[33m";
        const std::string BLUE        = "\033[34m";
        const std::string MAGENTA     = "\033[35m";
        const std::string CYAN        = "\033[36m";
        const std::string WHITE       = "\033[37m";
        const std::string BRIGHT_CYAN = "\033[96m";
        const std::string BRIGHT_GREEN= "\033[92m";
        const std::string BRIGHT_YELLOW="\033[93m";
    }
}

#endif // UTILS_H
