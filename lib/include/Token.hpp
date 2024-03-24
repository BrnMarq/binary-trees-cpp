#pragma once

#include <string>

enum class TokenType
{
    EoF,
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Int,
    LParen,
    RParen,
    Unknown
};

std::string to_string(TokenType token_type) noexcept;

using Token = std::pair<TokenType, std::string>;