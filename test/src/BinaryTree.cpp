#include <iostream>

#include <BinaryTree.hpp>
#include <TestUtilities.hpp>

int main() {
  std::cout << "Binary Tree Test\n";

  BinaryTree<int> tree = BinaryTree<int>(13);
  std::vector<int> test_numbers = { 20, 8, 5, 30, 10, 15, 4, 6, 9, 11, 14, 17, 25, 35 };
  for (auto& number : test_numbers) {
    tree.insert(std::move(number));
  }

  print_tree(tree);
}