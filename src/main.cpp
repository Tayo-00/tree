#include <filesystem>
#include <iostream>
#include <string>

#include "help.hpp"
#include "node.hpp"
#include "options.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int dirs = 0;
    int files = 0;

    if (argc > 1) {
        tree::options::parse(argc, argv);
    }

    if (tree::options::show_help == true) {
        tree::help::print();
        exit(0);
    }

    for (size_t i = 0; i < tree::options::directories.size(); i++) {
        auto directory = fs::directory_entry(fs::path(tree::options::directories[i]));
        auto dir_str = directory.path().generic_string();
        if (dir_str == ".") {
            directory = fs::directory_entry(fs::path("./"));
        }

        std::cout << dir_str << '\n';
        tree::node(directory, &files, &dirs, 0, "", true, true);
    }

    // Subtract 1 from dirs since we don't want to count the entrypoint
    if (tree::options::directories_only == true) {
        std::cout << '\n' << dirs << " directories\n";
    } else {
        std::cout << '\n' << dirs << " directories, " << files << " files\n";
    }
}