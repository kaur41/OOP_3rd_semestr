#include "../lib_Parser/Parser.h"
#include "../C_Stack/Header.h"
#include "../lib_TList/TemplateList.h"
#include "../lib_Parser/Parser.h"  
#include <iostream>
bool is_correct(const CString* exp) {
    Stack<char> st;
    const char* mass = exp->data();
    char module_bracket = '\0';

    for (size_t i = 0; i < exp->size() + 1; i++) {
        if (mass[i] == '(' || mass[i] == '[' || mass[i] == '{') {
            st.push(mass[i]);
        }
        else if (mass[i] == '|') {
            if (module_bracket == '\0') {
                // Встретили открывающую скобку модуля
                module_bracket = '|';
            }
            else {
                // Встретили закрывающую скобку модуля
                if (module_bracket == '|') {
                    module_bracket = '\0'; // Сбрасываем переменную
                }
                else {
                    throw std::logic_error("Mismatched brackets found");
                }
            }
        }
        else if (mass[i] == ')' || mass[i] == ']' || mass[i] == '}') {
            if (st.empty()) {
                throw std::logic_error("Unmatched closing bracket found");
            }
            else {
                char top = st.top();
                st.pop();
                if ((mass[i] == ')' && top != '(') ||
                    (mass[i] == ']' && top != '[') ||
                    (mass[i] == '}' && top != '{')) {
                    throw std::logic_error("Mismatched brackets found");
                }
            }
        }
    }

    if (!st.empty() || module_bracket != '\0') {
        throw std::logic_error("Unmatched opening bracket found");
    }

    return true;
}


//TList<int> list1;
//TList<int> list2;

//TList<int> Unification(TList<int> list1, TList<int> list2) {
//}
#include <iostream>

void main() {
    // Создаем первый список
    TList<int> list1;
    list1.push_back(1);
    list1.push_back(3);
    list1.push_back(5);

    // Создаем второй список
    TList<int> list2;
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(6);

    TList<int> result = list_uni(list1, list2);

    std::cout << "list1: ";
    for (auto it = list1.begin(); it != list1.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << " list2: ";
    for (auto it = list2.begin(); it != list2.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "unification(list3): ";
    for (auto it = result.begin(); it != result.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    system("pause");
}
