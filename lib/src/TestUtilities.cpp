// #include <TestUtilities.hpp>

// // template <typename Key>
// // void print_tree_rec(std::shared_ptr<BinNode<Key>> root, std::ostream& out) noexcept
// // {
// //     if (root == nullptr)
// //     {
// //         return;
// //     }

// //     auto l = std::dynamic_pointer_cast<BinNode>(L(root));
// //     auto r = std::dynamic_pointer_cast<BinNode>(R(root));
// //     out << "(";    
// //     print_tree_rec(l, out);
// //     out << K(root).value;
// //     print_tree_rec(r, out);
// //     out << ")";
// // }

// // template <typename Key>
// // void print_tree(std::shared_ptr<BinNode<Key>> root, std::ostream& out) noexcept
// // {
// //     if (root == nullptr)
// //     {
// //         out << "()";
// //         return;
// //     }

// //     print_tree_rec(root, out);
// // }

// template <typename Key>
// std::ostream& operator << (std::ostream& out, std::shared_ptr<BinNode<Key>> root) noexcept
// {
//     print_arithm_tree(root, out);
//     return out;
// }

// template <typename Key>
// bool equal(std::shared_ptr<BinNode<Key>> t1, std::shared_ptr<BinNode<Key>> t2) noexcept
// {
//     if (t1 == nullptr && t2 == nullptr)
//     {
//         return true;
//     }

//     if (t1 == nullptr || t2 == nullptr)
//     {
//         return false;
//     }

//     auto l1 = std::dynamic_pointer_cast<BinNode<Key>>(L(t1));
//     auto r1 = std::dynamic_pointer_cast<BinNode<Key>>(R(t1));

//     auto l2 = std::dynamic_pointer_cast<BinNode<Key>>(L(t2));
//     auto r2 = std::dynamic_pointer_cast<BinNode<Key>>(R(t2));

//     return K(t1).value == K(t2).value && equal(l1, l2) && equal(r1, r2);
// }
