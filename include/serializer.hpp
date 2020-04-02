#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <filesystem>
#include <string>

namespace tree {
    class serializer {
      protected:
        bool initial_opening_required = false;
        bool closure_required = false;
        bool final_closure_required = false;

      public:
        bool requires_initial_opening() {
            return initial_opening_required;
        }
        bool requires_closure() {
            return closure_required;
        };
        bool requires_final_closure() {
            return final_closure_required;
        };
        virtual ~serializer() {
        }
        virtual void initially_open() = 0;
        virtual void print(std::string* prefix, bool last, int depth,
                           std::filesystem::directory_entry path) = 0;
        virtual void close_entry(bool last, int depth) = 0;
        virtual void print_statistics(bool directories_only, int dirs, int files) = 0;
        virtual void finally_close() = 0;
    };
}  // namespace tree

#endif  // SERIALIZER_HPP
