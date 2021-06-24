#include "../src/network.hpp"

#include <iostream>

const int size = 10;
const int seed = 24;

bool fill_get_cost_test() {
	double array[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			array[i][j] = double(rand()) / RAND_MAX;
		}
	}

	Network net(size, size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			net.add_connection(i, j, 100, array[i][j]);
		}
	}

	bool flag = true;
	for (int i = 0; i < size && flag; i++) {
		for (int j = 0; j < size && flag; j++) {
			flag = net.get_cost(j, i) == array[i][j];
		}
	}

	return flag;
}

int main() {
	srand(seed);

	std::cout << "Testy klasy network:" << std::endl;

	if (fill_get_cost_test()) {
		std::cout << "\tTest się powiódł." << std::endl;
	} else {
		std::cout << "\tWystąpił problem z zapisem i odczytem kosztu." << std::endl;
	}

	return 0;
}
