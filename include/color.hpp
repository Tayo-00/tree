#pragma once

#include <string>

namespace col {
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    // http://jlk.fjfi.cvut.cz/arch/manpages/man/core/man-pages/console_codes.4.en
    const unsigned int BOLD = 0x1000;
    const unsigned int Reset = 0;

    enum Color : const unsigned int { Black = 30, Red, Green, Yellow, Blue, Magenta, Cyan, White };

    inline constexpr unsigned int bright(unsigned int c) {
        return c + 60;
    }
    inline constexpr unsigned int background(unsigned int c) {
        return c + 10;
    }
    inline constexpr unsigned int bold(unsigned int c) {
        return c | BOLD;
    }

    enum ColorType : const unsigned int {
        Archive = Color::Red,
        Directory = bright(bold(Color::Blue)),
        Media = Color::Magenta,
        Script = Color::Green
    };

    inline const std::string get_ansi_escape_code(unsigned int ct) {
        std::string controlSequence = "\033[";

        if (ct & BOLD) controlSequence += "1;";

        controlSequence += std::to_string(ct & ~BOLD) + "m";

        return controlSequence;
    }

}  // namespace col

std::string colorize_string(std::string& string, col::ColorType ct);
