#ifndef JSON_H
#define JSON_H

#include <filesystem>
#include <string>

#include "serializer.hpp"

namespace tree {
    namespace serializers {
        class json : public tree::serializer {
          public:
            void print(std::string* prefix, bool last, int depth,
                       std::filesystem::directory_entry path);
        };
    }  // namespace serializers

}  // namespace tree

#endif // JSON_H
