#pragma once
#include <vector>
#include<iostream>

template<class K, class V>
class bst {
public:
    class node {
    public:
        K key_;
        V value_;
        node* left_;
        node* right_;

        node(const K& key, const V& value)
                :key_(key), value_(value), left_(nullptr), right_(nullptr) {
        };

        node(const node& other) {
            key_ = other.key_;
            value_ = other.value_;
            left_ = other.left_;
            right_ = other.right_;
        }

        ~node() {
            if (left_ != nullptr) {
                delete left_;
            }

            if (right_ != nullptr) {
                delete right_;
            }
        }

    protected:
        node* most_left() {
            auto current = this;

            while (current->left_ != nullptr) {
                current = current->left_;
            }

            return current;
        }

        node* most_right() {
            auto current = this;

            while (current->right_ != nullptr) {
                current = current->right_;
            }

            return current;
        }

        node* left_parent(node* root) {
            auto current = root;
            auto parent = root;

            while (current->key_ != this->key_) {
                if (this->key_ < current->key_) {
                    parent = current;

                    current = current->left_;
                    continue;
                }

                current = current->right_;
            }

            return parent;
        }

        node* right_parent(node* root) {
            auto current = root;
            auto parent = root;

            while (current->key_ != this->key_) {
                if (this->key_ < current->key_) {
                    current = current->left_;
                    continue;
                }

                parent = current;
                current = current->right_;
            }

            return parent;
        }

        friend class bst;
    };

    template<class I>
    class iterator_base {
    public:
        iterator_base(node* current, bst* tree)
                :current_(current), tree_(tree) {
        };

        V& operator*() const {
            if (current_ == nullptr) {
                throw std::out_of_range("EXCEPTION: iterator out of bounds");
            }

            return current_->value_;
        };

        bool operator==(const iterator_base& other) const {
            return current_ == other.current_;
        };

        bool operator!=(const iterator_base& other) const {
            return current_ != other.current_;
        };

    protected:
        node* current_;
        bst* tree_;

        I& next() {
            if (current_->right_ != nullptr) {
                current_ = current_->right_->most_left();

                return *This();
            }

            auto parent = current_->left_parent(tree_->root_);

            if (current_->key_ < parent->key_) {
                current_ = parent;
            }
            else {
                current_ = nullptr;
            }

            return *This();
        }

        I& prev() {
            if (current_->left_ != nullptr) {
                current_ = current_->left_->most_right();

                return *This();
            }

            auto parent = current_->right_parent(tree_->root_);

            if (current_->key_ > parent->key_) {
                current_ = parent;
            }
            else {
                current_ = nullptr;
            }

            return *This();
        }

        friend class bst;

    private:
        I* This() {
            return static_cast<I*>(this);
        }
    };

    class iterator : public iterator_base<iterator> {
    public:
        iterator(node* current, bst* tree)
                :iterator_base<iterator>(current, tree) {

        }

        iterator operator++() {
            return iterator_base<iterator>::next();
        }

        iterator operator--() {
            return iterator_base<iterator>::prev();
        }
    };

    class reverse_iterator : public iterator_base<reverse_iterator> {
    public:
        reverse_iterator(node* current, bst* tree)
                :iterator_base<reverse_iterator>(current, tree) {

        }

        reverse_iterator operator++() {
            return iterator_base<reverse_iterator>::prev();
        }

        reverse_iterator operator--() {
            return iterator_base<reverse_iterator>::next();
        }
    };

    bst()
            :root_(nullptr), size_(0), operationsCounter_(0) {

    };

    bst(const bst& other) {
        root_ = new node(*other.root_);

        size_ = other.size_;
        operationsCounter_ = other.operationsCounter_;
        keys_ = other.keys_;
    }

    virtual bool insert(const K& key, const V& value) {
        operationsCounter_ = 0;

        try {
            root_ = insert(key, value, root_);
        }
        catch (std::exception& e) {
            return false;
        }

        size_ = size_ + 1;

        return true;
    }

    V& operator[](const K& key) {
        operationsCounter_ = 0;

        node* result = get(key, root_);

        if (result == nullptr) {
            throw std::runtime_error("EXCEPTION: key not found");
        }

        return (*result).value_;
    }

    virtual bool remove(const K& key) {
        operationsCounter_ = 0;

        try {
            root_ = remove(key, root_);
        }
        catch (std::exception& e) {
            return false;
        }

        size_ = size_ - 1;

        return true;
    }

