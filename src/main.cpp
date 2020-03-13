#include <filesystem>
#include <iostream>
#include <string>

#include "help.hpp"
#include "node.hpp"
#include "options.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    int dirs = 0;
    int files = 0;

    if (argc > 1) {
        tree::options::parse(argc, argv);
    }

    if (tree::options::show_help == true) {
        tree::help::print();
        exit(0);
    }

    std::cout << "." << std::endl;

    tree::node(fs::directory_entry(fs::path("./")), &files, &dirs, 0, "", true);

    // Subtract 1 from dirs since we don't want to count the entrypoint
    std::cout << std::endl << dirs - 1 << " directories, " << files << " files" << std::endl;
}