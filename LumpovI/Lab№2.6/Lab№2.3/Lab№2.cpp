#include <iostream>
#include <cmath>
class Vector {
private:
	double* elements;
	int size;
public:
	Vector(): elements(nullptr), size(0) {}

	Vector(int n) {
		while (n < 1 || n > 20) {
			std::cout << "Error: the vector size should be 1-20\n";
			std::cout << "Input size:\n";
			std::cin >> n;
		}
		size = n;
		elements = new double[size];
		for (int i = 0; i < size; i++) {
			elements[i] = 0;
		}
	}

	~Vector() {
		delete[] elements;
	}

	Vector(const Vector& v) {
		size = v.size;
		elements = new double[size];
		for (int i = 0; i < size; i++) {
			elements[i] = v.elements[i];
		}
	}

	Vector& operator=(const Vector& v) {
		if (this != &v) {
			delete[] elements;
			size = v.size;
			elements = new double[size];
			for (int i = 0; i < size; i++) {
				elements[i] = v.elements[i];
			}
			return *this;
		}
	}

	void setSize(int n) {
		if (n < 1 || n > 20) {
			std::cout << "Error: the vector size should be 1-20\n";	
			return;
		}
		delete[] elements;
		size = n;
		elements = new double[size];
		for (int i = 0; i < size; i++) {
			elements[i] = 0;
		}
	}

	int getSize() const {
		return size;
	}

	void setElem(int ind, int value) {
		if (ind < 1 || ind > size) {
			std::cout << "Error!!! Wrong number\n";
			return;
		}
		elements[ind-1] = value;
	}

	double getElem(int ind) const {
		if (ind < 1 || ind > size) {
			std::cout << "Error!!! Wrong number\n";
			return 0;
		}
		return elements[ind-1];
	}

	double length() const {
		double sum = 0;
		for (int i = 0; i < size; i++) {
			sum += elements[i] * elements[i];
		}
		return sqrt(sum);
	}

	Vector sum(const Vector& v) const {
		if (size != v.size) {
			std::cout << "Error!!! Sizes of vectors should be equal\n";
			return Vector();
		}
		Vector result(size);
		for (int i = 0; i < size; i++) {
			result.setElem(i+1,elements[i] + v.elements[i]);
		}
		return result;
	}

	double mult(const Vector& v) const {
		if (size != v.size) {
			std::cout << "Error!!! Sizes of vectors should be equal\n";
			return 0;
		}
		int result = 0;
		for (int i = 0; i < size; i++) {
			result += elements[i] * v.elements[i];
		}
		return result;
	}
	
	void print() const {
		std::cout << "[";
		for (int i = 0; i < size; i++) {
			std::cout << elements[i];
			if (i < size - 1) {
				std::cout << ",";
			}
		}
		std::cout << "]\n";
	}

	void input() {
		std::cout << "Enter " << size << " elements of your vector:\n";
		for (int i = 0; i < size; i++) {
			std::cin >> elements[i];
		}
	}
};

int main() {
	std::cout << "======= VECTORS UTILITY =======\n";
	int size, c, num, ind, value, set_size;
	std::cout << "Initialize the first vector\n";
	std::cout << "Enter the size(1-20):\n";
	std::cin >> size;
	Vector v1(size);
	v1.input();
	std::cout << "Initialize the second vector\n";
	std::cout << "Enter the size(1-20):\n";
	std::cin >> size;
	Vector v2(size);
	v2.input();
	do {
		std::cout << "======= MENU =======\n";
		std::cout << "1. Vectors output\n" << "2. Show the sizes of the vectors\n" << "3. Change vector size\n" << "4. Set the element\n" << "5. Get the element\n" << "6. Vector length\n" << "7. The scalar multiplication\n" << "8. The summary of the vectors\n" << "0. Exit\n";
		std::cin >> c;
		switch (c) {
		case 1:
			std::cout << "v1 = "; v1.print();
			std::cout << "v2 = "; v2.print();
			break;
		case 2:
			std::cout << "v1 size: " << v1.getSize() << std::endl;
			std::cout << "v2 size: " << v2.getSize() << std::endl;
			break;

		case 3: {
			std::cout << "Choose a vector(1 or 2):\n";
			std::cin >> num;
			std::cout << "Input new value of size:\n";
			std::cin >> set_size;
			if (num == 1) {
				v1.setSize(set_size);
				v1.input();
			}
			else {
				v2.setSize(set_size);
				v2.input();
			}
			break;
		}

		case 4: {
			std::cout << "Choose a vector(1 or 2):\n";
			std::cin >> num;
			std::cout << "Input index:\n";
			std::cin >> ind;
			std::cout << "Input value:\n";
			std::cin >> value;
			if (num == 1) {
				v1.setElem(ind, value);
			}else {
				v2.setElem(ind, value);
			}
			break;
		}
		case 5: {
			std::cout << "Choose a vector(1 or 2):\n";
			std::cin >> num;
			std::cout << "Input index:\n";
			std::cin >> ind;
			if (num == 1) {
				std::cout << "v1[" << ind << "] = " << v1.getElem(ind) << std::endl;
			}
			else {
				std::cout << "v2[" << ind << "] = " << v2.getElem(ind) << std::endl;
			}
			break;
		}
		case 6: {
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
		case 7:
			std::cout << "The scalar multiplication = " << v1.mult(v2) << std::endl;
			break;
		case 8: {
			Vector v3 = v1.sum(v2);
			std::cout << "v1+v2 = ";
			v3.print();
			break;
		}
		case 0:
			return 0;
		}
	} while (c != 0);
	return 0;
}