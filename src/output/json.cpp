#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level) {
    while (level--) std::cout << tab;
}

void tree::serializers::json::initially_open() {
    std::cout << "{\n";
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
    if (depth == 0) return;

    indent(depth);
    if (last == true) {
        std::cout << "]}";
    } else {
        std::cout << "]},";
    }

    std::cout << '\n';
}

void tree::serializers::json::print_statistics(bool directories_only, int dirs, int files) {
    indent(1);
    std::cout << ", {\"type\":\"report\", \"directories\": " << dirs;
    if (!directories_only == true) {
        std::cout << ", \"files\": " << files << "}\n";
    }
}

void tree::serializers::json::finally_close() {
    std::cout << "}\n";
}

tree::serializers::json::json() {
    closure_required = true;
    initial_opening_required = true;
    final_closure_required = true;
}
