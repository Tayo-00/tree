#include "node.hpp"

#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

void tree::node::print() {
    auto name = tree::node::path.path().filename();

    int size = tree::node::depth * 3;

    for (int i = 0; i < size; i++) std::cout << ' ';

    std::cout << name.string() << std::endl;
}

tree::node::node(fs::directory_entry path, int* files, int* dirs, int depth) {
    tree::node::path = path;
    tree::node::depth = depth;

    tree::node::print();

    if (path.is_directory()) {
        for (const auto& entry : fs::directory_iterator(path)) {
            node(entry, files, dirs, depth + 1);
        }
        (*dirs)++;
    } else {
        (*files)++;
    }
}

tree::node::~node() {
}