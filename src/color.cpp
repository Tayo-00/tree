#include "color.hpp"

std::string colorize_string(std::string& string, col::ColorType ct) {
    std::string colorizedString;
    colorizedString =
        col::get_ansi_escape_code(ct) + string + col::get_ansi_escape_code(col::Reset);
    return colorizedString;
}