    std::size_t size() {
        return size_;
    }

    void clear() {
        delete root_;

        root_ = nullptr;
        size_ = 0;
    }

    bool empty() {
        return size_ == 0;
    }

    std::size_t depth() {
        return depth(root_, 0);
    }

    const std::vector<K>& keys() {
        keys_.clear();
        keys_.reserve(size_);

        keys(root_);

        return keys_;
    }

    void print(std::ostream& out) {
        print(out, root_, 0);
    }

    iterator begin() {
        auto begin = root_;

        if (begin == nullptr) {
            return { begin, this };
        }

        while (begin->left_ != nullptr) {
            begin = begin->left_;
        }

        return { begin, this };
    }

    iterator end() {
        return { nullptr, this };
    }

    reverse_iterator rbegin() {
        auto rbegin = root_;

        if (rbegin == nullptr) {
            return { rbegin, this };
        }

        while (rbegin->right_ != nullptr) {
            rbegin = rbegin->right_;
        }

        return { rbegin, this };
    }

    reverse_iterator rend() {
        return { nullptr, this };
    }

    size_t operations_amount() {
        return operationsCounter_;
    }

    ~bst() {
        delete root_;
    };

protected:
    node* root_;
    size_t size_;

    std::vector<K> keys_ = std::vector<K>();
    size_t operationsCounter_ = 0;

    virtual node* insert(const K& key, const V& value, node* current) {
        operationsCounter_ = operationsCounter_ + 1;

        if (current == nullptr) {
            return new node(key, value);
        }

        if (key < current->key_) {
            current->left_ = insert(key, value, current->left_);
            return current;
        }
        else if (key > current->key_) {
            current->right_ = insert(key, value, current->right_);
            return current;
        }

        throw std::runtime_error("EXCEPTION: key already exists");
    }

    node* get(const K& key, node* current) {
        operationsCounter_ = operationsCounter_ + 1;

        if (current == nullptr || key == current->key_) {
            return current;
        }

        if (key < current->key_) {
            return get(key, current->left_);
        }

        return get(key, current->right_);
    }

    virtual node* remove(const K& key, node* current) {
        operationsCounter_ = operationsCounter_ + 1;

        if (current == nullptr) {
            throw std::runtime_error("EXCEPTION: key not found");
        }

        if (key < current->key_) {
            current->left_ = remove(key, current->left_);
            return current;
        }

        if (key > current->key_) {
            current->right_ = remove(key, current->right_);
            return current;
        }


        // Есть оба потомка
        if (current->left_ != nullptr && current->right_ != nullptr) {
            auto min = current->right_;

            while (min->left_ != nullptr) {
                min = min->left_;
            }

            current->key_ = min->key_;
            current->value_ = min->value_;

            current->right_ = remove(min->key_, current->right_);

            return current;
        }

        // Нет левого
        if (current->left_ != nullptr) {
            auto left_subtree = current->left_;

            current->key_ = left_subtree->key_;
            current->value_ = left_subtree->value_;
            current->left_ = left_subtree->left_;
            current->right_ = left_subtree->right_;

            left_subtree->left_ = nullptr;
            left_subtree->right_ = nullptr;
            delete left_subtree;

            return current;
        }

        // Нет правого
        if (current->right_ != nullptr) {
            auto right_subtree = current->right_;

            current->key_ = right_subtree->key_;
            current->value_ = right_subtree->value_;
            current->left_ = right_subtree->left_;
            current->right_ = right_subtree->right_;

            right_subtree->left_ = nullptr;
            right_subtree->right_ = nullptr;
            delete right_subtree;

            return current;
        }

        // Нет потомков
        delete current;
        current = nullptr;

        return current;
    }

    std::size_t depth(node* current, std::size_t current_depth) {
        if (current == nullptr) {
            return current_depth;
        }

        return std::max(depth(current->left_, current_depth + 1), depth(current->right_, current_depth + 1));
    }

    void keys(node* current) {
        if (current == nullptr) {
            return;
        }

        keys_.push_back(current->key_);
        keys(current->left_);
        keys(current->right_);
    }

    void print(std::ostream& out, node* current, std::size_t level) {
        if (current == nullptr) {
            return;
        }

        print(out, current->right_, level + 1);

        for (auto i = 0; i < level; i++) {
            std::cout << "   ";
        }
        std::cout << current->key_ << std::endl;

        print(out, current->left_, level + 1);
    }
};
