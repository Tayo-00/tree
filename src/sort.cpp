#include "sort.hpp"

#include <cstring>
namespace fs = std::filesystem;

bool tree::sort::alphabetical(const fs::directory_entry& a, const fs::directory_entry& b) {
    auto one = (a.path().filename()).generic_string();
    auto two = (b.path().filename()).generic_string();

    return (strcoll(one.c_str(), two.c_str()) < 0);
}