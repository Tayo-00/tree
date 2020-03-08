#include <filesystem>
#include <iostream>
#include <string>

#include "node.hpp"

namespace fs = std::filesystem;

int main() {
    int dirs = 0;
    int files = 0;

    std::cout << "." << std::endl;

    for (const auto& entry : fs::directory_iterator("./")) {
        tree::node(entry, &files, &dirs, 1);
    }

    std::cout << std::endl << dirs << " directories, " << files << " files" << std::endl;
}