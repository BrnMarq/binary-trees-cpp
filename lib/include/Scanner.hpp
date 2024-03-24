#pragma once 

#include <sstream>
#include <string_view>

#include <Token.hpp>

class Scanner
{
public:
    static constexpr char EoF = 0x05;

    Scanner(std::string_view expr) noexcept;

    Token get_next_token() noexcept;

private:
    bool has_token() const noexcept;

    char getc() noexcept;

    void unget(size_t n = 1) noexcept;

    void skip_whitespaces() noexcept;

    Token build_integer_token() noexcept;

    std::string_view expression;
    size_t current_character{0};
};
