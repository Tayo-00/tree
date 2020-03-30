#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level) {
    while (level--) std::cout << tab;
}

void tree::serializers::json::print(std::string* prefix, bool last, int depth,
                                    std::filesystem::directory_entry path) {
    std::string line = *prefix;
    indent(depth);

    if (path.is_directory()) {
        std::cout << "{\"type\":\"directory\", \"name\": " << path.path().stem()
                  << ", \"contents\": [";

    } else {
        std::cout << "{\"type\":\"file\", \"name\": " << path.path().filename() << "}";

        if (!last) {
            std::cout << ",";
        }
    }

    std::cout << line << '\n';
}

void tree::serializers::json::close_entry(bool last, int depth) {
    indent(depth);
    if (last == true) {
        std::cout << "]}";
    } else {
        std::cout << "]},";
    }

    std::cout << '\n';
}

tree::serializers::json::json() {
    closure_required = true;
}