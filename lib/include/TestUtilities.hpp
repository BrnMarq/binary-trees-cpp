#pragma once

#include <iostream>
#include <BinNode.hpp>

template <typename Key>
void print_tree_rec(std::shared_ptr<BinNode<Key>> root, std::ostream& out) noexcept
{
    if (root == nullptr) return;
    auto l = std::dynamic_pointer_cast<BinNode<Key>>(L(root));
    auto r = std::dynamic_pointer_cast<BinNode<Key>>(R(root));
    out << K(root) << std::endl;
    if (l != nullptr) out << "/ ";
    else out << "  ";
    if (r != nullptr) out << "\\";
    out << std::endl;
    print_tree_rec(l, out);
    print_tree_rec(r, out);
}

template <typename Key>
void print_tree(std::shared_ptr<BinNode<Key>> root, std::ostream& out) noexcept
{
    if (root == nullptr)
    {
        out << "()";
        return;
    }

    print_tree_rec(root, out);
}


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