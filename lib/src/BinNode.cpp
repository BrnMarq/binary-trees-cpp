#include <BinNode.hpp>

// BinNode* CreateBinNode(int key)
// {
//     BinNode* newBinNode = new BinNode(key,nullptr,nullptr);
//     return newBinNode;
// }      

// BinNode* InsertBinNode(BinNode* root,int key)
// {
//     if(root == nullptr) return CreateBinNode(key);
//     if (key > root->key) root->right = InsertBinNode(root->right, key);
//     else if (key < root->key) root->left = InsertBinNode(root->left, key);
//     return root;
// }

// BinNode* FindBinNode(BinNode* root,int key)  
// {
//     if (root == NULL || root->key == key) return root;
//     else if (key > root->key) return FindBinNode (root->right,key);
//     else  return FindBinNode (root->left,key);
// }

// BinNode* Join_Ex(BinNode* minor, BinNode* higher) 
// {
//     if (minor == NULL) return higher;
//     else if (higher == NULL) return minor;
//     minor->right = Join_Ex(minor->right , higher->left);
//     higher->left = minor;
//     return higher;
// }
// void InOrder(BinNode* root)
// {
//     if(root != NULL)
//     {
//         InOrder(root->left);
//         std::cout << root->key << " ";
//         InOrder(root->right);
//     }
// }
// BinNode* RemoveBinNode(BinNode*& root, int key)
// {
//     if(root == nullptr) return nullptr;
//     if(key > root->key) RemoveBinNode(root->right, key);
//     else if(key < root->key) return RemoveBinNode(root->left, key);
//     else
//     {
//         std::cout << "/* message */" << std::endl;
//         // root = Join_Ex(root->left, root->right);
//         // if(temp2 == root) root = temp;
//         // return temp2;
//     }
// }