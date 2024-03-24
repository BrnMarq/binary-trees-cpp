#pragma once

#include <functional>
#include <forward_list>
#include <string>
#include <string_view>

#include <BinNode.hpp>

// Key forward declartion
struct ArithmNode;

// Eval function type
// It should receive a binary node and return an integer value.
using eval_fct_t = std::function<long(ArithmNode*)>;

// Struct to use as a binary node key
struct BinNodeKey
{
    // The value, it could be an operand or an operator value
    std::string value;

    // The evaluation function
    eval_fct_t eval_fct;
};

template <typename FunctionType>
BinNodeKey make_key(const std::string& value, FunctionType&& eval_function) noexcept
{
    return BinNodeKey{value, eval_fct_t{eval_function}};
}

// Specialization for an arithmetic node
class ArithmNode: public BinNode<BinNodeKey>
{
    using Base = BinNode<BinNodeKey>;
    using Base::Base;

public:
    long eval() noexcept;
};

// Alias for a pointer to arithmetic node
using ArithmNodePtr = std::shared_ptr<ArithmNode>;

class PrecedenceTable : public std::forward_list<std::pair<std::string, size_t>>
{
    using Base = std::forward_list<std::pair<std::string, size_t>>;
    using Base::Base;

public:
    size_t lookup(std::string_view op) const;
};