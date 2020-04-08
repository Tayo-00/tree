#include "color.hpp"

const std::string colorize_string(std::string string, const col::ColorType ct) {
    return col::get_format_sequences(ct) + string +
           col::get_format_sequences(col::ColorType::Normal);
}

inline bool is_of_type(std::filesystem::directory_entry& path,
                       const std::vector<std::string>& type) {
    return std::find(type.begin(), type.end(), path.path().extension()) != type.end();
}

const std::string colorize_entry(std::filesystem::directory_entry path) {
    using namespace col;
    std::string name = path.path().filename().string();

    if (path.is_directory()) {
        return colorize_string(name, ColorType::Directory);
    }

    if (path.is_symlink()) {
        return colorize_string(name, ColorType::SymbolicLink);
    }

    if (path.is_fifo()) {
        return colorize_string(name, ColorType::Fifo);
    }

    if (path.is_socket()) {
        return colorize_string(name, ColorType::Socket);
    }

    if (path.is_block_file()) {
        return colorize_string(name, ColorType::BlockDeviceDriver);
    }

    if (path.is_character_file()) {
        return colorize_string(name, ColorType::CharacterDeviceDriver);
    }

    try {
        return colorize_string(name, ExtensionTypeMap.at(path.path().extension().string()));
    } catch (const std::out_of_range& ex) {
        return path.path().filename().string();
    }
}
