#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::cin;
using std::string;
// рандомные функции для примера
double st(double a) {
	return a * a;
}
double minus1(double a) {
	return a - 1.0;
}
// функция проверки ввода на число. на проверку входят разные типы (int и double), поэтому шаблонная
template <typename T>
T num() {
	T x;
	while (!(cin >> x)) {
		cout << "ERROR: enter the number: ";
		cin.clear();
		cin.ignore(10000, '\n');
	}
	return x;
}

class Menu {
private:
	using fooptr = double(*)(double);
	int number;
	int count;
	string* arr;
	fooptr* foo;
public:
	Menu() : number(1), count(0), arr(new string[number]), foo(new fooptr[number]) {
		arr[0] = "";
		foo[0] = nullptr;
	}
	Menu(int n) : number(n), count(0), arr(new string[number]), foo(new fooptr[number]) {
		for (int i = 0; i < number; ++i) {
			arr[i] = "";
			foo[i] = nullptr;
		}
	}
	
	Menu(const Menu& b) {
		number = b.number;
		arr = new string[number];
		foo = new fooptr[number];
		for (int i = 0; i < number; i++) {
			arr[i] = b.arr[i];
			foo[i] = b.foo[i];
		}
	}
	
	Menu& operator=(const Menu& b) {
		if (this == &b) {
			return *this;
		}
		string* newarr = new string[b.number];
		fooptr* newfoo = new fooptr[b.number];
		for (int i = 0; i < b.number; i++) {
			newfoo[i] = b.foo[i];
			newarr[i] = b.arr[i];
		}
		delete[] foo;
		delete[] arr;
		arr = newarr;
		foo = newfoo;
		number = b.number;
		return *this;
	}
	~Menu() {
		delete[] arr;
		delete[] foo;
	}
	void setnum(int n) {
		string* newarr = new string[n];
		fooptr* newfoo = new fooptr[n];
		if (number > n) {
			for (int i = 0; i < n; ++i) {
				newarr[i] = arr[i];
				newfoo[i] = foo[i];
			}
		}
		else if (number < n) {
			for (int i = 0; i < number; ++i) {
				newarr[i] = arr[i];
				newfoo[i] = foo[i];
			}
			for (int i = number; i < n; ++i) {
				newarr[i] = "";
				newfoo[i] = nullptr;
			}
		}
		else {
			return;
		}
		delete[] arr;
		delete[] foo;
		number = n;
		arr = newarr;
		foo = newfoo;
	}
	int getnum() const {
		return number;
	}
	void setitem(int n, string name, fooptr f) {
		--n;
		if (n >= 0 && n < number) {
			arr[n] = name;
			foo[n] = f;
		}
	}
	void print() const {
		cout << "----------- MENU -----------\n\n";
		cout << "Enter the option:\n";
		for (int i = 0; i < number; ++i) {
			cout << i + 1 << " - " << arr[i] << '\n';
		}
		cout << '\n';
	}
	void choice() {
		cout << "Enter your choice: ";
		int mode = 0;
		while (true) {
			mode = num<int>();
			cout << '\n';
			if (mode < 1 || mode > number) {
				cout << "The number should be from 1 to " << number << '\n' << "Enter another: ";
			}
			else {
				count = mode;
				cout << "Your choice is " << mode << " - " << arr[mode - 1] << '\n' << "Enter the argument: ";
				double arg = num<double>();
				double res = foo[mode - 1](arg);
				cout << "The result is: " << res << "\n";
				break;
			}
		}
	}
	int getlastchoice() const {
		if (count == 0) {
			cout << "Nothing has been choosen\n";
			return 0;
		}
		else {
			return count;
		}
	}
	string getlastchoice(double a) const { // перегрузил функцию для удобного вывода не только count, но и функции, к которой он относится
		return arr[count - 1];
	}

};
void menuu() {
	cout << "1 - to choose\n" << "2 - to know the number of operations\n" << "3 - to print the menu\n" << "4 - to know the last operation\n" << "5 - to exit\n";
}
int main() {
	Menu M(2);
	M.setnum(5);
	M.setitem(1, "cos(x)", cos);
	M.setitem(2, "sin(x)", sin);
	M.setitem(3, "tan(x)", tan);
	M.setitem(4, "the second degree", st);
	M.setitem(5, "minus 1", minus1);
	M.print();
	int mode = 0;
	menuu();
	while (true) {
		while (true) {
			mode = num<int>();
			if (mode >= 1 && mode <= 5) {
				break;
			}
			else {
				cout << "ERROR: incorrect input. Try again\n";
				menuu();
			}
		}
		switch (mode) {
		case 1:
			M.choice();
			menuu();
			break;
		case 2:
			cout << "The number of opeations is: " << M.getnum() << '\n';
			menuu();
			break;
		case 3: {
			M.print();
			menuu();
			break;
		}
		case 4: {
			cout << "The last operation is " << M.getlastchoice() << ") " << M.getlastchoice(1.1) << '\n';
			menuu();
			break;
		}
		case 5:
			return 0;
			break;
		}
	}
}