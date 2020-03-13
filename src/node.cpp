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
    if (last) {
        std::cout << prefix << "└── ";
    } else {
        std::cout << prefix << "├── ";
    }

    if (tree::node::path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        auto name = resolved.path().filename();

        std::cout << name.string() << " -> " << resolved.path().string() << std::endl;
    } else {
        auto name = tree::node::path.path().filename();

        std::cout << name.string() << std::endl;
    }
}

tree::node::node(fs::directory_entry path, int* files, int* dirs, int depth, std::string prefix,
                 bool last) {
    tree::node::path = path;
    tree::node::depth = depth;

    if (tree::options::all_files == true || (path.path().filename()).generic_string()[0] != '.') {
        if (path.is_symlink()) {
            auto resolved = fs::directory_entry(fs::read_symlink(path));
            if (resolved.is_directory()) {
                (*dirs)++;
            } else {
                (*files)++;
            }

            if (depth > 0) {
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
                    paths.push_back(entry);
                }

                std::sort(paths.begin(), paths.end(), tree::sort::alphabetical);

                for (size_t i = 0; i < paths.size(); i++) {
                    if (depth > 0) {
                        if (last && i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "    ", true);
                        } else if (last) {
                            node(paths[i], files, dirs, depth + 1, prefix + "    ", false);
                        } else if (i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "│   ", true);
                        } else {
                            node(paths[i], files, dirs, depth + 1, prefix + "│   ", false);
                        }
                    } else {
                        if (i == paths.size() - 1) {
                            node(paths[i], files, dirs, depth + 1, prefix + "", true);
                        } else {
                            node(paths[i], files, dirs, depth + 1, prefix + "", false);
                        }
                    }
                }
                (*dirs)++;
            } else {
                if (tree::options::directories_only != true && depth > 0) {
                    tree::node::print(prefix, last);
                }
                (*files)++;
            }
        }
    }
}

tree::node::~node() {
}