//
// Created by Poyraz Güler on 20.12.2023.
//

#ifndef HW3_BST_H
#define HW3_BST_H
using namespace std;
template<class Key,class Value>
class BSTSearchTree{
private:
    struct Node {
        Key key;
        Value* value;
        Node* left;
        Node* right;
        int height;

        Node(const Key& k, Value* v)
                : key(k), value(v), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return (node->height);
    };

    Node* insert(Node* node, const Key &key, Value *value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            // If the key is equal, update the value
            node->value = value;
            return node;
        }

        // Update height of the current node
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    };

    Value* search(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr; // Key not found
        }

        if (key == node->key) {
            return node->value; // Key found
        } else if (key < node->key) {
            return search(node->left, key); // Search in the left subtree
        } else {
            return search(node->right, key); // Search in the right subtree
        }
    };

public:
    BSTSearchTree() :root(nullptr){
    };
    void insert_pub(const Key& key, Value* value) {
        root=insert(root,key,value);
    };
    Value* search_pub(const Key& key){
        if(search(root,key)!=nullptr){
            return search(root,key);
        }
        else{return nullptr;}
    }
};
#endif //HW3_BST_H
