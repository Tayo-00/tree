#include <filesystem>
#include <iostream>
#include <string>

#include "node.hpp"

namespace fs = std::filesystem;

int main() {
    int dirs = 0;
    int files = 0;

    std::cout << "." << std::endl;

    tree::node(fs::directory_entry(fs::path("./")), &files, &dirs, 0);

    // Subtract 1 from dirs since we don't want to count the entrypoint
    std::cout << std::endl << dirs - 1 << " directories, " << files << " files" << std::endl;
}