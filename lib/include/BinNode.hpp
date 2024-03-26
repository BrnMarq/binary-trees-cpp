#include <memory>

template <typename Key>
class BinNode
{
public:
    
    using KeyType = Key;
    using KeyRefType = Key&;
    using KeyCRefType = const Key&;
    using KeyURefType = Key&&;
    using PointerType = std::shared_ptr<BinNode<Key>>;
    using PointerRefType = std::shared_ptr<BinNode<Key>>&;
    
    BinNode(KeyURefType k) noexcept;

    BinNode(KeyURefType k, PointerType l, PointerType r) noexcept;
    
    KeyRefType get_key() noexcept;

    KeyCRefType get_key() const noexcept;

    PointerRefType get_lchild() noexcept;

    PointerRefType get_rchild() noexcept;

    virtual ~BinNode() = default;

    PointerRefType CreateNode(int);

    PointerRefType InsertNode(PointerRefType ,int);

    PointerRefType FindNode(PointerRefType ,int);

    PointerRefType Join_Ex(PointerRefType , PointerRefType);

    void InOrder(PointerRefType);

    PointerRefType RemoveNode(PointerRefType , int);

private:
    KeyType key;
    PointerType lchild;
    PointerType rchild;
};

template <typename Key>
BinNode<Key>::BinNode(KeyURefType k) noexcept
    : key{k}, lchild{nullptr}, rchild{nullptr}
{
    // empty
}

template <typename Key>
BinNode<Key>::BinNode(KeyURefType k, PointerType l, PointerType r) noexcept
    : key{k}, lchild{l}, rchild{r}
{
    // empty
}

template <typename Key>
Key& BinNode<Key>::get_key() noexcept
{
    return this->key;
}

template <typename Key>
const Key& BinNode<Key>::get_key() const noexcept
{
    return this->key;
}

template <typename Key>
std::shared_ptr<BinNode<Key>>& BinNode<Key>::get_lchild() noexcept
{
    return this->lchild;
}

template <typename Key>
std::shared_ptr<BinNode<Key>>& BinNode<Key>::get_rchild() noexcept
{
    return this->rchild;
}


// Helper functions
template <typename BinNodeType>
inline typename BinNodeType::KeyRefType K(std::shared_ptr<BinNodeType> node) noexcept
{
    return node->get_key();
}

template <typename BinNodeType>
inline typename BinNodeType::KeyRefType K(BinNodeType* node) noexcept
{
    return node->get_key();
}

template <typename BinNodeType>
inline typename BinNodeType::PointerRefType L(std::shared_ptr<BinNodeType> node) noexcept
{
    return node->get_lchild();
}

template <typename BinNodeType>
inline typename BinNodeType::PointerRefType L(BinNodeType* node) noexcept
{
    return node->get_lchild();
}

template <typename BinNodeType>
inline typename BinNodeType::PointerRefType R(std::shared_ptr<BinNodeType> node) noexcept
{
    return node->get_rchild();
}

template <typename BinNodeType>
inline typename BinNodeType::PointerRefType R(BinNodeType* node) noexcept
{
    return node->get_rchild();
}
