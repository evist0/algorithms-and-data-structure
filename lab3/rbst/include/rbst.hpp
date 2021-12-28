#pragma once
#include <stdlib.h>
#include <bst.hpp>

template<class K, class V>
class rbst : public bst<K, V> {
public:
    bool insert(const K& key, const V& value) override {
        this->operationsCounter_ = 0;

        try {
            this->root_ = insert(key, value, this->root_);

            this->size_ = this->size_ + 1;
        }
        catch (std::exception e) {
            return false;
        }

        return true;
    }

    bool remove(const K& key) override {
        this->operationsCounter_ = 0;

        try {
            this->root_ = remove(key, this->root_);

            this->size_ = this->size_ - 1;
        }
        catch (std::exception& e) {
            return false;
        }

        return true;
    }

    void print(std::ostream& out) {
        print(out, this->root_, 0);
    }

private:
    std::pair<typename bst<K, V>::node*, typename bst<K, V>::node*>
    split(typename bst<K, V>::node* current, const K& key) {
        if (node_size(current) == 0) {
            return std::make_pair(nullptr, nullptr);
        }

        if (key < current->key_) {
            auto pair = split(current->left_, key);

            current->left_ = pair.second;
            pair.second = new typename bst<K, V>::node(*current);

            return pair;
        }

        auto pair = split(current->right_, key);

        current->right_ = pair.first;
        pair.first = new typename bst<K, V>::node(*current);

        return pair;
    }

    std::size_t node_size(typename bst<K, V>::node* current) {
        if (current == nullptr) {
            return 0;
        }

        auto left_size = current->left_ == nullptr ? 0 : node_size(current->left_);
        auto right_size = current->right_ == nullptr ? 0 : node_size(current->right_);

        return left_size + right_size + 1;
    }

    void print(std::ostream& out, typename bst<K, V>::node* current, std::size_t level) {
        if (current == nullptr) {
            return;
        }

        print(out, current->right_, level + 1);

        for (auto i = 0; i < level; i++) {
            std::cout << "   ";
        }
        std::cout << current->key_ << " " << node_size(current) << std::endl;

        print(out, current->left_, level + 1);
    }

    typename bst<K, V>::node* insert_as_root(const K& key, const V& value, typename bst<K, V>::node* current) {
        if (current == nullptr) {
            return new typename bst<K, V>::node(key, value);
        }

        auto pair = split(current, key);

        current->key_ = key;
        current->value_ = value;

        current->left_ = pair.first;
        current->right_ = pair.second;

        return current;
    }

    typename bst<K, V>::node* insert(const K& key, const V& value, typename bst<K, V>::node* current) override {
        this->operationsCounter_ = this->operationsCounter_ + 1;

        if (current != nullptr && key == current->key_) {
            throw std::runtime_error("EXCEPTION: key already exists");
        }

        auto current_size = current == nullptr ? 0 : node_size(current);

        bool should_insert_root = rand() < RAND_MAX / (current_size + 1);

        if (should_insert_root) {
            current = insert_as_root(key, value, current);
            return current;
        }

        if (key < current->key_) {
            current->left_ = insert(key, value, current->left_);
            return current;
        }

        current->right_ = insert(key, value, current->right_);
        return current;
    }

    typename bst<K, V>::node* merge(typename bst<K, V>::node* left, typename bst<K, V>::node* right) {
        auto left_size = node_size(left);
        auto right_size = node_size(right);

        auto total_size = left_size + right_size;

        if (total_size == 0) {
            return nullptr;
        }

        if ((rand() / RAND_MAX / (left_size + right_size + 1)) < left_size) {
            if (left_size == 0) {
                return new typename bst<K, V>::node(right->key_, right->value_);
            }

            left->right_ = merge(left->right_, right);
            return left;
        }

        if (right_size == 0) {
            return new typename bst<K, V>::node(left->key_, left->value_);
        }

        right->left_ = merge(left, right->left_);
        return right;
    }

    typename bst<K, V>::node* remove(const K& key, typename bst<K, V>::node* current) override {
        this->operationsCounter_ = this->operationsCounter_ + 1;

        if (current == nullptr) {
            throw std::runtime_error("EXCEPTION: key doesn't exists");
        }

        if (key < current->key_) {
            current->left_ = remove(key, current->left_);
        }
        else if (key > current->key_) {
            current->right_ = remove(key, current->right_);
        }
        else {
            current = merge(current->left_, current->right_);
        }

        return current;
    }
};