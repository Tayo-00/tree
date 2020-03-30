#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <filesystem>
#include <string>

namespace tree {
    class serializer {
      protected:
        bool closure_required;

      public:
        bool requires_closure() {
            return closure_required;
        };
        virtual ~serializer() {
        }
        virtual void print(std::string* prefix, bool last, int depth,
                           std::filesystem::directory_entry path) = 0;
        virtual void close_entry(bool last, int depth) = 0;
    };
}  // namespace tree

#endif  // SERIALIZER_HPP
