#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>
#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

inline constexpr unsigned int bright(const unsigned int color) {
    return color + (60 << 8);
}

inline constexpr unsigned int background(const unsigned int color) {
    return (color + (10 << 8)) << 8;
}

namespace tree {
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    // http://jlk.fjfi.cvut.cz/arch/manpages/man/core/man-pages/console_codes.4.en
    const unsigned int SGT_BLOCK = 0x0000FF;
    const unsigned int FG_BLOCK = 0x00FF00;
    const unsigned int BG_BLOCK = 0xFF0000;

    class color {
      protected:
        enum style : const unsigned int {
            normal_reset = 1 << 0,
            bold = 1 << 1,
            faint = 1 << 2,  // FIXME: if both fg and bg color set, will dim both
            italic = 1 << 3,
            underline = 1 << 4,
            blink = 1 << 5
        };

        static const std::string get_ansi_escape_code(const unsigned int color_type);

        static bool is_of_type(std::filesystem::directory_entry& path,
                               const std::vector<std::string>& type);

      public:
        enum code : const unsigned int {
            black = 30 << 8,
            red = 31 << 8,
            green = 32 << 8,
            yellow = 33 << 8,
            blue = 34 << 8,
            magenta = 35 << 8,
            cyan = 36 << 8,
            white = 37 << 8
        };

        enum type : const unsigned int {
            normal = normal_reset,
            directory = blue | bold,
            symbolic_link = cyan | bold,
            multi_hard_link = normal,           // regular file with more than one link
            fifo = yellow | background(black),  // pipe
            socket = magenta | bold,
            door = socket,
            block_device_driver = yellow | background(black) | bold,
            character_device_driver = yellow | background(black) | bold,
            orphan = red | background(black) |
                     bold,     // symlink to nonexistent file, or non-stat'able file ...
            missing = normal,  // ... and the files they point to
            file_setuid = white | background(red),     // file: with setuid (u+s)
            file_setgid = black | background(yellow),  // file: with setgid (g+s)
            fil_capability = black | background(red),  // file: with capability
            sticky_other_writable =
                black | background(green),              // dir: sticky and other-writable (+t,o+w)
            other_writable = blue | background(green),  // dir: other-writable (o+w), not sticky
            sticky = white | background(blue),          // dir: sticky bit (+t) set
            executable = bright(tree::color::code::green) | bold,
            archive_or_compressed = red | bold,
            image = magenta | bold,
            audio = cyan
        };

        static const std::string colorize_string(std::string string,
                                                 const tree::color::type color_type);
        static const std::string colorize_entry(std::filesystem::directory_entry path,
                                                bool full_path = false);

      private:
        static const std::string get_format_sequences(const tree::color::type color_type);
    };

}  // namespace tree

#endif  // COLOR_HPP