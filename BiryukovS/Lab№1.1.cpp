#include <iostream>

class Number {
private:
	int a;
	int b;
public:
	Number() : a(0), b(1) {}
	void reduce() {
		for (int i = 2; i < 10; ++i) {
			if (a % i == 0 and b % i == 0) {
				while (a % i == 0 and b % i == 0) {
					a = a / i;
					b = b / i;
				}
			}
		}
	}
	void scan() {
		while (true) {
			std::cout << "Enter numerator and denominator\n";
			std::cin >> a >> b;
			if (b == 0) {
				std::cout << "Error: the denomirator cannot be 0\n" << "Try again\n";
			}
			else {
				break;
			}
		}
		reduce();
	}
	void summ() {
		int newa = 0;
		int newb = 0;
		std::cout << "Enter new fraction: ";
		while (true) {
			std::cin >> newa >> newb;
			if (newb == 0) {
				std::cout << "ERROR: incorrect fraction\n";
			}
			else {
				break;
			}
		}
		if (b != newb) {
			a = a * newb + newa * b;
			b = b * newb;
		}
		else {
			a = a + newa;
		}
		reduce();
	}
	void dif() {
		int newa = 0;
		int newb = 0;
		std::cout << "Enter new fraction: ";
		while (true) {
			std::cin >> newa >> newb;
			if (newb == 0) {
				std::cout << "ERROR: incorrect fraction\n";
			}
			else {
				break;
			}
		}
		if (b != newb) {
			a = a * newb - newa * b;
			b = b * newb;
		}
		else {
			a = a - newa;
		}
		reduce();
	}
	void mult() {
		int newa = 0;
		int newb = 0;
		std::cout << "Enter new fraction: ";
		while (true) {
			std::cin >> newa >> newb;
			if (newb == 0) {
				std::cout << "ERROR: incorrect fraction\n";
			}
			else {
				break;
			}
		}
		if (newb == 0) {
			std::cout << "The denomirator cannot be 0\n";
		}
		else {
			a = a * newa;
			b = b * newb;
		}
	}
	void div() {
		int newa = 0;
		int newb = 0;
		std::cout << "Enter new fraction: ";
		while (true) {
			std::cin >> newa >> newb;
			if (newb == 0) {
				std::cout << "ERROR: incorrect fraction\n";
			}
			else {
				break;
			}
		}
		if (newa == 0) {
			std::cout << "You cannot divide by 0\n";
		}
		else {
			a = a * newb;
			b = b * newa;
		}
	}
	void print() {
		std::cout << "The number is " << a << '/' << b << '\n';
	}
};
void menu() {
	using std::cout;
	cout << '\n'<< "Choose the operation:\n" << "1 - to enter number\n" << "2 - to print the number\n" << "3 - to add a fraction\n" << "4 - to substract a fraction\n";
	cout << "5 - to multiply by a fraction\n" << "6 - to divide by a fraction\n" << "7 - Exit the programm\n" << '\n';
}
int main() {
	int mode = 0;
	using std::cout;
	cout << "Welcome to calculator for fractions!!!\n";
	menu();
	Number A;
	int flag = 0;
	while (flag == 0) {
		while (true) {
			std::cin >> mode;
			if (mode >= 1 && mode <= 7) {
				break;
			}
			else {
				cout << "ERROR: incorrect input. Try again\n";
				menu();
			}
		}
		switch (mode) {
		case 1:
			A.scan();
			menu();
			break;
		case 2:
			A.print();
			menu();
			break;
		case 3:
			A.summ();
			menu();
			break;
		case 4:
			A.dif();
			menu();
			break;
		case 5:
			A.mult();
			menu();
			break;
		case 6:
			A.div();
			menu();
			break;
		case 7:
			++flag;
		}
	}
}