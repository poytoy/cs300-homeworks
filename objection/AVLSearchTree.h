//
// Created by Poyraz Güler on 21.11.2023.
//




#ifndef AVL_SEARCH_TREE_H
#define AVL_SEARCH_TREE_H
template<class Key,class Value>
class AVLSearchTree{
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
    int max(int a,int b){
        if(a>b){return a;}
        else {return b;}
    };
    int getBalance(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    };
    Node* rotateRight(Node* y) {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1+ max(getHeight(x->left), getHeight(x->right));

        return x;
    };
    Node* rotateLeft(Node *x) {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }
    Node* doubleRotateRight(Node* y) {
        y->left = rotateLeft(y->left);
        return rotateRight(y);
    }

    Node* doubleRotateLeft(Node* x) {
        x->right = rotateRight(x->right);
        return rotateLeft(x);
    }

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

        // Check balance and perform rotations if needed
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key) {
            return rotateRight(node);
        }
        if (balance < -1 && key > node->right->key) {
            return rotateLeft(node);
        }
        if (balance > 1 && key > node->left->key) {
            return doubleRotateRight(node);
        }
        if (balance < -1 && key < node->right->key) {
            return doubleRotateLeft(node);
        }

        return node;
    };
/*
    void destroy(Node* node){
        if(node!= nullptr){
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    };*/
    Node* destroyNode(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr; // Key not found
        }

        if (key == node->key) {
            // Found the node with the specified key, delete it
            return deleteNode(node);
        } else if (key < node->key) {
            // Key is in the left subtree
            node->left = destroyNode(node->left, key);
        } else {
            // Key is in the right subtree
            node->right = destroyNode(node->right, key);
        }

        // Update height and balance factor
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Perform rotations if needed
        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* deleteNode(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        // If the node has only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // If the node has two children, get the inorder successor
        Node* temp = findMin(node->right);

        // Copy the inorder successor's data to this node
        node->key = temp->key;
        node->value = temp->value;

        // Delete the inorder successor
        node->right = deleteNode(node->right);

        // Update height and balance factor
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        // Perform rotations if needed
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }


    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
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
    AVLSearchTree() :root(nullptr){
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
    void destroy_pub(const Key& key){
        root=destroyNode(root,key);
    }

    // Add any additional functions you need for your specific use case
};
#endif // AVL_SEARCH_TREE_H