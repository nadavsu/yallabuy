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
		Array(int Bsize = 10, char delimeter = '\n');
		Array(const Array& other);
		Array(Array&& other);
		inline ~Array();

		inline const Array& operator=(const Array& other);
		const Array& operator+=(const T& newVal);
		T operator[](int index) const;
		int givelogsize() const;
		int givephysize() const;
		friend ostream& operator<<(ostream& os,const Array& arr) {
			for (int i = 0; i < arr.logsize; i++) {
				os << arr.arr[i] << arr.delimeter;
				return os;
			}
		}


};

template<class T>
Array<T>::Array(int Bsize, char delimeter): logsize(0), physize(Bsize), delimeter(delimeter){
	this->arr = new T[Bsize];
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
Array<T>::Array(Array&& other){
	cout << "in move array" << endl;
	this->delimeter = other.delimeter;
	this->logsize = other.logsize;
	this->physize = other.physize;
	this->arr = other.arr;
	other.arr = nullptr;
}

template<class T>
const Array<T>& Array<T>::operator=(const Array& other) {
	if (this != &other) {
		delete[]arr;
		logsize = other.logsize;
		physize = other.physize;
		delimeter = other.delimeter;
		for (int i = 0; i < logsize;i++) {
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
	return *this;
}
template<class T>
T Array<T>::operator[](int index) const {
	return arr[index];
}

template<class T>
int Array<T>::givelogsize() const {
	return logsize;
}
template<class T>
int Array<T>::givephysize() const {
	return physize;
}

// member function specialization
template<> // works with and without template<> 
inline const Array<Feedback*>& Array<Feedback*>::operator=(const Array<Feedback*>& other)
{
	if (this != &other) {
		delete[]arr;
		this->logsize = other.logsize;
		this->physize = other.physize;
		delimeter = other.delimeter;
		this->arr = new Feedback * [physize];
		for (int i = 0; i < this->logsize; i++) {
			Feedback* new_feed = new Feedback(*other.arr[i]);
			arr[i] = new_feed;
		}
	}
	return *this;
}
// member function specialization
template<> // works with and without template<> 
inline Array<Feedback*>::~Array() {
	for (int i = 0; i < logsize; i++) {
		delete arr[i];
	}
	delete[]arr;
}

#endif //ECOMMERCE_ARRAY_H