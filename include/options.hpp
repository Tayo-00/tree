#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include <vector>

namespace tree {
    class options {
      public:
        static void parse(int argc, char* argv[]);
        static bool all_files;
        static bool directories_only;
        static bool show_help;
        static std::vector<std::string> directories;
    };
}  // namespace tree

#endif  // OPTIONS_HPP
