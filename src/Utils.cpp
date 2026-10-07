#include "Utils.h"
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstring>

namespace Utils {

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

bool caseInsensitiveFind(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return true;
    std::string h = toLower(haystack);
    std::string n = toLower(needle);
    return h.find(n) != std::string::npos;
}

std::string getCurrentDateTime() {
    std::time_t now = std::time(nullptr);
    std::tm ltm{};
#if defined(_WIN32)
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif
    char buffer[64];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &ltm);
    return std::string(buffer);
}

std::string getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm ltm{};
#if defined(_WIN32)
    localtime_s(&ltm, &now);
#else
    localtime_r(&now, &ltm);
#endif
    char buffer[32];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", &ltm);
    return std::string(buffer);
}

std::time_t parseDate(const std::string& dateStr) {
    std::tm tm{};
    std::memset(&tm, 0, sizeof(std::tm));

    // Try parsing "DD-MM-YYYY HH:MM:SS"
    int d = 0, m = 0, y = 0, hr = 0, min = 0, sec = 0;
    if (sscanf(dateStr.c_str(), "%d-%d-%d %d:%d:%d", &d, &m, &y, &hr, &min, &sec) == 6) {
        tm.tm_mday = d;
        tm.tm_mon = m - 1;
        tm.tm_year = y - 1900;
        tm.tm_hour = hr;
        tm.tm_min = min;
        tm.tm_sec = sec;
        return std::mktime(&tm);
    }
    // Try parsing "DD-MM-YYYY"
    if (sscanf(dateStr.c_str(), "%d-%d-%d", &d, &m, &y) >= 3) {
        tm.tm_mday = d;
        tm.tm_mon = m - 1;
        tm.tm_year = y - 1900;
        return std::mktime(&tm);
    }

    return 0;
}

} // namespace Utils
