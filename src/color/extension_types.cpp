#include "color/extension_types.hpp"

const std::vector<std::string> tree::extension_types::archive_or_compressed_types = {
    ".tar", ".tgz", ".arc",  ".arj", ".taz", ".lha", ".lz4",  ".lzh", ".lzma", ".tlz",
    ".txz", ".tzo", ".t7z",  ".zip", ".z",   ".dz",  ".gz",   ".lrz", ".lz",   ".lzo",
    ".xz",  ".zst", ".tzst", ".bz2", ".bz",  ".tbz", ".tbz2", ".tz",  ".deb",  ".rpm",
    ".jar", ".war", ".ear",  ".sar", ".rar", ".alz", ".ace",  ".zoo", ".cpio", ".7z",
    ".rz",  ".cab", ".wim",  ".swm", ".dwm", ".esd"};

const std::vector<std::string> tree::extension_types::image_types = {
    ".jpg", ".jpeg", ".mjpg", ".mjpeg", ".gif",  ".bmp",  ".pbm",  ".pgm", ".ppm", ".tga",
    ".xbm", ".xpm",  ".tif",  ".tiff",  ".png",  ".svg",  ".svgz", ".mng", ".pcx", ".mov",
    ".mpg", ".mpeg", ".m2v",  ".mkv",   ".webm", ".webp", ".ogm",  ".mp4", ".m4v", ".mp4v",
    ".vob", ".qt",   ".nuv",  ".wmv",   ".asf",  ".rm",   ".rmvb", ".flc", ".avi", ".fli",
    ".flv", ".gl",   ".dl",   ".xcf",   ".xwd",  ".yuv",  ".cgm",  ".emf", ".ogv", ".ogx"};

const std::vector<std::string> tree::extension_types::audio_types = {
    ".aac", ".au",  ".flac", ".m4a", ".mid", ".midi", ".mka", ".mp3",
    ".mpc", ".ogg", ".ra",   ".wav", ".oga", ".opus", ".spx", ".xspf"};

const std::unordered_map<std::string, tree::color::type> tree::extension_types::map = []() {
    std::unordered_map<std::string, tree::color::type> etm;

    for (auto type : tree::extension_types::archive_or_compressed_types)
        etm[type] = tree::color::type::archive_or_compressed;

    for (auto type : tree::extension_types::image_types) etm[type] = tree::color::type::image;

    for (auto type : tree::extension_types::audio_types) etm[type] = tree::color::type::audio;

    return etm;
}();