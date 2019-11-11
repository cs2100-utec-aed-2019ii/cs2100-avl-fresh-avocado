//
// Created by Gabriel Spranger Rojas on 11/7/19.
//

#ifndef AVL_TREE_NODE_H
#define AVL_TREE_NODE_H

#include <iostream>

template <typename T>
struct Node {
    Node<T>* right = nullptr;
    Node<T>* left = nullptr;
    Node<T>* parent = nullptr;
    unsigned height;
    T value;

    explicit Node(const T& value): value{value}, height{1} {
//        no funcionó esto :(
//        static_assert(std::is_arithmetic(value), "Only numerical values are accepted!");
    }

    Node(const T& value, Node<T>* _parent): value{value}, parent{_parent}, height{1} {}

    ~Node() {
        std::cout << "Node with value " << value << " deleted!" << std::endl;
    }
};

#endif //AVL_TREE_NODE_H
