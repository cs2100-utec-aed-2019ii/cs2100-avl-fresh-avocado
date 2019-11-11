//
// Created by Gabriel Spranger Rojas on 11/7/19.
//

#ifndef AVL_TREE_AVLTREE_H
#define AVL_TREE_AVLTREE_H

#include <queue>
#include "Node.h"

template <typename T>
class AVLTree {
    Node<T>* root;

public:
    AVLTree(): root(nullptr) {}
    explicit AVLTree(const T& value) {
//        static_assert(std::is_arithmetic(value), "Only numerical values are accepted!");
        root = new Node(value);
    }

    Node<T>* get_root() {
        return root;
    }

    /// Traversals

    void print_inorder(Node<T>* node) { // left - node - right
        if (node == nullptr)
            return;
        print_inorder(node->left);
        std::cout << node->key << " ";
        print_inorder(node->right);
    }

    void print_postorder(Node<T>* node) { // left - right - node
        if (node == nullptr)
            return;
        print_postorder(node->left);
        print_postorder(node->right);
        std::cout << node->data << " ";
    }

    void print_preorder(Node<T>* node) { // node - left - right
        if (node == nullptr)
            return;
        std::cout << node->data << " ";
        print_preorder(node->left);
        print_preorder(node->right);
    }

    void print_level_order(Node<T>* _root) {
        if (_root == nullptr)
            return;

        std::queue< Node<T>* > q;

        q.push(_root);

        while (!q.empty()) {
            // number of nodes at the current level
            unsigned node_count = q.size();

            // delete all nodes in the current level
            // insert all nodes in the next level
            while (node_count > 0) {
                Node<T>* node = q.front();
                std::cout << node->value << " ";
                q.pop();
                if (node->left != nullptr)
                    q.push(node->left);
                if (node->right != nullptr)
                    q.push(node->right);
                --node_count;
            }
            std::cout << std::endl;
        }
    }

    /// Helper Functions

    Node<T>* find_parent(const T& value) {
        Node<T>* curr = root;
        Node<T>* parent = nullptr;
        while (curr) {
            parent = curr;
            if (value > curr->value)
                curr = curr->right;
            else
                curr = curr->left;
        }
        return parent;
    }

    /// Rotations

    Node<T>* right_rotate(Node<T>* _node) {
        Node<T>* _root = _node;
        Node<T>* _rootChild = _node->left;

        _root->left = _rootChild->right;

        if (_rootChild->right) {
            _rootChild->right->parent = _root;
        }

        _rootChild->right = _root;

        if (_root->parent) {
            if (_root->parent->right == _root) {
                _root->parent->right = _rootChild;
            } else {
                _root->parent->left = _rootChild;
            }
            _root->parent = _rootChild;
        }

        _rootChild->parent = _root->parent;

        if (_node == root) {
            root = _rootChild;
        }

        _root->height = get_height(_root);
        _rootChild->height = get_height(_rootChild);
    }

    Node<T>* left_rotate(Node<T>* _node) {
        Node<T>* _root = _node;
        Node<T>* _rootChild = _node->right;

        _root->right = _rootChild->left;

        if (_rootChild->left) {
            _rootChild->left->parent = _root;
        }

        _rootChild->left = _root;

        if (_root->parent) {
            if (_root->parent->right == _root) {
                _root->parent->right = _rootChild;
            } else {
                _root->parent->left = _rootChild;
            }
            _root->parent = _rootChild;
        }

        _rootChild->parent = _root->parent;

        if (_node == root) {
            root = _rootChild;
        }

        _root->height = get_height(_root);
        _rootChild->height = get_height(_rootChild);
    }

    /// Obtener Altura

    unsigned get_height(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        } else {
            // sacar la altura de casa sub-arbol
            unsigned left_height = get_height(node->left);
            unsigned right_height = get_height(node->right);

            // retornar la mayor altura de ambas
            if (left_height > right_height)
                return left_height+1;
            else
                return right_height+1;
        }
    }

    int get_height_difference(Node<T>* _node) {
        return int(get_height(_node->right)) - int(get_height(_node->left));
    }

    /// Insert

    void insert(const T& value) {
        if (root == nullptr) {
            root = new Node(value);
            return;
        } else {
            insert_helper(root, value);
        }
    }

    void insert_helper(Node<T>* _node, const T& value) {
        if (_node->value < value) {
            if (_node->right) {
                insert_helper(_node->right, value);
            } else {
                _node->right = new Node<T>(value, _node);
            }
        } else if (_node->value > value){
            if (_node->left) {
                insert_helper(_node->left, value);
            }
            else {
                _node->left = new Node<T>(value, _node);
            }
        } else {
            return;
        }

        _node->height = get_height(_node);

        int height_difference = get_height_difference(_node);

        if (height_difference < -1 && value < _node->left->value) {
            right_rotate(_node);
        } else if(height_difference > 1 && value > _node->right->value) {
            left_rotate(_node);
        } else if(height_difference > 1 && value < _node->right->value) {
            right_rotate(_node->right);
            left_rotate(_node);
        } else if(height_difference < -1 && value > _node->left->value) {
            left_rotate(_node->left);
            right_rotate(_node);
        }
    }

    /// Delete all nodes

    void clear(Node<T>* _root) {
        if (_root == nullptr)
            return;
        clear(_root->left);
        clear(_root->right);
        delete _root;
    }

    ~AVLTree() {
        clear(root);
        printf("Deleted AVL Tree!\n");
    }
};

#endif //AVL_TREE_AVLTREE_H











