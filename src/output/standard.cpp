#include "serializers/standard.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void tree::serializers::standard::print(std::string* prefix, bool last, int depth,
                                        std::filesystem::directory_entry path) {
    std::string line = *prefix;

    if (depth > 0) {
        if (last) {
            (*prefix) += "    ";
        } else {
            (*prefix) += "│   ";
        }
    }

    if (last) {
        line += "└── ";
    } else {
        line += "├── ";
    }

    if (path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        auto name = resolved.path().filename();

        line += name.string() + " -> " + resolved.path().string();
    } else {
        auto name = path.path().filename();

        line += name.string();
    }

    std::cout << line << '\n';
}

void tree::serializers::standard::close_entry(bool last, int depth) {
}

tree::serializers::standard::standard() {
    closure_required = false;
}