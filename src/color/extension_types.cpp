#include "color/extension_types.hpp"

const std::vector<std::string> tree::extension_types::archive_or_compressed_types = {
    ".tar", ".tgz", ".arj",  ".taz", ".lzh", ".tz2", ".zip", ".z",
    ".gz",  ".bz2", ".tbz2", ".tb2", ".tbz", ".deb", ".rpm", ".zoo",
};

const std::vector<std::string> tree::extension_types::image_types = {
    ".jpg", ".jpeg", ".gif",  ".bmp", ".ppm", ".tga", ".xbm", ".xpm", ".tif",
    ".mov", ".mpg",  ".mpeg", ".m2v", ".wmv", ".asf", ".rm",  ".avi",
};

const std::vector<std::string> tree::extension_types::audio_types = {
    ".flac", ".m2a", ".mp3", ".ogg", ".wav",
};

const std::unordered_map<std::string, tree::color::type> tree::extension_types::map = []() {
    std::unordered_map<std::string, tree::color::type> etm;

    for (auto type : tree::extension_types::archive_or_compressed_types)
        etm[type] = tree::color::type::archive_or_compressed;

    for (auto type : tree::extension_types::image_types) etm[type] = tree::color::type::image;

    for (auto type : tree::extension_types::audio_types) etm[type] = tree::color::type::audio;

    return etm;
}();