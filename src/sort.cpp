#include "sort.hpp"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

bool tree::sort::alphabetical(const fs::directory_entry& a, const fs::directory_entry& b) {
    auto one = (a.path().filename()).generic_string();
    auto two = (b.path().filename()).generic_string();

    // TODO: Reduces performance by ~10-15%
    std::transform(one.begin(), one.end(), one.begin(), ::toupper);
    std::transform(two.begin(), two.end(), two.begin(), ::toupper);

    return (strcoll(one.c_str(), two.c_str()) < 0);
}