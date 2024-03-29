#include "BinNode.hpp"

template <typename Key>
class BinaryTree
{
public:
  using KeyURefType = Key&&;
  using NodePtrType = std::shared_ptr<BinNode<Key>>;
  using NodePtrRefType = NodePtrType&;

  BinaryTree(KeyURefType k);
  virtual ~BinaryTree() = default;

  NodePtrRefType get_root() noexcept;

  template <typename Cmp = std::less<Key>>
  bool insert(KeyURefType k, Cmp c = {});

  template <typename Cmp = std::less<Key>>
  bool insert(KeyURefType k, NodePtrRefType node, Cmp c = {});

  // Non-copyable, non-movable, and non-assignable
  BinaryTree(const BinaryTree& node) = delete;
  BinaryTree(BinaryTree&& node) = delete;
  BinaryTree operator = (BinaryTree node) = delete;
private:
  NodePtrType root;
};

template <typename Key>
BinaryTree<Key>::BinaryTree(KeyURefType k): root{std::make_shared<BinNode<Key>>(std::move(k))}
{
  // empty
}

template <typename Key>
template <typename Cmp>
bool BinaryTree<Key>::insert(KeyURefType k, Cmp c)
{
  return insert(std::move(k), root, c);
}

template <typename Key>
template <typename Cmp>
bool BinaryTree<Key>::insert(KeyURefType k, NodePtrRefType node, Cmp c)
{
  if (node == nullptr) {
    node = std::make_shared<BinNode<Key>>(std::move(k));
    return true;
  };
  if (c(k, K(node))) insert(std::move(k), L(node), c);
  if (c(K(node), k)) insert(std::move(k), R(node), c);
  return false;
}

template <typename Key>
inline typename BinaryTree<Key>::NodePtrRefType BinaryTree<Key>::get_root() noexcept
{
    return this->root;
}