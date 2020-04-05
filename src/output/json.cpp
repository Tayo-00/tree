#include "serializers/json.hpp"

#include <filesystem>
#include <iostream>

#include "options.hpp"

namespace fs = std::filesystem;
const std::string tab = "  ";

inline void indent(int level, std::string* line) {
    while (level--) (*line) += tab;
}

void tree::serializers::json::initially_open() {
    if (tree::options::no_indent != true) {
        std::cout << "[\n";
    } else {
        std::cout << "[";
    }
}

void tree::serializers::json::print(std::string* prefix, bool last, int depth,
                                    std::filesystem::directory_entry path,
                                    std::string override_name = "") {
    std::string line = *prefix;

    if (tree::options::no_indent != true) {
        indent(depth + 1, &line);
    }

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

    if (tree::options::no_indent != true) {
        std::cout << line << "\n";
    } else {
        std::cout << line;
    }
}

void tree::serializers::json::close_entry(bool last, int depth) {
    std::string line = "";

    if (tree::options::no_indent != true) {
        indent(depth + 1, &line);
    }

    if (last == true && depth > 0) {
        line += "]}";
    } else {
        line += "]},";
    }

    if (tree::options::no_indent != true) {
        std::cout << line << "\n";
    } else {
        std::cout << line;
    }
}

void tree::serializers::json::print_statistics(bool directories_only, int dirs, int files) {
    std::string line = "";

    if (tree::options::no_indent != true) {
        indent(1, &line);
    }

    if (directories_only == true) {
        line += "{\"type\": \"report\", \"directories\": ";
        line += std::to_string(dirs);
        line += "}";
    } else {
        line += "{\"type\": \"report\", \"directories\": ";
        line += std::to_string(dirs);
        line += ", \"files\": ";
        line += std::to_string(files);
        line += "}";
    }

    if (tree::options::no_indent != true) {
        std::cout << line << "\n";
    } else {
        std::cout << line;
    }
}

void tree::serializers::json::finally_close() {
    if (tree::options::no_indent != true) {
        std::cout << "]\n";
    } else {
        std::cout << "]";
    }
}

tree::serializers::json::json() {
    closure_required = true;
    initial_opening_required = true;
    final_closure_required = true;
}
