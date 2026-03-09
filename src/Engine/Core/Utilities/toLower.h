//
// Created by Terrarizer on 09/03/2026.
//

#ifndef DNDCREATOR_TOLOWER_H
#define DNDCREATOR_TOLOWER_H
#include <algorithm>
#include <string>

namespace dndHelper {
    inline std::string toLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}

#endif //DNDCREATOR_TOLOWER_H