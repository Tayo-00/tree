#include "help.hpp"

#include <iostream>

void tree::help::print() {
    std::cout << "usage: tr++ [-a]" << std::endl;
    std::cout << "        [<directory list>]" << std::endl << std::endl;

    std::cout << "listing options:" << std::endl;
    std::cout << "  -a                       All files are listed" << std::endl;
    std::cout << "  -d                       List directories only" << std::endl;
}