#include <TestUtilities.hpp>

void print_arithm_tree_rec(std::shared_ptr<ArithmNode> root, std::ostream& out) noexcept
{
    if (root == nullptr)
    {
        return;
    }

    auto l = std::dynamic_pointer_cast<ArithmNode>(L(root));
    auto r = std::dynamic_pointer_cast<ArithmNode>(R(root));
    out << "(";    
    print_arithm_tree_rec(l, out);
    out << K(root).value;
    print_arithm_tree_rec(r, out);
    out << ")";
}

void print_arithm_tree(std::shared_ptr<ArithmNode> root, std::ostream& out) noexcept
{
    if (root == nullptr)
    {
        out << "()";
        return;
    }

    print_arithm_tree_rec(root, out);
}

std::ostream& operator << (std::ostream& out, std::shared_ptr<ArithmNode> root) noexcept
{
    print_arithm_tree(root, out);
    return out;
}

std::ostream& operator << (std::ostream& out, const Token& t) noexcept
{
    out << "(" << to_string(t.first) << ", " << t.second << ")";
    return out;
}

std::ostream& operator << (std::ostream& out, const std::vector<Token>& ts) noexcept
{
    out << "[";

    auto it = ts.begin();

    if (it != ts.end())
    {
        out << *it;
        ++it;
    }

    for ( ; it != ts.end(); ++it)
    {
        out << ", " << *it;
    }

    out << "]";

    return out;
}

bool equal(std::shared_ptr<ArithmNode> t1, std::shared_ptr<ArithmNode> t2) noexcept
{
    if (t1 == nullptr && t2 == nullptr)
    {
        return true;
    }

    if (t1 == nullptr || t2 == nullptr)
    {
        return false;
    }

    auto l1 = std::dynamic_pointer_cast<ArithmNode>(L(t1));
    auto r1 = std::dynamic_pointer_cast<ArithmNode>(R(t1));

    auto l2 = std::dynamic_pointer_cast<ArithmNode>(L(t2));
    auto r2 = std::dynamic_pointer_cast<ArithmNode>(R(t2));

    return K(t1).value == K(t2).value && equal(l1, l2) && equal(r1, r2);
}

bool equal(const std::vector<Token>& ts1, const std::vector<Token>& ts2) noexcept
{
    if (ts1.size() != ts2.size())
    {
        return false;
    }

    for (size_t i = 0; i < ts1.size(); ++i)
    {
        if (ts1[i] != ts2[i])
        {
            return false;
        }
    }

    return true;
}