#include "help.hpp"

#include <iostream>

void tree::help::print() {
    std::cout << "usage: tr++ [-adiJ] [-L level]" << std::endl;
    std::cout << "        [<directory list>]" << std::endl;

    std::cout << std::endl << "listing options:" << std::endl;
    std::cout << "  -a                       All files are listed" << std::endl;
    std::cout << "  -d                       List directories only" << std::endl;
    std::cout << "  -L level                 Only descend level of directories deep" << std::endl;

    std::cout << std::endl << "output options:" << std::endl;
    std::cout << "  -J                       Print output as JSON" << std::endl;

    std::cout << std::endl << "graphics options:" << std::endl;
    std::cout << "  -i                       Don't print indentation lines" << std::endl;

    std::cout << std::endl << "miscellaneous options:" << std::endl;
    std::cout << "  --help                   Print this help message" << std::endl;
}