#include "node.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "options.hpp"
#include "sort.hpp"

namespace fs = std::filesystem;

void tree::node::print(std::string prefix, bool last) {
    std::string line = prefix;

    if (last) {
        line += "└── ";
    } else {
        line += "├── ";
    }

    if (tree::node::path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        auto name = resolved.path().filename();

        line += name.string() + " -> " + resolved.path().string();
    } else {
        auto name = tree::node::path.path().filename();

        line += name.string();
    }

    std::cout << line << '\n';
}

tree::node::node(fs::directory_entry path, int* files, int* dirs, int depth, std::string prefix,
                 bool last, bool entry) {
    tree::node::path = path;
    tree::node::depth = depth;

    if (tree::options::all_files == true || (path.path().filename()).generic_string()[0] != '.') {
        if (tree::options::directories_only == false && path.is_symlink()) {
            auto resolved = fs::directory_entry(fs::read_symlink(path));
            if (entry == false) {
                if (resolved.is_directory()) {
                    (*dirs)++;
                } else {
                    (*files)++;
                }

                tree::node::print(prefix, last);
            }
        }

        if (!path.is_symlink()) {
            if (path.is_directory()) {
                if (depth > 0) {
                    tree::node::print(prefix, last);
                }

                fs::directory_iterator iterator =
                    fs::directory_iterator(path, fs::directory_options::skip_permission_denied);
                std::vector<fs::directory_entry> paths;

                for (const auto& entry : iterator) {
                    if (tree::options::directories_only == true) {
                        if (!entry.is_symlink() && entry.is_directory()) {
                            paths.push_back(entry);
                        }
                    } else {
                        paths.push_back(entry);
                    }
                }

                std::sort(paths.begin(), paths.end(), tree::sort::alphabetical);

                for (size_t i = 0; i < paths.size(); i++) {
                    if (depth > 0) {
                        if (last && i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "    ", true, false);
                        } else if (last) {
                            node(paths[i], files, dirs, depth + 1, prefix + "    ", false, false);
                        } else if (i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "│   ", true, false);
                        } else {
                            node(paths[i], files, dirs, depth + 1, prefix + "│   ", false, false);
                        }
                    } else {
                        if (i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "", true, false);
                        } else {
                            node(paths[i], files, dirs, depth + 1, prefix + "", false, false);
                        }
                    }
                }
                if (entry == false) (*dirs)++;
            } else {
                if (tree::options::directories_only != true && depth > 0) {
                    tree::node::print(prefix, last);
                }
                if (entry == false) (*files)++;
            }
        }
    }
}

tree::node::~node() {
}