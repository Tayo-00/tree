#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level, std::string* line) {
    while (level--) (*line) += tab;
}

void tree::serializers::json::initially_open() {
    std::cout << "[\n";
}

void tree::serializers::json::print(std::string* prefix, bool last, int depth,
                                    std::filesystem::directory_entry path,
                                    std::string override_name = "") {
    std::string line = *prefix;
    indent(depth + 1, &line);

    std::string name = "";

    if (path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        name = path.path().filename().string();
    } else {
        name = path.path().filename().string();
    }

    if (depth == 0) {
        name = override_name;
    }

    if (path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        line += "{\"type\": \"link\", \"name\": \"" + name + "\", \"target\": \"" +
                resolved.path().string() + "\", \"contents\": []}";

        if (!last) {
            line += ",";
        }
    } else {
        if (path.is_directory()) {
            line += "{\"type\": \"directory\", \"name\": \"" + name + "\", \"contents\": [";
        } else {
            line += "{\"type\": \"file\", \"name\": \"" + name + "\"}";

            if (!last) {
                line += ",";
            }
        }
    }

    std::cout << line << '\n';
}

void tree::serializers::json::close_entry(bool last, int depth) {
    std::string line = "";
    indent(depth + 1, &line);
    if (last == true && depth > 0) {
        line += "]}\n";
    } else {
        line += "]},\n";
    }

    std::cout << line;
}

void tree::serializers::json::print_statistics(bool directories_only, int dirs, int files) {
    std::string line = "";
    indent(1, &line);
    if (directories_only == true) {
        std::cout << line << "{\"type\": \"report\", \"directories\": " << dirs << "}\n";
    } else {
        std::cout << line << "{\"type\": \"report\", \"directories\": " << dirs
                  << ", \"files\": " << files << "}\n";
    }
}

void tree::serializers::json::finally_close() {
    std::cout << "]\n";
}

tree::serializers::json::json() {
    closure_required = true;
    initial_opening_required = true;
    final_closure_required = true;
}
