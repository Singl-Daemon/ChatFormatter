#pragma once

#include <ll/api/Config.h>

#include <unordered_map>

struct Config {
    int version = 2;

    struct chatLogger {
        bool        Enabled   = false;
        bool        LogToFile = false;
        std::string FilePath  = "./logs/chat.log";
    } ChatLogger;

    std::string ChatFormat = "[%chatformatter_dimension%] {player} >> {message}";

    std::unordered_map<std::string, std::string> DimensionNameMap = {
        {"overworld", "Overworld"},
        {"nether",    "Nether"   },
        {"the_end",   "The End"  }
    };
};