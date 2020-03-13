#ifndef OPTIONS_HPP
#define OPTIONS_HPP

namespace tree {
    class options {
      public:
        static void parse(int argc, char* argv[]);
        static bool all_files;
        static bool show_help;
    };
}  // namespace tree

#endif  // OPTIONS_HPP
