#include "options.hpp"

#include <iostream>
#include <string>

bool tree::options::show_help = false;
bool tree::options::all_files = false;

void tree::options::parse(int argc, char* argv[]) {
    std::string arg1 = std::string(argv[1]);

    if (arg1.substr(0, 2) == "--" && arg1 == "--help") {
        tree::options::show_help = true;
    }

    if (arg1.substr(0, 2) != "--" && arg1.substr(0, 1) == "-") {
        if (arg1.find('a') != std::string::npos) {
            tree::options::all_files = true;
        }
    }
}