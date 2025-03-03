
#pragma once

#include "../lib_TList/TemplateList.h"
#include "../lib_String/CString.h"
#include "../C_Stack/Header.h"
#include "iostream"
bool is_correct(const CString* exp);
//template <class T>
/*int  list_uni(TList<int> list1, TList<int> list2) {
	auto cur1 = list1.begin();
	auto cur2 = list2.begin();
	TList<int> result;
	//TNode<int>* head1 = list1.get_head();
	while (cur1 != list1.end() && cur2 != list2.end()) {
		if (*cur1<*cur2){
			result.push_back(*cur1);
			cur1++;
			//cur1= TList<T>.cur1->get_pnext();
		}
		else {
			result.push_back(*cur2);
			cur2++;
			//cur2 = TList<T>.cur2->get_pnext();
		}
		while (cur2 != list1.end()){
			result.push_back(*cur1);
			cur2++;
			//cur1 = TList<T>.cur1->get_pnext();
		}
		while (cur1 != list2.end()) {
			result.push_back(*cur2);
			cur1++;
			//cur2 = TList<T>.cur2->get_pnext();
		}
	}
	return result;
}*/
TList<int> list_uni(TList<int> list1,TList<int> list2) {
	auto cur1 = list1.begin();
	auto cur2 = list2.begin();
	TList<int> result;

	// Основной цикл слияния
	while (cur1 != list1.end() && cur2 != list2.end()) {
		if (*cur1 < *cur2) {
			result.push_back(*cur1);
			cur1++;
		}
		else {
			result.push_back(*cur2);
			cur2++;
		}
	}

	// Добавление оставшихся элементов из list1
	while (cur1 != list1.end()) {
		result.push_back(*cur1);
		cur1++;
	}

	// Добавление оставшихся элементов из list2
	while (cur2 != list2.end()) {
		result.push_back(*cur2);
		cur2++;
	}

	for (auto it = result.begin(); it != result.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	return result;
}
