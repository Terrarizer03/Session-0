//
// Created by Terrarizer on 12/03/2026.
//

#ifndef DNDCREATOR_PROJECTDEFAULTS_H
#define DNDCREATOR_PROJECTDEFAULTS_H
#include <string>
#include <vector>
#include <chrono>
#include <format>
#include "../Loaders/EngineSettings.h"

namespace dndProjectDefaults {
    inline std::pmr::vector<std::string> defaultFolders = { "maps", "characters", "campaign_rules", "audio" };
    inline nlohmann::json createDefaultProjectJson(const std::string& name, const std::string& author) {
        nlohmann::json data;

        auto now = std::chrono::system_clock::now();
        auto today = std::chrono::year_month_day{std::chrono::floor<std::chrono::days>(now)};

        std::string dateStr = std::format("{}-{:02}-{:02}",
                                  static_cast<int>(today.year()),
                                  static_cast<unsigned>(today.month()),
                                  static_cast<unsigned>(today.day())
                              );

        data["name"] = name;
        data["metadata"]["version"] = EngineSettings::getInstance().version;
        data["metadata"]["author"] = author;
        data["metadata"]["timeCreated"] = dateStr;
        data["metadata"]["timeModified"] = dateStr;
        data["mapPaths"] = std::unordered_map<std::string, std::string>{};
        data["characterPaths"] = std::unordered_map<std::string, std::string>{};
        data["rules"] = std::unordered_map<std::string, std::string>{};

        return data;
    }
};

#endif //DNDCREATOR_PROJECTDEFAULTS_H