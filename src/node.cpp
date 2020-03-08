#include "node.hpp"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "sort.hpp"

namespace fs = std::filesystem;

void tree::node::print() {
    int size = tree::node::depth * 3;
    for (int i = 0; i < size; i++) std::cout << ' ';

    if (tree::node::path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        auto name = resolved.path().filename();

        std::cout << name.string() << " -> " << resolved.path().string() << std::endl;
    } else {
        auto name = tree::node::path.path().filename();

        std::cout << name.string() << std::endl;
    }
}

tree::node::node(fs::directory_entry path, int* files, int* dirs, int depth) {
    tree::node::path = path;
    tree::node::depth = depth;

    if (path.is_symlink()) {
        auto resolved = fs::directory_entry(fs::read_symlink(path));
        if (resolved.is_directory()) {
            (*dirs)++;
        } else {
            (*files)++;
        }

        tree::node::print();
    }

    if (!path.is_symlink()) {
        tree::node::print();

        if (path.is_directory()) {
            fs::directory_iterator iterator =
                fs::directory_iterator(path, fs::directory_options::skip_permission_denied);
            std::vector<fs::directory_entry> paths;

            for (const auto& entry : iterator) {
                paths.push_back(entry);
            }

            std::sort(paths.begin(), paths.end(), tree::sort::alphabetical);

            for (const auto& entry : paths) {
                node(entry, files, dirs, depth + 1);
            }
            (*dirs)++;
        } else {
            (*files)++;
        }
    }
}

tree::node::~node() {
}