#ifndef JSON_H
#define JSON_H

#include <filesystem>
#include <string>

#include "serializer.hpp"

namespace tree {
    namespace serializers {
        class json : public tree::serializer {
          public:
            void initially_open();
            void print(std::string* prefix, bool last, int depth,
                       std::filesystem::directory_entry path);
            void close_entry(bool last, int depth);
            void finally_close();
            json();
        };
    }  // namespace serializers

}  // namespace tree

#endif  // JSON_H
