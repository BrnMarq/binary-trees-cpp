#include <cctype>

#include <stdexcept>

#include <Scanner.hpp>

Scanner::Scanner(std::string_view expr) noexcept
    : expression{expr}
{
    // empty
}

Token Scanner::get_next_token() noexcept
{
    this->skip_whitespaces();

    char c = this->getc();

    if (c == EoF)
    {
        return std::make_pair(TokenType::EoF, "");
    }
    
    if (std::isdigit(c))
    {
        this->unget();
        return this->build_integer_token();
    }
    
    switch (c)
    {
        case '+': return std::make_pair(TokenType::Add, "+");
        case '-': return std::make_pair(TokenType::Sub, "-");
        case '*': return std::make_pair(TokenType::Mul, "*");
        case '/': return std::make_pair(TokenType::Div, "/");
        case '%': return std::make_pair(TokenType::Mod, "/");
        case '(': return std::make_pair(TokenType::LParen, "(");
        case ')': return std::make_pair(TokenType::RParen, ")");
    }

    return std::make_pair(TokenType::Unknown, "");
}

Token Scanner::build_integer_token() noexcept
{
    std::string value{};
    
    char c = this->getc();

    while (std::isdigit(c))
    {
        value.push_back(c);
        c = this->getc();
    }

    if (c != EoF)
    {
        this->unget();
    }

    return std::make_pair(TokenType::Int, value);
}

bool Scanner::has_token() const noexcept
{
    return current_character < expression.size();
}

char Scanner::getc() noexcept
{
    if (!this->has_token())
    {
        return Scanner::EoF;
    }

    return this->expression[this->current_character++];
}

void Scanner::unget(size_t n) noexcept
{
    this->current_character -= n;
}

void Scanner::skip_whitespaces() noexcept
{
    if (!this->has_token())
    {
        return;
    }

    char c = this->getc();

    while (std::isspace(c))
    {
        c = this->getc();
    }

    if (c != EoF)
    {
        this->unget();
    }
}
