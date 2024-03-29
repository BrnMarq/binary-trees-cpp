#include <iostream>

#include <BinaryTree.hpp>
#include <TestUtilities.hpp>

int main() {
  std::cout << "Binary Tree Test\n";

  BinNode<int> node(10);
  BinaryTree<int> tree = BinaryTree<int>(10);
  tree.insert(14);

  print_tree(tree.get_root(), std::cout);
}