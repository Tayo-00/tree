#include "help.hpp"

#include <iostream>

void tree::help::print() {
    std::cout << "usage: tr++ [-adJ]" << std::endl;
    std::cout << "        [<directory list>]" << std::endl;

    std::cout << std::endl << "listing options:" << std::endl;
    std::cout << "  -a                       All files are listed" << std::endl;
    std::cout << "  -d                       List directories only" << std::endl;
    std::cout << "  -J                       Print output as JSON" << std::endl;

    std::cout << std::endl << "miscellaneous options:" << std::endl;
    std::cout << "  --help                   Print this help message" << std::endl;
}