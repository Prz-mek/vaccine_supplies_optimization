#include "arraylist.hpp"

#include <string>
#include <stdexcept>

template class ArrayList<std::string>;
template class ArrayList<int>;
template class ArrayList<Manufacturer>;
template class ArrayList<Chemists>;

template <typename T>
ArrayList<T>::ArrayList() {
	num = 0;
	size = 10;
	data = new T[size];
}

template <typename T>
void ArrayList<T>::double_size() {
	int newsize = 2 * size;
	T* newdata = new T[newsize];
	for (int i = 0; i < size; i++) {
		newdata[i] = data[i];
	}
	size = newsize;
	delete[] data;
	data = newdata;
}

template <typename T>
void ArrayList<T>::add(T elem) {
	if (num >= size) {
		double_size();
	}
	*(data + num) = elem;
	num++;
}

template <typename T>
T ArrayList<T>::get(int index) {
	if (index > num) {
		throw std::invalid_argument("Przekroczenie wielkości listy.");
	} else {
		return data[index];
	}
}

template <typename T>
int ArrayList<T>::length() {
	return num;
}

template <typename T>
void ArrayList<T>::clear() {
	num = 0;
}

template <typename T>
ArrayList<T>::~ArrayList() {
	delete[] data;
}
