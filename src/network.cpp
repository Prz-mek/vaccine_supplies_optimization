#include "network.hpp"

// --- Manufacturer methods --- //


Manufacturer::Manufacturer() { 
	id = 0;
	name = "X";
	supply = 0;
}

Manufacturer::Manufacturer(int id, std::string name, int supply) {
	this->id = id;
	this->name = name;
	this->supply = supply;
}

int Manufacturer::get_id() {
	return id;
}

std::string Manufacturer::get_name() {
	return name;
}

int Manufacturer::get_supply() {
	return supply;
}

// --- Chemists methods --- //

Chemists::Chemists() {
	id = 0;
	name = "X";
	demand = 0;
}

Chemists::Chemists(int id, std::string name, int demand) {
	this->id = id;
	this->name = name;
	this->demand = demand;
}

int Chemists::get_id() {
	return id;
}

std::string Chemists::get_name() {
	return name;
}

int Chemists::get_demand() {
	return demand;
}

// --- Network methods --- //

Network::Network(int chems_num, int manufs_num) {
	rows = chems_num + 1;
	cols = manufs_num + 1;
	int size = rows * cols;
	capacity = new int[size];
	flow = new int[size];
	costs = new double[size];
	for (int i = 0; i < size; i++) {
		capacity[i] = 0;
		flow[i] = 0;
		costs[i] = 0.0;
	}
}

int Network::size() {
	return rows + cols;
}

int Network::sorce() {
	return 0;
}

int Network::sink() {
	return rows + cols - 1;
}

int Network::devide() {
	return rows;
}

void Network::set_supply(int manuf_index, int value) {
	*(capacity + manuf_index) = value;
}

void Network::set_demand(int chem_index, int value) {
	*(capacity + (chem_index + 2) * cols - 1) = value;
}

void Network::add_connection(int manuf_index, int chem_index, int cap, double cost) {
	int index = (chem_index + 1) * cols + manuf_index;
	*(capacity + index) = cap;
	*(costs + index) = cost;
}

int Network::remaining_capacity(int from, int to) {
	if (from < rows && to >= rows) {
		if (from == 0 || to == rows + cols - 1) {
			return *(capacity + from * cols + to - rows) - *(flow + from * cols + to - rows);
		}else {
			return *(flow + from * cols + to - rows);
		}
	} else if (from >= rows && to < rows) {
		if (to == 0 || from == rows + cols - 1) {
			return *(flow + to * cols + from - rows);
		} else {
			return *(capacity + to * cols + from - rows) - *(flow + to * cols  + from - rows);
		}
	} else {
		return 0;
	}
}

double Network::cost(int from, int to) {
	if (from < rows && to >= rows) {
		if (from == 0 || to == rows + cols - 1) {
			return *(costs +from * cols + to - rows);
		}else {
			return -*(costs + from * cols + to - rows);
		}
	} else if (from >= rows && to < rows) {
		if (to == 0 || from == rows + cols - 1) {
			return -*(costs + to * cols + from - rows);
		} else {
			return *(costs + to * cols + from - rows);
		}
	} else {
		return 0.0;
	}
}

void Network::push(int from, int to, int amount) {
	if (from < rows && to >= rows) {
		if (from == 0 || to == rows + cols - 1) {
			*(flow + from * cols + to - rows) += amount;
		} else {
			*(flow + from * cols + to - rows) -= amount;
		}
	} else if (from >= rows && to < rows) {
		if (to == 0 || from == rows + cols - 1) {
			*(flow + to * cols + from - rows) -= amount;
		} else {
			*(flow + to * cols + from - rows) += amount;
		}
	}
}

int Network::get_flow(int chem_index, int manuf_index) {
	return *(flow + (chem_index + 1) * cols + manuf_index);
}

double Network::get_cost(int chem_index, int manuf_index) {
	return *(costs + (chem_index + 1) * cols + manuf_index);
}

Network::~Network() {
	delete[] capacity;
	delete[] flow;
	delete[] costs;
}
