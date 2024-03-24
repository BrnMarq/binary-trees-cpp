#include <stdexcept>

#include <Types.hpp>

long ArithmNode::eval() noexcept
{
    return this->get_key().eval_fct(this);
}

size_t PrecedenceTable::lookup(std::string_view op) const
{
    for (const auto& p: *this)
    {
        if (p.first == op)
        {
            return p.second;
        }
    }

    throw std::runtime_error{"Operator not found"};
}