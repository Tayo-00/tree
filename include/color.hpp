#pragma once

#include <string>

/*  Name            BG  FG
    --------------  --  --
    Black           30  40
    Red             31  41
    Green           32  42
    Yellow          33  43
    Blue            34  44
    Magenta         35  45
    Cyan            36  46
    White           37  47
    Bright Black    90  100
    Bright Red      91  101
    Bright Green    92  102
    Bright Yellow   93  103
    Bright Blue     94  104
    Bright Magenta  95  105
    Bright Cyan     96  106
    Bright White    97  107  */

namespace col {

    enum Color : const int { Black = 40, Red, Green, Yellow, Blue, Magenta, Cyan, White };

    inline constexpr int bright(Color c) {
        return c - 10;
    }
    inline constexpr int background(Color c) {
        return c + 60;
    }
    const int reset = 0;

    enum ColorType : int {
        Archive = Color::Red,
        Directory = bright(Color::Blue),
        Media = Color::Magenta,
        Script = Color::Green
    };

    inline std::string get_control_character(int ct) {
        std::string controlSequence = "\033[" + std::to_string(ct) + "m";
        return controlSequence;
    }

}  // namespace col

std::string colorize_string(std::string& string, col::ColorType ct);
