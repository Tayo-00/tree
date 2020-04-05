#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <string>
#include <vector>

#include "serializer.hpp"

namespace tree {
    class options {
      public:
        static void parse(int argc, char* argv[]);
        static bool all_files;
        static bool directories_only;
        static bool show_help;
        static bool no_indent;
        static int max_depth;
        static std::vector<std::string> directories;
        static tree::serializer* selected_serializer;
    };
}  // namespace tree

#endif  // OPTIONS_HPP
