#include "serializers/standard.hpp"

#include <filesystem>
#include <iostream>

#include "options.hpp"

namespace fs = std::filesystem;

void tree::serializers::standard::initially_open() {
}

void tree::serializers::standard::print(std::string* prefix, bool last, int depth,
                                        std::filesystem::directory_entry path,
                                        std::string override_name = "") {
    if (depth == 0) {
        std::cout << override_name << '\n';
    } else {
        std::string line = *prefix;

        if (depth > 0) {
            if (last) {
                (*prefix) += "    ";
            } else {
                (*prefix) += "│   ";
            }
        }

        if (last) {
            line += "└── ";
        } else {
            line += "├── ";
        }

        if (path.is_symlink()) {
            auto resolved = fs::directory_entry(fs::read_symlink(path));
            if (tree::options::colorize == true) {
                line += colorize_entry(path) + " -> " + colorize_entry(resolved);
            } else {
                line +=
                    path.path().filename().string() + " -> " + resolved.path().filename().string();
            }

        } else {
            if (tree::options::colorize == true) {
                line += colorize_entry(path);
            } else {
                line += path.path().filename().string();
            }
        }

        std::cout << line << '\n';
    }
}

void tree::serializers::standard::close_entry(bool, int) {
}

void tree::serializers::standard::print_statistics(bool directories_only, int dirs, int files) {
    if (directories_only == true) {
        std::cout << '\n' << dirs << " directories\n";
    } else {
        std::cout << '\n' << dirs << " directories, " << files << " files\n";
    }
}

void tree::serializers::standard::finally_close() {
}

tree::serializers::standard::standard() {
    closure_required = false;
}
