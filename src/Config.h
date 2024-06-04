#pragma once
#include <iostream>
#include <unordered_map>

struct Config {
    int version = 1;

    std::string ChatFormat = "[%chatformatter_dimension%] {player} >> {message}";

    std::unordered_map<std::string, std::string> DimensionNameMap = {
        {"overworld", "Overworld"},
        {"nether",    "Nether"   },
        {"the_end",   "The End"  }
    };
};