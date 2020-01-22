#ifndef ECOMMERCE_ARRAY_H
#define ECOMMERCE_ARRAY_H
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
using namespace std;

template<class T>
class Array {
	int logsize, physize;
	char delimeter;
	T* arr;
public:
		Array(int Bsize = 10, char delimeter = ' ');
		Array(const Array& other);
		~Array();

		const Array& operator=(const Array& other);
		const Array& operator+=(const T& newVal);
		friend ostream& operator<<(ostream& os,const Array& arr) {
			for (int i - 0; i < arr.logsize; i++) {
				os << arr.arr[i] << arr.delimeter;
				return os;
			}
		}
	

};

template<class T>
Array<T>::Array(int Bsize, char delimeter): logsize(0), physize(Bsize), delimeter(delimeter){
	arr = new T[physize];
}

template<class T>
Array<T>::Array(const Array& other) : arr(nullptr){
	*this = other;
}

template<class T>
Array<T>::~Array() {
	delete[]arr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array& other) {
	if (this != &other) {
		delete[]arr;
		logsize = other.logsize;
		physize = other.physize;
		delimeter = other.delimeter;
		for (int i - 0; i < logsize;i++) {
			arr[i] = other.arr[i];
		}
	}
	return *this;
}


template<class T>
const Array<T>& Array<T>::operator+=(const T& newVal) {
	if (logsize < physize) {
		arr[logsize++] = newVal;
	}
	else {
		physize = physize*2;
		T* newarr = new T[physize];
		for (int i = 0; i < logsize;i++) {
			newarr[i] = arr[i];
		}
		newarr[logsize++] = newVal;
		delete[]arr;
		arr = newarr;
	}
}
#endif //ECOMMERCE_ARRAY_H