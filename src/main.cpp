#include <filesystem>
#include <iostream>
#include <string>
namespace fs = std::filesystem;

int main() {
    int dirs = 0;
    int files = 0;

    for (const auto& entry : fs::directory_iterator("./")) {
        if (entry.is_directory()) {
            dirs++;
        } else {
            files++;
        }

        auto name = entry.path().filename();

        std::cout << name.string() << std::endl;
    }

    std::cout << std::endl << dirs << " directories, " << files << " files" << std::endl;
}