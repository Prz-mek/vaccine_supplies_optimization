#include <fstream>
#include <ctime>

int main(int argc, char** argv) {
	std::ofstream out;

	if (argc > 1) {
		out.open(argv[1]);
	}

	int m = argc > 2 ? std::atoi(argv[2]) : 10;
	int c = argc > 3 ? std::atoi(argv[3]) : 10;
	long seed = argc > 4 ? std::atoi(argv[4]) : time(NULL);

	if (!out.is_open()) {
		exit(EXIT_FAILURE);
	}

	srand(seed);

	out << "# Producenci szczepionek (id | nazwa | dzienna produkcja)\n";

	for (int i = 0; i < m; i++) {
		out << i << " | " << i << " | " << rand() % 2500 + 300 << std::endl;
	}

	out << "# Apteki (id | nazwa | dzienne zapotrzebowanie)\n";

	for (int i = 0; i < c; i++) {
		out << i << " | " << i << " | " << rand() % 2000 + 200 << std::endl;
	}

	out << "# Połączenia producentów i aptek (id producenta | id apteki | dzienna maksymalna liczba dostarczanych szczepionek | koszt szczepionki [zł] )";

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < c; j++) {
			out << i << " | " << j << " | " << rand() % 1500 + 200 << " | " <<  70.0 * rand() / RAND_MAX + 30.0 << std::endl;
		}
	}

	out.close();	

	return 0;
}
