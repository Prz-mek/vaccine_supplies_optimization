#include "arraylist.hpp"
#include "network.hpp"
#include "reader.hpp"
#include "solver.hpp"

#include <iostream>
#include <fstream>
#include <getopt.h>

const std::string help = "Opcje:\n\t-i - plik wejściowy (po fladze podaj nazwę pliku)\n\t-o - plik wyjściowy (po fladze podaj nazwę pliku)\n"
			"Przykład wywołania:\n\t./voco -i plik_wejscowy.txt -o plik_wyjsciowy.txt";

int main(int argc, char** argv) {
	int opt;
	char* in = NULL;
	char* out = NULL;

	while ((opt = getopt(argc, argv, "i:o:")) != -1) {
		switch (opt) {
			case 'i':
				in = optarg;
				break;
			case 'o':
				out = optarg;
				break;
			default:
				std::cout << help << std::endl;
				exit(EXIT_FAILURE);
		}
	}

	ArrayList<Manufacturer> manufacturers;
	ArrayList<Chemists> chemists;

	if (in == NULL) {
		std::cerr << "Brak pliku wejściowego!\n";
		exit(EXIT_FAILURE);
	}
	
	Network* net = NULL;
	
	try {
		net = read_file(in, manufacturers, chemists);
	} catch (std::invalid_argument ex) {
		std::cerr << ex.what() << std::endl;
	}

	if (net != NULL) {

		solve(*net);

		if (out == NULL) {
			write(std::cout, *net, manufacturers, chemists);
		} else {
			std::ofstream fout;
			fout.open(out);
			if(fout.is_open()) {
				write(fout, *net, manufacturers, chemists);
				fout.close();
			} else {
				std::cout << "Nie udało się zapiasać danych do pliku. Podaje je w konsoli:" << std::endl;
				write(std::cout, *net, manufacturers, chemists);
			}
		}

		delete net;
	}

	return 0;
}
