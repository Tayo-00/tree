#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level)
{
    while (level--)
        std::cout << tab;
}

void tree::serializers::json::print(std::string* prefix, bool last, int depth,
                                        std::filesystem::directory_entry path) {
    std::string line = *prefix;
    indent(depth);

    if (path.is_directory()) {
        std::cout << "{\"type\":\"directory\", \"name\": " << path.path().stem()
                  << ", \"contents\": [";

        if (std::filesystem::is_empty(path)) {
            std::cout << '\n';
            indent(depth);
            std::cout << "]}";
        }

    } else {
        std::cout << "{\"type\":\"file\", \"name\": "
                  << path.path().filename() << "}";

        if (! last) {
            std::cout << ",";
        } else {
            std::cout << '\n';
            indent(depth-1);
            std::cout << "]}";
        }
    }

    std::cout << line << '\n';
}
