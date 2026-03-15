//
// Created by Terrarizer on 15/03/2026.
//

#ifndef SESSIONZERO_GETCURRENTTIME_H
#define SESSIONZERO_GETCURRENTTIME_H
#include <chrono>
#include <string>
#include <format>

namespace zeroHelper {
    static std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto today = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(now)};

        std::string dateStr = std::format("{}-{:02}-{:02}",
                                  static_cast<int>(today.year()),
                                  static_cast<unsigned>(today.month()),
                                  static_cast<unsigned>(today.day())
                              );
        return dateStr;
    }
}

#endif //SESSIONZERO_GETCURRENTTIME_H