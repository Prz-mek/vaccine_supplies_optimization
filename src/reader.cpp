#include "reader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cctype>
#include <climits>

#define MAX_DOUBLE 1e30
#define MAX_INT INT_MAX / 8

const std::string manufacturers = "Producenci szczepionek";
const std::string chemists = "Apteki";
const std::string connections = "Połączenia producentów i aptek";

int split(std::string line, ArrayList<std::string>& list) {
	int pos = 0;
	int count = 0;
	while ((pos = line.find("|")) != std::string::npos) {
		list.add(line.substr(0, pos));
		line.erase(0, pos + 1);
		count++;
	}
	list.add(line);
	return count;
}

std::string trim(std::string word) {
	int i = 0;
	int j = word.length() - 1;
	while (isspace(word[i])) {
		i++;
	}
	while (isspace(word[j])) {
		j--;
	}
	return word.substr(i, j - i + 1);
}

double round_2(double x) {
	x *= 100.0;
	x = round(x);
	return x / 100.0;
}


Network* read_file(char* path, ArrayList<Manufacturer>& manufs, ArrayList<Chemists>& chems) {
	std::ifstream fin;
	fin.open(path);
	if (fin.is_open()) {
		Network* net = NULL;
		int line_number = 1;
		std::string line;
		try {
			RedBlackTree<int> manufs_pos;
			RedBlackTree<int> chems_pos;

			getline(fin, line);
			if (line.at(0) == '#' && line.find(manufacturers) != std::string::npos) {
				getline(fin, line);
				line_number++;
				int i = 0;
				while (line.at(0) != '#') {
					ArrayList<std::string> temp_list;
					split(line, temp_list);
					if (temp_list.length() == 3) {
						int id = std::stoi(trim(temp_list.get(0)));
						std::string name = trim(temp_list.get(1));
						int supply = std::stoi(trim(temp_list.get(2)));

						if (supply > MAX_INT) {
							throw std::invalid_argument("stoi");
						}

						Manufacturer temp(id, name, supply);
						manufs.add(temp);
						manufs_pos.put(temp.get_id(), i);
						i++;
					} else {
						throw std::invalid_argument("Nie właściwa składniw w linii: " + std::to_string(line_number));
					}
					
					getline(fin, line);
					line_number++;
				}
			} else {
				throw std::invalid_argument("Brak listy producentów szczepionki.");
			}

			if (line.at(0) == '#' && line.find(chemists) != std::string::npos) {
				getline(fin, line);
				line_number++;
				int i = 0;
				while (line.at(0) != '#') {
					ArrayList<std::string> temp_list;
					split(line, temp_list);
					if (temp_list.length() == 3) {
						int id = std::stoi(trim(temp_list.get(0)));
						std::string name = trim(temp_list.get(1));
						int demand = std::stoi(trim(temp_list.get(2)));
						
						if (demand > MAX_INT) {
							throw std::invalid_argument("stoi");
						}

						Chemists temp(id, name, demand);
						chems.add(temp);
						chems_pos.put(temp.get_id(), i);
						i++;
					} else {
						throw std::invalid_argument("Nie właściwa składniw w linii: " + std::to_string(line_number));
					}
					
					getline(fin, line);
					line_number++;
				}
			} else {
				throw std::invalid_argument("Brak listy aptek.");
			}

			int m = manufs.length();
			int c = chems.length();

			net = new Network(c, m);

			for (int i = 0; i < m; i++) {
				net->set_supply(i, manufs.get(i).get_supply());
			}

			for (int i = 0; i < c; i++) {
				net->set_demand(i, chems.get(i).get_demand());
			}
			
			if (line.at(0) && line.find(connections) != std::string::npos) {
				getline(fin, line);
				line_number++;
				while (!line.empty() && line.at(0) != '#') {
					ArrayList<std::string> temp_list;
					split(line, temp_list);
					if (temp_list.length() == 4) {
						int mid = std::stoi(trim(temp_list.get(0)));
						int cid = std::stoi(trim(temp_list.get(1).c_str()));
						int amount = std::stoi(trim(temp_list.get(2)));
						double cost = round_2(std::stod(trim(temp_list.get(3))));
						
						if (amount > MAX_INT) {
							throw std::invalid_argument("stoi");
						}

						if (cost > MAX_DOUBLE) {
							throw std::invalid_argument("stod");
						}

						Node<int>* temp1 = manufs_pos.get(mid);
                    				Node<int>* temp2 = chems_pos.get(cid);
						if (temp1 != NULL && temp2 != NULL) {
                    					int from = temp1->get_value();
                    					int to = temp2->get_value();
							net->add_connection(from, to, amount, cost);
						} else {
							throw std::invalid_argument("ID z poza listy w linii: " + std::to_string(line_number));
						}

					} else {
						throw std::invalid_argument("Nie właściwa składniw w linii: " + std::to_string(line_number));
					}

					getline(fin, line);
					line_number++;
				}
			} else {
				throw std::invalid_argument("Brak listy połączeń producentów i aptek.");
			}

			fin.close();
			return net;

		} catch(std::invalid_argument ex) {
			fin.close();
			if (net != NULL) {
				delete net;
			}
			std::string syntax_stoi = "stoi";
			std::string syntax_stod = "stod";
			if (ex.what() == syntax_stoi) {
				throw std::invalid_argument("Nie udało się odczytać liczby całkowitej w linii: " + std::to_string(line_number));
			} else if (ex.what() == syntax_stod) {
				throw std::invalid_argument("Nie udało się odczytać liczby zmiennoprzecinkowej w linii: " + std::to_string(line_number));
			} else {
				throw ex;
			}
		} catch(std::out_of_range ex) {
			fin.close();
			if (net != NULL) {
				delete net;
			}
			std::string syntax_stoi = "stoi";
			std::string syntax_stod = "stod";
			if (ex.what() == syntax_stoi) {
				throw std::invalid_argument("Za duża liczba całkowita w linii: " + std::to_string(line_number));
			} else if (ex.what() == syntax_stod) {
				throw std::invalid_argument("Za duża liczba zmiennoprzecinkowa w linii: " + std::to_string(line_number));
			} else {
				throw ex;
			}
		}

	} else {
		throw std::invalid_argument("Nie udało się otworzyć pliku z danymi.");
	}
}


void write(std::ostream& fout, Network& net, ArrayList<Manufacturer>& makers, ArrayList<Chemists>& sellers) {
	int rows = sellers.length();
	int cols = makers.length();
	double total_cost = 0.0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			int flow = net.get_flow(i, j);
			if (flow > 0) {
				double cost = net.get_cost(i, j);
				fout << makers.get(j).get_name() << " -> " << sellers.get(i).get_name()
					<< " [Koszt = " << flow << " * " << cost << " = " << flow * cost << " zł]" << std::endl;
				total_cost += flow * cost;
			}	       
		}
	}

	std::ios_base::fmtflags initial = fout.setf(std::ios_base::fixed);
	fout.precision(2);
	fout << "Opłaty całkowite: " << total_cost << " zł" <<std::endl;
	fout.setf(initial);
	
}
