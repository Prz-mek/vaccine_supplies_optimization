#ifndef DATA_SRTUCTURES_H_
#define DATA_SRTUCTURES_H_

#include "network.hpp"

template <typename T>
class ArrayList {
	private:
		int num;
		int size;
		T* data;

	public:
		ArrayList();
		void add(T elem);
		T get(int index);
		int length();
		void clear();
		~ArrayList();
	private:
		void double_size();
};

#endif
