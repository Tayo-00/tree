#ifndef SORT_HPP
#define SORT_HPP

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

namespace tree {
    class sort {
      public:
        static bool alphabetical(const fs::directory_entry& a, const fs::directory_entry& b);
    };
}  // namespace tree

#endif  // SORT_HPP
