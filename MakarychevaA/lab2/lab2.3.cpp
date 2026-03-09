#include <iostream>
class vector {
private:
	int* array;
	int size;
public:
	vector():array(nullptr),size(0){}
	vector(int n) {
		while (n < 1 || n > 20) {
			std::cout << "The vector size should be between 1 and 20" << std::endl;
			std::cout << "Enter size" << std::endl;
			std::cin >> n;
		}
		size = n;
		array = new int[size];
		for (int i = 0; i < size; i++) {
			array[i] = 0;
		}
	}
	~vector() {
		delete[] array;
	}
	vector(const vector& v) {
		size = v.size;
		array = new int[size];
		for (int i = 0; i < size; i++) {
			array[i] = v.array[i];
		}
	}
	vector& operator=(const vector& v) {
		if (this != &v) {
			delete[] array;
			size = v.size;
			array = new int[size];
			for (int i = 0; i < size; i++) {
				array[i] = v.array[i];
			}
			return *this;
		}
	}
	void setSize(int n) { 
		if (n < 1 || n > 20) {
			std::cout << "The vector size should be between 1 and 20" << std::endl;
			return;
		}
		delete[] array;
		size = n;
		array = new int[size];
		for (int i = 0; i < size; i++) {
			array[i] = 0;
		}
	}
	int getSize() const {
		return size;
	}
	void setComponent(int index, int value) {
		if (index < 0 || index >= size) {
			std::cout << "Error. Invalid index" << std::endl;
			return;
		}
		array[index] = value;
	}
	int getComponent(int index) const {
		if (index < 0 || index >= size) {
			std::cout << "Error. Invalid index" << std::endl;
			return 0;
		}
		return array[index];
	}
	double length() const {
		double sum = 0;
		for (int i = 0; i < size; i++) {
			sum += array[i] * array[i];
		}
		return sqrt(sum);
	}
	int composition(const vector& v) const {
		if (size != v.size) {
			std::cout << "Error.Vectors of different sizes" << std::endl;
			return 0;
		}
		int result = 0;
		for (int i = 0; i < size; i++) {
			result += array[i] * v.array[i];
		}
		return result;
	}
	vector sum(const vector& v) const {
		if (size != v.size) {
			std::cout << "Error.Vectors of different sizes" << std::endl;
			return vector();
		}
		vector result(size);
		for (int i = 0; i < size; i++) {
			result.array[i] = array[i] + v.array[i];
		}
		return result;
	}
	void print() const {
		std::cout << "[";
		for (int i = 0; i < size; i++) {
			std::cout << array[i];
			if (i < size - 1) {
				std::cout << ",";
			}
		}
		std::cout << "]" << std::endl;
	}
	void input() {
		std::cout << "Enter " << size << " elem" << std::endl;
		for (int i = 0; i < size; i++) {
			std::cin >> array[i];
		}
	}
};

int main() {
	int n;
	int choice;
	int num; 
	int idx, val;
	std::cout << "The first vector" << std::endl;
	std::cout << "Enter the size(1-20)" << std::endl;
	std::cin >> n;
	vector v1(n);
	v1.input();
	std::cout << "The second vector" << std::endl;
	std::cout << "Enter the size(1-20)" << std::endl;
	std::cin >> n;
	vector v2(n);
	v2.input();
	do {
		std::cout << "1.View vectors" << std::endl;
		std::cout << "2.The size of the vectors" << std::endl;
		std::cout << "3.Set the component" << std::endl;
		std::cout << "4.Get the component" << std::endl;
		std::cout << "5.Vector length" << std::endl;
		std::cout << "6.The scalar product" << std::endl;
		std::cout << "7.The sum of the vectors" << std::endl;
		std::cout << "0.Exit" << std::endl;
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "v1="; v1.print();
			std::cout << "v2="; v2.print();
			break;
		case 2:
			std::cout << "size v1=" << v1.getSize() << std::endl;
			std::cout << "size v2=" << v2.getSize() << std::endl;
			break;
		case 3: {
			std::cout << "Choose a vector(1 or 2)" << std::endl;
			std::cin >> num;
			std::cout << "Enter index" << std::endl;
			std::cin >> idx;
			std::cout << "Enter value" << std::endl;
			std::cin >> val;
			if (num == 1) {
				v1.setComponent(idx, val);
			}
			else {
				v2.setComponent(idx, val);
			}
			break;
		}
		case 4: {
			std::cout << "Choose a vector(1 or 2)" << std::endl;
			std::cin >> num;
			std::cout << "Enter index" << std::endl;
			std::cin >> idx;
			if (num == 1) {
				std::cout << "v1[" << idx << "] = " << v1.getComponent(idx) << std::endl;
			}
			else {
				std::cout << "v2[" << idx << "] = " << v2.getComponent(idx) << std::endl;
			}
			break;
		}
		case 5: {
			std::cout << "Choose a vector(1 or 2)" << std::endl;
			std::cin >> num;
			if (num == 1) {
				std::cout << "Lenght v1=" << v1.length() << std::endl;
			}
			else {
				std::cout << "Lenght v2=" << v2.length() << std::endl;
			}
			break;
		}
		case 6:
			std::cout << "The scalar product=" << v1.composition(v2) << std::endl;
			break;
		case 7: {
			vector v3 = v1.sum(v2);
			std::cout << "v1+v2=";
			v3.print();
			break;
		}
		case 0:
			return 0;
	}
	} while (choice != 0);
	return 0;
}
