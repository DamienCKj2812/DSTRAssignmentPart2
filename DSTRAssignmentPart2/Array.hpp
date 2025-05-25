#ifndef ARRAY_HPP
#define ARRAY_HPP

template<typename T>
class Array {
private:
	T* data;
	int capacity;
	int length;

public:
	Array() : capacity(4), length(0) {
		data = new T[capacity];
	}


// Copy Constructor
Array(const Array& other) {
	capacity = other.capacity;
	length = other.length;
	data = new T[capacity];
	for (int i = 0; i < length; ++i) {
		data[i] = other.data[i];
	}
}

	// Copy Assignment Operator
	Array& operator=(const Array& other) {
		if (this != &other) {
			delete[] data;
			capacity = other.capacity;
			length = other.length;
			data = new T[capacity];
			for (int i = 0; i < length; ++i) {
				data[i] = other.data[i];
			}
		}
		return *this;
	}

	~Array() {
		delete[] data;
	}

	void push(const T& value) {
		if (length == capacity) {
			resize();
		}
		data[length++] = value;
	}

	T get(int index) const {
		if (index < 0 || index >= length) return T();
		return data[index];
	}

	void set(int index, const T& value) {
		if (index >= 0 && index < length) {
			data[index] = value;
		} else {
			std::cout << "[Array Error] Index " << index << " is out of bounds (size = " << length << ").\n";
		}
	}

	int size() const {
		return length;
	}

	T pop() {
		if (length == 0) return T();
		T last = data[length - 1];
		data[length - 1] = T(); // clear last element
		length--;
		return last;
	}

	T shift() {
		if (length == 0) return T();
		T first = data[0];
		for (int i = 1; i < length; i++) {
			data[i - 1] = data[i];
		}
		length--;
		return first;
	}

private:
	void resize() {
		int newCap = capacity * 2;
		T* newData = new T[newCap];
		for (int i = 0; i < length; ++i) {
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = newCap;
	}
};

#endif
