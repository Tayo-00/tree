#ifndef EXTENSION_TYPES_HPP
#define EXTENSION_TYPES_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "color/color.hpp"

namespace tree {
    class extension_types {
      private:
        static const std::vector<std::string> archive_or_compressed_types;
        static const std::vector<std::string> image_types;
        static const std::vector<std::string> audio_types;

      public:
        static const std::unordered_map<std::string, tree::color::type> map;
    };

}  // namespace tree

#endif  // EXTENSION_TYPES_HPP
