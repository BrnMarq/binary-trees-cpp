#include <iostream>
#include <stdexcept>

#include <Parser.hpp>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " expression\n";
        return EXIT_FAILURE;
    }

    Parser parser{argv[1]};
    auto arithm_tree = parser.build_arithmetic_tree();

    std::cout << arithm_tree->eval() << std::endl;
    
    return EXIT_SUCCESS;
}