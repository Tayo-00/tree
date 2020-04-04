#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level) {
    while (level--) std::cout << tab;
}

void tree::serializers::json::initially_open() {
    std::cout << "[\n";
}

void tree::serializers::json::print(std::string* prefix, bool last, int depth,
                                    std::filesystem::directory_entry path,
                                    std::string override_name = "") {
    std::string line = *prefix;
    indent(depth + 1);

    std::string name = path.path().filename();

    if (depth == 0) {
        name = override_name;
    }

    if (path.is_directory()) {
        std::cout << "{\"type\":\"directory\", \"name\": \"" << name << "\", \"contents\": [";
    } else {
        std::cout << "{\"type\":\"file\", \"name\": \"" << name << "\"}";

        if (!last) {
            std::cout << ",";
        }
    }

    std::cout << line << '\n';
}

void tree::serializers::json::close_entry(bool last, int depth) {
    indent(depth + 1);
    if (last == true && depth > 0) {
        std::cout << "]}";
    } else {
        std::cout << "]},";
    }

    std::cout << '\n';
}

void tree::serializers::json::print_statistics(bool directories_only, int dirs, int files) {
    indent(1);
    std::cout << "{\"type\": \"report\", \"directories\": " << dirs;
    if (!directories_only == true) {
        std::cout << ", \"files\": " << files;
    }
    std::cout << "}\n";
}

void tree::serializers::json::finally_close() {
    std::cout << "]\n";
}

tree::serializers::json::json() {
    closure_required = true;
    initial_opening_required = true;
    final_closure_required = true;
}
