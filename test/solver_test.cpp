#include "../src/solver.hpp"
#include "../src/network.hpp"

#include <iostream>

const int size = 3;

bool solve_test() {
	int m_cap[size] = {900, 1300, 1100};
	int p_cap[size] = {450, 690, 1200};
	int c_cap[size][size] = {
		{800, 600, 750},
		{900, 600, 450},
		{900, 900, 300}
	};
	double cost[size][size] = {
		{70.5, 70, 90.99},
		{100, 80, 70},
		{80, 90, 100}
	};

	int answer[size][size] = {
		{0, 0, 450},
		{450, 240, 0},
		{450, 450, 300}
	};

	Network net(size, size);

	for (int i = 0; i < size; i++) {
		net.set_supply(i, m_cap[i]);
		net.set_demand(i, p_cap[i]);
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			net.add_connection(i, j, c_cap[i][j], cost[i][j]);
		}
	}

	solve(net);

	bool flag = true;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (net.get_flow(i, j) != answer[i][j]) {
				flag = false;
				break;
			}
		}
	}

	return flag;
}

int main() {
	std::cout << "Test matody solve." << std::endl;

	if (solve_test()) {
		std::cout << "\tTest się powiódł." << std::endl;
	} else {
		std::cout << "\tBłędny wynik." << std::endl;
	}

	return 0;
}
