#include "help.hpp"

#include <iostream>

void tree::help::print() {
    std::cout << "usage: tr++ [-a]" << std::endl;
    std::cout << "        [<directory list>]" << std::endl;
}