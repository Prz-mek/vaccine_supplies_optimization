#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <string>

class Manufacturer {
	private:
		int id;
		std::string name;
		int supply;
	public:
		Manufacturer();
		Manufacturer(int id, std::string name, int supply);
		int get_id();
		std::string get_name();
		int get_supply();
};

class Chemists {
	private:
		int id;
		std::string name;
		int demand;
	public:
		Chemists();
		Chemists(int id, std::string name, int demand);
		int get_id();
		std::string get_name();
		int get_demand();
};

class Network {
	private:
		int rows;
		int cols;
		int* capacity;
		int* flow;
		double* costs;
	public:
		Network(int rows, int cols);
		int size();
		int sorce();
		int sink();
		int devide();
		void set_supply(int manuf_index, int value);
		void set_demand(int chem_index, int value);
		void add_connection(int manuf_index, int chem_index, int cap, double cost);
		int remaining_capacity(int from, int to);
		double cost(int from, int to);
		void push(int from, int to, int amount);
		int get_flow(int chems_index, int manuf_index);
		double get_cost(int chems_index, int manuf_index);
		~Network();
};

#endif
