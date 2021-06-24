#include "../src/arraylist.hpp"

#include <iostream>
#include <stdexcept>


const int size = 30;

bool put_get_test() {
	int array[size];
	for (int i = 0; i < size; i++) {
		array[i] = rand() % size;
	}

	ArrayList<int> list;
	for (int i = 0; i < size; i++) {
		list.add(array[i]);
	}

	bool flag = true;
	for(int i = 0; i < size; i++) {
		if (list.get(i) != array[i]) {
			flag = false;
			break;
		}
	}

	return flag;
}

bool out_except_test() {
	ArrayList<int> list;
	for (int i = 0; i < size; i++) {
		list.add(i);
	}

	try {
		list.get(2 * size + 1);
	} catch (std::invalid_argument ex) {
		return true;
	}

	return false;
}

int main() {

	std::cout << "Testy klasy ArrayList" <<std::endl;
	if (put_get_test()) {
		std::cout << "\tTest się powiódł." << std::endl;
	} else {
		std::cout << "\tTest funkcji put i get wykrył błąd!" << std::endl;
	}

	if (put_get_test()) {
		std::cout << "\tTest się powiódł." << std::endl;
	} else {
		std::cout << "\tTest funkcji get nie zwrócił wyjątku!" << std::endl;
	}

	return 0;
}
