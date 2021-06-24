#include "../src/redblacktree.hpp"

#include <iostream>

#define MAX 500

const int size = 50;
const int seed = 394;

bool put_get_test() {
	int keys[size];
	int values[size];
	for (int i = 0; i < size; i++) {
		keys[i] = rand() % MAX;
		values[i] = rand() % MAX;
	}

	RedBlackTree<int> tree;
	for (int i = 0; i < size; i++) {
		tree.put(keys[i], values[i]);
	}

	bool flag = true;
	for (int i = 0; i < size; i++) {
		Node<int>* temp = tree.get(keys[i]);
		if (temp == NULL) {
			std::cout << "1\n";
			flag = false;
			break;
		}
		
		if (temp->get_value() != values[i]) {
			flag = false;
			break;
		}
	}

	return flag;
}

bool put_with_incorrect_key_test() {
	
	RedBlackTree<int> tree;
	for (int i = 0; i < size; i++) {
		tree.put(i, i);
	}

	return tree.get(2 * size) == NULL;
}

int main() {

	srand(seed);
	std::cout << "Test klasy RedBlackTree." << std::endl;

	if (put_get_test()) {
		std::cout << "\tTest się powiódł" << std::endl;
	} else {
		std::cout << "\tWystąpił błąd dla metody put lub get." << std::endl;
	}

	if (put_with_incorrect_key_test()) {
		std::cout << "\tTest się powiódł" << std::endl;
	} else {
		std::cout << "\tWystąpił błąd przy wywołaniu niewłaściwego klucza." << std::endl;
	}

	return 0;
}
