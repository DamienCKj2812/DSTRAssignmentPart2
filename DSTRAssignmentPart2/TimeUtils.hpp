
#ifndef TIME_UTILS_HPP
#define TIME_UTILS_HPP

#include <string>
#include <ctime>

inline std::string getCurrentTimeString() {
    time_t now = time(0);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now);  
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return std::string(buffer);
}

#endif
