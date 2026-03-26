#include <iostream>
#include <cmath>

using std::cin;
using std::cout;

void menu() {
	cout << "\nWhat do you want to do?\n" << "1 - to enter the size of a vector\n" << "2 - to know the size\n" << "3 - to enter the component\n" << "4 - to know the component\n" << "5 - to know the length of the vector\n" << "6 - to know the scalar product\n" << "7 - to know the summ of vectors\n" << "8 - to print the vector\n" << "9 - to exit\n\n";
}

int number() {
	int x;
	while (!(cin >> x)) {
		cout << "ERROR: enter the number: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return x;
}

class Vector {
private:
	int size;
	int* arr;
public:
	Vector() : size(1) {
		arr = new int[size];
		arr[0] = 0;
	}
	Vector(int n) {
		if (n < 1) {
			n = 1;
		}
		if (n > 20) {
			n = 20;
		}
		size = n;
		arr = new int[size];
		for (int i = 0; i < size; ++i) {
			arr[i] = 0;
		}
	}
	Vector(const Vector& b) {
		size = b.size;
		arr = new int[size];
		for (int i = 0; i < size; i++) {
			arr[i] = b.arr[i];
		}
	}
	~Vector() {
		delete[] arr;
	}
	Vector newvector() {
		Vector V(size);
		cout << "Enter a new vector. The size is: " << size << '\n';
		for (int i = 0; i < size; ++i) {
			cout << i + 1 << ") ";
			V.arr[i] = number();
		}
		return V;
	}
	void operator=(const Vector& b) {
		if (this == &b) {
			return;
		}
		int* newarr = new int[b.size];
		for (int i = 0; i < b.size; i++) {
			newarr[i] = b.arr[i];
		}
		delete[] arr;
		arr = newarr;
		size = b.size;
	}
	void sz() {
		int newsize = 0;
		cout << "Enter the size of the vector (1 - 20): ";
		while (newsize > 20 || newsize < 1) {
			newsize = number();
			if (newsize > 20 || newsize < 1) {
				cout << "The size can be between 1 and 20. Try again: ";
			}
		}
		cout << '\n';
		int* newarr = new int[newsize];
		if (newsize <= size) {
			for (int i = 0; i < newsize; ++i) {
				newarr[i] = arr[i];
			}
		}
		else {
			for (int i = 0; i < size; ++i) {
				newarr[i] = arr[i];
			}
			for (int i = size; i < newsize; ++i) {
				newarr[i] = 0;
			}
		}
		delete[] arr;
		size = newsize;
		arr = newarr;
	}
	void setcomponent() {
		cout << "Enter the component that you want to set: ";
		int n = 0;
		while (n > size || n < 1) {
			n = number();
			if (n > size || n < 1) {
				cout << "The number can be between 1 and " << size << ".Try again : ";
			}
		}
		cout << '\n';
		cout << "Enter new number: ";
		arr[n - 1] = number();
	}

	void printsize() const {
		cout << "The size of the vector is: " << size << '\n';
	}
	void printvector() const {
		cout << "V = [";
		for (int i = 0; i < size - 1; ++i) {
			cout << arr[i] << " ";
		}
		cout << arr[size - 1] << "]";
	}
	void takecomponent() const {
		int n = 0;
		cout << "Enter the component you would like to know: ";
		while (n >= size || n <= 1) {
			n = number();
			if (n >= size || n <= 1) {
				cout << "The number can be between 1 and " << size << ".Try again: ";
			}
		}
		cout << "The " << n << "th component is: " << arr[n - 1];
	}
	void scal() {
		Vector V = newvector();
		int res = 0;
		for (int i = 0; i < size; ++i) {
			res = res + V.arr[i] * arr[i];
		}
		cout << "The result is: " << res << '\n';
	}
	void summ() {
		Vector V = newvector();
		Vector res(size);
		for (int i = 0; i < size; ++i) {
			res.arr[i] = arr[i] + V.arr[i];
		}
		cout << "The result is: ";
		res.printvector();
		cout << '\n';
	}
	void length() const {
		long long int len = 0;
		for (int i = 0; i < size; ++i) {
			len = len + arr[i] * arr[i];
		}
		double res = sqrt((double)len);
		cout << "The length of the vector is: " << res << '\n';
	}
};


int main() {
	int mode = 0;
	cout << "Welcome!!!\n";
	menu();
	Vector V;
	while (true) {
		while (true) {
			mode = number();
			if (mode >= 1 && mode <= 9) {
				break;
			}
			else {
				cout << "ERROR: incorrect input. Try again\n";
				menu();
			}
		}
		switch (mode) {
		case 1:
			V.sz();
			menu();
			break;
		case 2:
			V.printsize();
			menu();
			break;
		case 3:
			V.setcomponent();
			menu();
			break;
		case 4:
			V.takecomponent();
			menu();
			break;
		case 5:
			V.length();
			menu();
			break;
		case 6:
			V.scal();
			menu();
			break;
		case 7:
			V.summ();
			menu();
			break;
		case 8:
			V.printvector();
			menu();
			break;
		case 9:
			return 0;
			break;
		}
	}
}