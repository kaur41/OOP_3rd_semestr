#include <iostream>
#include <stdexcept>

template <typename T>
struct NullNode {};

class TreeNode {
    int _value;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode() : _value(0), left(nullptr), right(nullptr) {}
    TreeNode(int value) : _value(value), left(nullptr), right(nullptr) {}

    int GetValue() const { return _value; }
    void SetValue(int val) { _value = val; }

    TreeNode* GetLeft() const { return left; }
    TreeNode* GetRight() const { return right; }
    void SetLeft(TreeNode* node) { left = node; }
    void SetRight(TreeNode* node) { right = node; }
};

class BinTree {
    TreeNode* _root;
    int _size;

    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->GetLeft()) {
            current = current->GetLeft();
        }
        return current;
    }

public:
    BinTree() : _root(nullptr), _size(0) {}
    ~BinTree() {
        clear(_root);
    }

    int Insert(int value) {
        if (!_root) {
            _root = new TreeNode(value);
            _size++;
            return 1;
        }
        return Insert(_root, value);
    }

    void Delete(int value) {
        _root = Delete(_root, value);
    }

    TreeNode* Find(int value) const {
        return Find(_root, value);
    }

    int FindMin() const {
        if (!_root) throw std::runtime_error("Tree is empty");
        TreeNode* current = _root;
        while (current->GetLeft()) {
            current = current->GetLeft();
        }
        return current->GetValue();
    }

    void Print() const {
        if (_root) {
            Print(_root, "", true);
        }
        else {
            std::cout << "Tree is empty" << std::endl;
        }
    }

    int Size() const { return _size; }
    bool Empty() const { return _size == 0; }

private:
    void clear(TreeNode* node) {
        if (node) {
            clear(node->GetLeft());
            clear(node->GetRight());
            delete node;
        }
    }

    int Insert(TreeNode* node, int value) {
        if (value < node->GetValue()) {
            if (!node->GetLeft()) {
                node->SetLeft(new TreeNode(value));
                _size++;
                return 1;
            }
            return Insert(node->GetLeft(), value);
        }
        else if (value > node->GetValue()) {
            if (!node->GetRight()) {
                node->SetRight(new TreeNode(value));
                _size++;
                return 1;
            }
            return Insert(node->GetRight(), value);
        }
        return 0;
    }

    TreeNode* Delete(TreeNode* node, int value) {
        if (!node) return nullptr;

        if (value < node->GetValue()) {
            node->SetLeft(Delete(node->GetLeft(), value));
        }
        else if (value > node->GetValue()) {
            node->SetRight(Delete(node->GetRight(), value));
        }
        else {
            if (!node->GetLeft()) {
                TreeNode* temp = node->GetRight();
                delete node;
                _size--;
                return temp;
            }
            else if (!node->GetRight()) {
                TreeNode* temp = node->GetLeft();
                delete node;
                _size--;
                return temp;
            }

            TreeNode* temp = minValueNode(node->GetRight());
            node->SetValue(temp->GetValue());
            node->SetRight(Delete(node->GetRight(), temp->GetValue()));
        }
        return node;
    }

    TreeNode* Find(TreeNode* node, int value) const {
        if (!node || node->GetValue() == value) {
            return node;
        }

        if (value < node->GetValue()) {
            return Find(node->GetLeft(), value);
        }

        return Find(node->GetRight(), value);
    }

    void Print(TreeNode* node, const std::string& prefix, bool isLeft) const {
        if (!node) return;

        std::cout << prefix;
        std::cout << (isLeft ? "+-- " : "\\-- ");
        std::cout << node->GetValue() << std::endl;

        Print(node->GetLeft(), prefix + (isLeft ? "|   " : "    "), true);
        Print(node->GetRight(), prefix + (isLeft ? "|   " : "    "), false);
    }
};

