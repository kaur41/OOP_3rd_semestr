
#include "../D_Massive/DMassiv.h"
#pragma once
#include <cmath>
#include <stdexcept>
#include <string>

template <class T>
class TStack {
    T* _data;
    size_t _size;
    size_t _top;

public:
    TStack(size_t size = 20) {
        _data = new T[size];
        _size = size;
        _top = -1;
    }

    ~TStack() {
        delete[] _data;
        _data = nullptr;
    }

    void push(T val) {
        if (is_full()) {
            throw std::logic_error("Unexpected incident: stack is full");
        }
        _data[++_top] = val;
    }

    void pop() {
        if (is_empty()) {
            throw std::logic_error("Unexpected incident: stack is empty");
        }
        --_top;
    }

    T top() const {
        if (is_empty()) {
            throw std::logic_error("Unexpected incident: stack is empty");
        }
        return _data[_top];
    }

    bool find(T val) const noexcept {
        for (size_t i = 0; i <= _top; ++i) {
            if (_data[i] == val) {
                return true;
            }
        }
        return false;
    }

    bool is_empty() const noexcept {
        return _top == -1;
    }

    bool is_full() const noexcept {
        return _top == _size - 1;
    }

    int inverse_num(int num) {
        int ans = 0;
        int count = 0;
        TStack<int> s(10);
        while (num > 0) {
            s.push(num % 10);
            num /= 10;
        }
        while (!s.is_empty()) {
            ans += s.top() * std::pow(10, count);
            count++;
            s.pop();
        }
        return ans;
    }

    bool correct_value(const std::string& exp) {
        for (size_t i = 0; i < exp.size(); i++) {
            if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
                push(exp[i]);
            }
            else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
                if (is_empty()) {
                    throw std::logic_error("Unexpected incident: there is no bracket");
                }
                char bracket = top();
                pop();
                if ((exp[i] == ')' && bracket != '(') ||
                    (exp[i] == ']' && bracket != '[') ||
                    (exp[i] == '}' && bracket != '{')) {
                    throw std::logic_error("Unexpected incident: there is no matching bracket");
                }
            }
            else if (('0' > exp[i] || '9' < exp[i]) &&
                ('A' > exp[i] || 'Z' < exp[i]) &&
                ('a' > exp[i] || 'z' < exp[i]) &&
                exp[i] != '*' && exp[i] != '/' && exp[i] != '+' && exp[i] != '-') {
                throw std::logic_error("Unexpected incident: incorrect value in position");
            }
        }
        if (!is_empty()) {
            throw std::logic_error("Unexpected incident: stack is not empty");
        }
        return true;
    }
};
