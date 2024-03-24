#include <iostream>
#include <stack>

#include <Parser.hpp>

#include <Scanner.hpp>
#include <Token.hpp>

Parser::Parser(std::string_view expression)
    : suffix_expression{build_suffix_expression(expression)}
{
    // Empty
}

long Parser::evaluate_integer(ArithmNode* node) noexcept
{
    return std::stol(K(node).value);
}

long Parser::evaluate_addition(ArithmNode* node) noexcept
{
    ArithmNodePtr left = std::dynamic_pointer_cast<ArithmNode>(L(node));
    ArithmNodePtr right = std::dynamic_pointer_cast<ArithmNode>(R(node));

    return left->eval() + right->eval();
}

long Parser::evaluate_subtraction(ArithmNode* node) noexcept
{
    ArithmNodePtr left = std::dynamic_pointer_cast<ArithmNode>(L(node));
    ArithmNodePtr right = std::dynamic_pointer_cast<ArithmNode>(R(node));

    return left->eval() - right->eval();
}

long Parser::evaluate_multiplication(ArithmNode* node) noexcept
{
    ArithmNodePtr left = std::dynamic_pointer_cast<ArithmNode>(L(node));
    ArithmNodePtr right = std::dynamic_pointer_cast<ArithmNode>(R(node));

    return left->eval() * right->eval();
}

long Parser::evaluate_division(ArithmNode* node) noexcept
{
    ArithmNodePtr left = std::dynamic_pointer_cast<ArithmNode>(L(node));
    ArithmNodePtr right = std::dynamic_pointer_cast<ArithmNode>(R(node));

    return left->eval() / right->eval();
}

long Parser::evaluate_module(ArithmNode* node) noexcept
{
    ArithmNodePtr left = std::dynamic_pointer_cast<ArithmNode>(L(node));
    ArithmNodePtr right = std::dynamic_pointer_cast<ArithmNode>(R(node));

    return left->eval() % right->eval();
}

bool Parser::validate_parenthesis(std::string_view expression) noexcept
{
    int bracket_count = 0;
    for (int i = 0; i < expression.size(); ++i) {
        if (expression[i] == '(') ++bracket_count;
        if (expression[i] == ')') --bracket_count;
        if (bracket_count < 0) return false;
    }
    return bracket_count == 0;
}

std::vector<Token> Parser::Parser::build_suffix_expression(std::string_view expression)
{
    if (!validate_parenthesis(expression))
        throw std::runtime_error{"Parenthesis don't match"};

    Scanner scanner(expression);
    std::stack<Token> operands_stack;
    std::vector<Token> suffix;

    PrecedenceTable precedence{
        {"(", 0},
        {"+", 1},
        {"-", 1},
        {"*", 2},
        {"/", 2},
        {"%", 2},
    };

    auto token = scanner.get_next_token();
    for (; token.first != TokenType::EoF && token.first != TokenType::Unknown; token = scanner.get_next_token()) {
        auto [token_type, token_value] = token;
        if (token_type == TokenType::Int) suffix.push_back(token);
        else if (token_type == TokenType::LParen) operands_stack.push(token);
        else if (token_type == TokenType::RParen) {
            auto top_token = operands_stack.top();
            while(!operands_stack.empty()) {
                operands_stack.pop();
                if (top_token.first == TokenType::LParen) break;
                suffix.push_back(top_token);
                top_token = operands_stack.top();
            }
        }
        else if (!operands_stack.empty()) {
            auto top_token = operands_stack.top();
            while(precedence.lookup(top_token.second) >= precedence.lookup(token_value)) {
                operands_stack.pop();
                suffix.push_back(top_token);
                if (operands_stack.empty()) break;
                top_token = operands_stack.top();
            }
            operands_stack.push(token);
        }
        else {
            operands_stack.push(token);
        }
    }

    while (!operands_stack.empty()) {
        auto top_token = operands_stack.top();
        operands_stack.pop();
        suffix.push_back(top_token);
    }

    return suffix;
}

eval_fct_t get_eval_function(std::string operand) {
    if (operand == "+") return Parser::evaluate_addition;
    if (operand == "-") return Parser::evaluate_subtraction;
    if (operand == "*") return Parser::evaluate_multiplication;
    if (operand == "/") return Parser::evaluate_division;
    if (operand == "%") return Parser::evaluate_module;
    return Parser::evaluate_integer;
}

ArithmNodePtr Parser::build_arithmetic_tree() const
{
    std::vector<Token> expression = this->suffix_expression;
    if (expression.empty()) return nullptr;
    
    std::stack<ArithmNodePtr> node_stack;

    for (const auto& token: expression) {
        auto [token_type, token_value] = token;
        if (token_type == TokenType::Int) {
            node_stack.push(std::make_shared<ArithmNode>(make_key(token_value, Parser::evaluate_integer)));
            continue;
        }
        ArithmNodePtr childs[2];
        for (int i = 0; i < 2; ++i) {
            if (!node_stack.empty()) {
                childs[i] = node_stack.top();
                node_stack.pop();
                continue;
            }
            throw std::runtime_error{"Invalid Expression"};
        }
        node_stack.push(std::make_shared<ArithmNode>(make_key(token_value, get_eval_function(token_value)), childs[1], childs[0]));
    }
    if (node_stack.size() != 1) throw std::runtime_error{"Invalid Expression"};
    return node_stack.top();
} 