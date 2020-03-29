#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <filesystem>
#include <string>

namespace tree {
    class serializer {
      public:
        virtual ~serializer() {
        }
        virtual void print(std::string* prefix, bool last, int depth,
                           std::filesystem::directory_entry path) = 0;
    };
}  // namespace tree

#endif  // SERIALIZER_HPP
