#include <iostream>
#include <string>

template <class T>
struct Link {
    T _data;
    Link* _right;
    Link* _left;

    Link(T data) : _data(data), _right(nullptr), _left(nullptr) {}

    int insert(T data) {
        if (data < _data) {
            if (_left == nullptr) {
                _left = new Link<T>(data);
                return 1;
            }
            else {
                return _left->insert(data);
            }
        }
        else if (data > _data) {
            if (_right == nullptr) {
                _right = new Link<T>(data);
                return 1;
            }
            else {
                return _right->insert(data);
            }
        }
        else {
            return 0;
        }
    }

    void printTree(const std::string& prefix = "", bool isLeft = true) const {
        // Выводим текущий узел
        std::cout << prefix;
        std::cout << (isLeft ? "+-- " : "\\-- "); // Используем ASCII-символы
        std::cout << _data << std::endl;

        // Рекурсивно выводим левое и правое поддеревья
        if (_left != nullptr) {
            _left->printTree(prefix + (isLeft ? "|   " : "    "), true); // Левое поддерево
        }
        if (_right != nullptr) {
            _right->printTree(prefix + (isLeft ? "|   " : "    "), false); // Правое поддерево
        }
    }

    ~Link() {
        delete _left;
        delete _right;
    }
};

int main() {
    Link<int>* root = new Link<int>(4);
    root->insert(2);
    root->insert(1);
    root->insert(3);
    root->insert(7);
    root->insert(6);
    root->insert(9);
    root->insert(8);
    root->insert(11);

    root->printTree();

    delete root;

    return 0;
}