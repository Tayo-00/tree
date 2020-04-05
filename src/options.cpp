#include "options.hpp"

#include <iostream>
#include <string>

#include "serializers/json.hpp"
#include "serializers/standard.hpp"

bool tree::options::show_help = false;
bool tree::options::all_files = false;
bool tree::options::directories_only = false;
int tree::options::max_depth = -1;
std::vector<std::string> tree::options::directories = {"."};
tree::serializer* tree::options::selected_serializer = new tree::serializers::standard();

void tree::options::parse(int argc, char* argv[]) {
    std::string arg1 = argv[1];

    int i = 1;

    if (arg1.substr(0, 2) == "--" && arg1 == "--help") {
        tree::options::show_help = true;
        i++;
    }

    if (arg1.substr(0, 2) != "--" && arg1.substr(0, 1) == "-") {
        if (arg1.find('a') != std::string::npos) {
            tree::options::all_files = true;
            i++;
        }

        if (arg1.find('d') != std::string::npos) {
            tree::options::directories_only = true;
            i++;
        }

        if (arg1.find('J') != std::string::npos) {
            tree::options::selected_serializer = new tree::serializers::json();
            i++;
        }
    }

    while (i < argc) {
        std::string arg2 = argv[i];

        if (arg2.substr(0, 2) == "--") {
        }

        if (arg2.substr(0, 2) != "--" && arg2.substr(0, 1) == "-") {
            if (arg2.find('L') != std::string::npos) {
                i++;
                std::string parameter = argv[i];
                tree::options::max_depth = std::stoi(parameter);
            }
        }

        if (arg2.substr(0, 2) != "--" && arg2.substr(0, 1) != "-") {
            break;
        }

        i++;
    }

    if (i < argc) {
        tree::options::directories = {};
    }

    while (i < argc) {
        tree::options::directories.push_back(argv[i]);

        i++;
    }
}
