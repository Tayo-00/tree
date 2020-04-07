#pragma once

#include <filesystem>
#include <string>

namespace col {
    // https://en.wikipedia.org/wiki/ANSI_escape_code
    // http://jlk.fjfi.cvut.cz/arch/manpages/man/core/man-pages/console_codes.4.en

    const unsigned int SGT_BLOCK = 0x0000FF;
    const unsigned int FG_BLOCK = 0x00FF00;
    const unsigned int BG_BLOCK = 0xFF0000;

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

    enum SGT : const unsigned int {
        NormalReset = 1 << 0,
        Bold = 1 << 1,
        Faint = 1 << 2,
        Italic = 1 << 3,
        Underline = 1 << 4,
        Blink = 1 << 5
    };

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
        Executable = Green | Bold,

        ArchiveOrCompressed = bright(Red),
        Image = Magenta,
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

const std::string colorize_string(std::string string, const col::ColorType ct);
const std::string colorize_entry(std::filesystem::directory_entry path);
