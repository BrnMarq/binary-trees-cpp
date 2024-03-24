#pragma once

#include <Token.hpp>
#include <Types.hpp>

class Parser
{
public:
    Parser(std::string_view expression);

    // Non-copyable, non-movable, and non-assignable
    Parser(const Parser& parser) = delete;
    Parser(Parser&& parser) = delete;
    Parser operator = (Parser parser) = delete;

    // Evaluation methods
    static long evaluate_integer(ArithmNode* node) noexcept;

    static long evaluate_addition(ArithmNode* node) noexcept;

    static long evaluate_subtraction(ArithmNode* node) noexcept;

    static long evaluate_multiplication(ArithmNode* node) noexcept;

    static long evaluate_division(ArithmNode* node) noexcept;

    static long evaluate_module(ArithmNode* node) noexcept;

    // Parenthesis validation
    static bool validate_parenthesis(std::string_view expression) noexcept;

    // From infix to suffix
    static std::vector<Token> build_suffix_expression(std::string_view expression);

    // Build the arithmetic tree
    std::shared_ptr<ArithmNode> build_arithmetic_tree() const;
private:
    std::vector<Token> suffix_expression;
};