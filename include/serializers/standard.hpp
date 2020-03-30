#ifndef STANDARD_HPP
#define STANDARD_HPP

#include <filesystem>
#include <string>

#include "serializer.hpp"

namespace tree {
    namespace serializers {
        class standard : public tree::serializer {
          public:
            void print(std::string* prefix, bool last, int depth,
                       std::filesystem::directory_entry path);
            void close_entry(bool last, int depth);
            standard();
        };
    }  // namespace serializers

}  // namespace tree

#endif  // STANDARD_HPP
