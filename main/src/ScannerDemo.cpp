#include <iostream>

#include <Scanner.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " expression\n";
        return EXIT_FAILURE;
    }

    Scanner scanner{argv[1]};

    for (Token token; (token = scanner.get_next_token()).first != TokenType::EoF; )
    {
        std::cout << to_string(token.first) << ": " << token.second << std::endl;
    }

    return EXIT_SUCCESS;
}