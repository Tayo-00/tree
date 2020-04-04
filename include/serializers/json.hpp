#ifndef JSON_H
#define JSON_H

#include <filesystem>
#include <string>

#include "serializer.hpp"

namespace tree {
    namespace serializers {
        class json : public tree::serializer {
          public:
            void initially_open() override;
            void print(std::string* prefix, bool last, int depth,
                       std::filesystem::directory_entry path, std::string override_name) override;
            void close_entry(bool last, int depth) override;
            void print_statistics(bool directories_only, int dirs, int files) override;
            void finally_close() override;
            json();
        };
    }  // namespace serializers

}  // namespace tree

#endif  // JSON_H
