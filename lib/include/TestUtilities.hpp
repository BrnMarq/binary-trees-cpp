#pragma once

#include <iostream>
#include <vector>

#include <Token.hpp>
#include <Types.hpp>

std::ostream& operator << (std::ostream& out, std::shared_ptr<ArithmNode> root) noexcept;

std::ostream& operator << (std::ostream& out, const Token& t) noexcept;

std::ostream& operator << (std::ostream& out, const std::vector<Token>& ts) noexcept;

bool equal(std::shared_ptr<ArithmNode> t1, std::shared_ptr<ArithmNode> t2) noexcept;

bool equal(const std::vector<Token>& ts1, const std::vector<Token>& ts2) noexcept;

template <typename T>
bool equal(const T& x, const T& y) noexcept
{
    return x == y;
}

template <typename T>
void assert_equal(const T& current, const T& expected) noexcept
{
    if (!equal(current, expected))
    {
        std::cerr << "Test failed!\n";
        std::cerr << "Current value: " << current << std::endl;
        std::cerr << "Expected value: " << expected << std::endl;
        abort();
    }

    std::cout << "Test ok!\n";
}