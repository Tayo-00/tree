#pragma once

#include <string>

namespace col {
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    // http://jlk.fjfi.cvut.cz/arch/manpages/man/core/man-pages/console_codes.4.en

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

    inline constexpr unsigned int bright(const unsigned int c) {
        return c + (60 << 8);
    }
    inline constexpr unsigned int background(const unsigned int c) {
        return c + (10 << 8);
    }

    enum SGT : const unsigned int {
        NormalReset = 1 << 0,
        Bold = 1 << 1,
        Faint = 1 << 2,
        Italic = 1 << 3,
        Underline = 1 << 4,
        Blink = 1 << 5
    };

    enum ColorType : const unsigned int {
        Normal = SGT::NormalReset,
        Archive = ColorCode::Red,
        Directory = bright(ColorCode::Blue) | SGT::Bold,
        Media = ColorCode::Magenta,
        Script = ColorCode::Green
    };

    inline const std::string get_ansi_escape_code(const unsigned int ct) {
        return "\033[" + std::to_string(ct) + "m";
    }

    inline const std::string get_format_sequences(const ColorType ct) {
        std::string formatSequence = get_ansi_escape_code(ct >> 8);

        if (ct & 0xFF) {
            for (unsigned int bit = 0; bit < 8; bit++) {
                if (ct & (1 << bit)) formatSequence += get_ansi_escape_code(bit);
            }
        }

        return formatSequence;
    }

}  // namespace col

const std::string colorize_string(std::string& string, const col::ColorType ct);
