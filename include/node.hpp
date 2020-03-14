#ifndef NODE_HPP
#define NODE_HPP

#include <filesystem>
#include <string>

namespace tree {
    class node {
      private:
        int depth;

      public:
        std::filesystem::directory_entry path;
        void print(std::string prefix, bool last);
        explicit node(std::filesystem::directory_entry path, int* files, int* dirs, int depth,
                      std::string prefix, bool last, bool entry);
        ~node();
    };
}  // namespace tree

#endif  // NODE_HPP
