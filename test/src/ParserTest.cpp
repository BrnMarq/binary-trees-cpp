#include <Parser.hpp>
#include <TestUtilities.hpp>

int main()
{
    std::cout << "Parser test\n";

    auto int_five = std::make_shared<ArithmNode>(make_key("5", Parser::evaluate_integer));
    auto int_three = std::make_shared<ArithmNode>(make_key("3", Parser::evaluate_integer));

    {
        std::cout << "Testing evaluate_integer\n";
        assert_equal(int_five->eval(), 5L);
    }

    {
        std::cout << "Testing evaluate_addition\n";
        auto tree = std::make_shared<ArithmNode>(make_key("+", Parser::evaluate_addition), int_five, int_three);
        assert_equal(tree->eval(), 8L);
    }

    {
        std::cout << "Testing evaluate_subtraction\n";
        auto tree = std::make_shared<ArithmNode>(make_key("-", Parser::evaluate_subtraction), int_five, int_three);
        assert_equal(tree->eval(), 2L);
    }

    {
        std::cout << "Testing evaluate_multiplication\n";
        auto tree = std::make_shared<ArithmNode>(make_key("*", Parser::evaluate_multiplication), int_five, int_three);
        assert_equal(tree->eval(), 15L);
    }
    
    {
        std::cout << "Testing evaluate_division\n";
        auto tree = std::make_shared<ArithmNode>(make_key("/", Parser::evaluate_division), int_five, int_three);
        assert_equal(tree->eval(), 1L);
    }

    {
        std::cout << "Testing evaluate_module\n";
        auto tree = std::make_shared<ArithmNode>(make_key("%", Parser::evaluate_module), int_five, int_three);
        assert_equal(tree->eval(), 2L);
    }

    {
        std::cout << "Testing validate_parenthesis\n";
        assert_equal(Parser::validate_parenthesis("2 * (5 + 3)"), true);
    }
    {
        assert_equal(Parser::validate_parenthesis("2 * )5 + 3("), false);
    }
    {
        assert_equal(Parser::validate_parenthesis("2 * ((5 + 3)"), false);
    }
    {
        assert_equal(Parser::validate_parenthesis("(18+24)-(4*6*(14/1+(25*1+(8-10)+(22/3*(23-3*(16*25))))))*(8*17-(11-3+(13*17*(12/9-(16+8-(15/8))))))"), true);
    }

    {
        std::cout << "Testing build_suffix_expression\n";
        std::vector<Token> expected{{TokenType::Int, "2"}, {TokenType::Int, "5"}, {TokenType::Mul, "*"}, {TokenType::Int, "3"}, {TokenType::Add, "+"}};
        assert_equal(Parser::build_suffix_expression("2 * 5 + 3"), expected);
    }
    {
        std::vector<Token> expected{{TokenType::Int, "2"}, {TokenType::Int, "5"}, {TokenType::Int, "3"}, {TokenType::Add, "+"}, {TokenType::Mul, "*"}};
        assert_equal(Parser::build_suffix_expression("2 * (5 + 3)"), expected);
    }
    {
        std::vector<Token> expected{{TokenType::Int, "10"}, {TokenType::Int, "5"}, {TokenType::Sub, "-"}, {TokenType::Int, "5"}, {TokenType::Mul, "*"}, {TokenType::Int, "21"}, {TokenType::Int, "7"}, {TokenType::Div, "/"}, {TokenType::Add, "+"}};
        assert_equal(Parser::build_suffix_expression("(10 - 5) * 5 + 21/7"), expected);
    }
    {
        std::vector<Token> expected{{TokenType::Int, "18"}, {TokenType::Int, "24"}, {TokenType::Add, "+"}, {TokenType::Int, "4"}, {TokenType::Int, "6"}, {TokenType::Mul, "*"}, {TokenType::Int, "14"}, {TokenType::Int, "1"}, {TokenType::Div, "/"}, {TokenType::Int, "25"}, {TokenType::Int, "1"}, {TokenType::Mul, "*"}, {TokenType::Int, "8"}, {TokenType::Int, "10"}, {TokenType::Sub, "-"}, {TokenType::Add, "+"}, {TokenType::Int, "22"}, {TokenType::Int, "3"}, {TokenType::Div, "/"}, {TokenType::Int, "23"}, {TokenType::Int, "3"}, {TokenType::Int, "16"}, {TokenType::Int, "25"}, {TokenType::Mul, "*"}, {TokenType::Mul, "*"}, {TokenType::Sub, "-"}, {TokenType::Mul, "*"}, {TokenType::Add, "+"}, {TokenType::Add, "+"}, {TokenType::Mul, "*"}, {TokenType::Int, "8"}, {TokenType::Int, "17"}, {TokenType::Mul, "*"}, {TokenType::Int, "11"}, {TokenType::Int, "3"}, {TokenType::Sub, "-"}, {TokenType::Int, "13"}, {TokenType::Int, "17"}, {TokenType::Mul, "*"}, {TokenType::Int, "12"}, {TokenType::Int, "9"}, {TokenType::Div, "/"}, {TokenType::Int, "16"}, {TokenType::Int, "8"}, {TokenType::Add, "+"}, {TokenType::Int, "15"}, {TokenType::Int, "8"}, {TokenType::Div, "/"}, {TokenType::Sub, "-"}, {TokenType::Sub, "-"}, {TokenType::Mul, "*"}, {TokenType::Add, "+"}, {TokenType::Sub, "-"}, {TokenType::Mul, "*"}, {TokenType::Sub, "-"}};
        assert_equal(Parser::build_suffix_expression("(18+24)-(4*6*(14/1+(25*1+(8-10)+(22/3*(23-3*(16*25))))))*(8*17-(11-3+(13*17*(12/9-(16+8-(15/8))))))"), expected);
    }

    {
        std::cout << "Testing build_arithmetic_tree\n";
        auto int_two = std::make_shared<ArithmNode>(make_key("2", Parser::evaluate_integer));
        auto addition = std::make_shared<ArithmNode>(make_key("+", Parser::evaluate_addition), int_five, int_three);
        auto expected = std::make_shared<ArithmNode>(make_key("*", Parser::evaluate_multiplication), int_two, addition);
        assert_equal(Parser{"2 * (5 + 3)"}.build_arithmetic_tree(), expected);
    }
    {
        auto int_two = std::make_shared<ArithmNode>(make_key("2", Parser::evaluate_integer));
        auto addition = std::make_shared<ArithmNode>(make_key("+", Parser::evaluate_addition), int_five, int_three);
        auto expected = std::make_shared<ArithmNode>(make_key("*", Parser::evaluate_multiplication), int_two, addition);
        assert_equal(Parser{""}.build_arithmetic_tree(), expected);
    }

    {
        std::cout << "Tesing parsing result\n";
        assert_equal(Parser{"2 * 5 + 3"}.build_arithmetic_tree()->eval(), 13L);
        assert_equal(Parser{"2 * (5 + 3)"}.build_arithmetic_tree()->eval(), 16L);
        assert_equal(Parser{"(2 * (5) + 3)"}.build_arithmetic_tree()->eval(), 13L);
        assert_equal(Parser{"(2 * ((5) + 3))"}.build_arithmetic_tree()->eval(), 16L);
    }

    return EXIT_SUCCESS;
}