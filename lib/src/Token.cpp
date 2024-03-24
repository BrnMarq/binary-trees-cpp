#include <Token.hpp>

std::string to_string(TokenType token_type) noexcept
{
    switch (token_type)
    {
        case TokenType::EoF: return "EoF";
        case TokenType::Add: return "Add";
        case TokenType::Sub: return "Sub";
        case TokenType::Mul: return "Mul";
        case TokenType::Div: return "Div";
        case TokenType::Mod: return "Mod";
        case TokenType::Int: return "Int";
        case TokenType::LParen: return "LParen";
        case TokenType::RParen: return "RParen";
        case TokenType::Unknown: return "Unknown";
    }

    return "";
}