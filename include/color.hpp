#pragma once

#include <algorithm>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace col {
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    // http://jlk.fjfi.cvut.cz/arch/manpages/man/core/man-pages/console_codes.4.en

    const unsigned int SGT_BLOCK = 0x0000FF;
    const unsigned int FG_BLOCK = 0x00FF00;
    const unsigned int BG_BLOCK = 0xFF0000;

    enum SGT : const unsigned int {
        NormalReset = 1 << 0,
        Bold = 1 << 1,
        Faint = 1 << 2,  // FIXME: if both fg and bg color set, will dim both
        Italic = 1 << 3,
        Underline = 1 << 4,
        Blink = 1 << 5
    };

    enum ColorCode : const unsigned int {
        Black = 30 << 8,
        Red = 31 << 8,
        Green = 32 << 8,
        Yellow = 33 << 8,
        Blue = 34 << 8,
        Magenta = 35 << 8,
        Cyan = 36 << 8,
        White = 37 << 8
    };

    inline constexpr unsigned int bright(const ColorCode c) {
        return c + (60 << 8);
    }
    inline constexpr unsigned int background(const unsigned int c) {
        return (c + (10 << 8)) << 8;
    }

    enum ColorType : const unsigned int {
        Normal = NormalReset,
        Directory = Blue | Bold,
        SymbolicLink = Cyan | Bold,
        MultiHardLink = Normal,             // regular file with more than one link
        Fifo = Yellow | background(Black),  // pipe
        Socket = Magenta | Bold,
        Door = Socket,
        BlockDeviceDriver = Yellow | background(Black) | Bold,
        CharacterDeviceDriver = Yellow | background(Black) | Bold,
        Orphan = Red | background(Black) |
                 Bold,     // symlink to nonexistent file, or non-stat'able file ...
        Missing = Normal,  // ... and the files they point to
        FileSetuid = White | background(Red),             // file: with setuid (u+s)
        FileSetgid = Black | background(Yellow),          // file: with setgid (g+s)
        FileCapability = Black | background(Red),         // file: with capability
        StickyOtherWritable = Black | background(Green),  // dir: sticky and other-writable (+t,o+w)
        OtherWritable = Blue | background(Green),         // dir: other-writable (o+w), not sticky
        Sticky = White | background(Blue),                // dir: sticky bit (+t) set
        Executable = bright(Green) | Bold,
        ArchiveOrCompressed = Red | Bold,
        Image = Magenta | Bold,
        Audio = Cyan
    };

    inline const std::string get_ansi_escape_code(const unsigned int ct) {
        return "\033[" + std::to_string(ct) + "m";
    }

    inline const std::string get_format_sequences(const ColorType ct) {
        std::string formatSequence;

        if (ct & FG_BLOCK) formatSequence += get_ansi_escape_code((ct & FG_BLOCK) >> 8);

        if (ct & BG_BLOCK) formatSequence += get_ansi_escape_code((ct & BG_BLOCK) >> 16);

        if (ct & SGT_BLOCK) {
            for (unsigned int bit = 0; bit < 8; bit++) {
                if (ct & (1 << bit)) formatSequence += get_ansi_escape_code(bit);
            }
        }

        return formatSequence;
    }
}  // namespace col

// These extensions are all taken from `dircolors -p`
const std::vector<std::string> ArchiveOrCompressedTypes{
    ".tar", ".tgz", ".arc",  ".arj", ".taz", ".lha", ".lz4",  ".lzh", ".lzma", ".tlz",
    ".txz", ".tzo", ".t7z",  ".zip", ".z",   ".dz",  ".gz",   ".lrz", ".lz",   ".lzo",
    ".xz",  ".zst", ".tzst", ".bz2", ".bz",  ".tbz", ".tbz2", ".tz",  ".deb",  ".rpm",
    ".jar", ".war", ".ear",  ".sar", ".rar", ".alz", ".ace",  ".zoo", ".cpio", ".7z",
    ".rz",  ".cab", ".wim",  ".swm", ".dwm", ".esd"};

const std::vector<std::string> ImageTypes{
    ".jpg", ".jpeg", ".mjpg", ".mjpeg", ".gif",  ".bmp",  ".pbm",  ".pgm", ".ppm", ".tga",
    ".xbm", ".xpm",  ".tif",  ".tiff",  ".png",  ".svg",  ".svgz", ".mng", ".pcx", ".mov",
    ".mpg", ".mpeg", ".m2v",  ".mkv",   ".webm", ".webp", ".ogm",  ".mp4", ".m4v", ".mp4v",
    ".vob", ".qt",   ".nuv",  ".wmv",   ".asf",  ".rm",   ".rmvb", ".flc", ".avi", ".fli",
    ".flv", ".gl",   ".dl",   ".xcf",   ".xwd",  ".yuv",  ".cgm",  ".emf", ".ogv", ".ogx"};

const std::vector<std::string> AudioTypes{".aac", ".au",   ".flac", ".m4a", ".mid", ".midi",
                                          ".mka", ".mp3",  ".mpc",  ".ogg", ".ra",  ".wav",
                                          ".oga", ".opus", ".spx",  ".xspf"};

const std::unordered_map<std::string, col::ColorType> ExtensionTypeMap = []() {
    using namespace col;
    std::unordered_map<std::string, ColorType> etm;

    for (auto type : ArchiveOrCompressedTypes) etm[type] = ColorType::ArchiveOrCompressed;

    for (auto type : ImageTypes) etm[type] = ColorType::Image;

    for (auto type : AudioTypes) etm[type] = ColorType::Audio;

    return etm;
}();

const std::string colorize_string(std::string string, const col::ColorType ct);
const std::string colorize_entry(std::filesystem::directory_entry path);
inline bool is_of_type(std::filesystem::directory_entry& path,
                       const std::vector<std::string>& type);
