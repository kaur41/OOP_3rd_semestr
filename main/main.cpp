#define EASY_EXAMPLE
#ifdef EASY_EXAMPLE

#include <iostream>
#include <iomanip>
#include "../lib_easy_example/easy_example.h"
#include "../D_Massive/DMassiv.h"
#include "../lib_String/CString.h"
#include "../lib_Parser/Parser.h"
#include "../lib_Tlist/TemplateList.h"

int main() {
    int a, b;
    float result;

    a = 1; b = 4;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    a = 1; b = 0;

    try {
        result = division(a, b);
        std::cout << a << " / " << b << " = "
            << std::setprecision(2) << result << std::endl;
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    char _a[16] = "(5*8) / (2+3)";

    CString ex(_a);

    bool _ans = is_correct(&ex);
    std::cout << _ans << "\n";

    TList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_pos(15, 1);
}

#endif  // EASY_EXAMPLE
