#ifndef STANDARD_HPP
#define STANDARD_HPP

#include <filesystem>
#include <string>

#include "color/color.hpp"
#include "serializer.hpp"

namespace tree {
    namespace serializers {
        class standard : public tree::serializer {
          public:
            void initially_open() override;
            void print(std::string* prefix, bool last, int depth,
                       std::filesystem::directory_entry path, std::string override_name) override;
            void close_entry(bool last, int depth) override;
            void print_statistics(bool directories_only, int dirs, int files) override;
            void finally_close() override;
            standard();
        };
    }  // namespace serializers

}  // namespace tree

#endif  // STANDARD_HPP
