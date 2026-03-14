//
// Created by Terrarizer on 09/03/2026.
//

#ifndef SESSIONZERO_TOLOWER_H
#define SESSIONZERO_TOLOWER_H
#include <algorithm>
#include <string>

namespace zeroHelper {
    inline std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}

#endif //SESSIONZERO_TOLOWER_H