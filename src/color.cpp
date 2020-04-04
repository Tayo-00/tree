#include "color.hpp"

std::string colorize_string(std::string& string, col::ColorType ct) {
    std::string colorizedString;
    colorizedString = get_control_character(ct) + string + col::get_control_character(col::reset);
    return colorizedString;
}
