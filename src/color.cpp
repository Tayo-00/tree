#include "color.hpp"

const std::string colorize_string(std::string& string, const col::ColorType ct) {
    return col::get_format_sequences(ct) + string +
           col::get_format_sequences(col::ColorType::Normal);
}
