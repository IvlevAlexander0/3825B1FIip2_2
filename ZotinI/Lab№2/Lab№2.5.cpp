#include <iostream>
#include <cmath>

using std::cout;
using std::cin;
using std::ostream;


void copy(float* arr, float* arr1, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		arr[i] = arr1[i];
	}
}

class arr {
private:
	size_t n;
	size_t pr;
	bool is_parr = false;
	float* array;
	float* parr;
public:
	arr(size_t k = 6) {
		n = k;
		array = new float[n];
		for (size_t i = 0; i < n; ++i) {
			array[i] = (float)(rand() / (float)RAND_MAX) * 100 + 10;
		}
		pr = ceil(n / 2.0);
		parr = new float[pr];
	}

	arr& operator=(const arr& other) {
		if (this != &other) {
			delete[] array;
			delete[] parr;

			pr = other.pr;
			n = other.n;
			is_parr = other.is_parr;

			array = new float[n];
			copy(array, other.array, n);

			parr = new float[pr];
			if (other.is_parr) {
				copy(parr, other.parr, pr);
			}
		}
		return *this;
	}

	arr(const arr& other) : n(other.n), pr(other.pr), is_parr(other.is_parr) {
		array = new float[n];
		copy(array, other.array, n);

		parr = new float[pr];
		if (is_parr) {
			copy(parr, other.parr, pr);
		}
	}

	void install_size() {
		size_t k;
		do {
			cout << "Enter size:\n";
			cin >> k;
		} while (k < 1 || k > 30);

		float* ar = new float[n];
		copy(ar, array, n);
		delete[] array;

		array = new float[k];
		if (n <= k) {
			copy(array, ar, n);
			for (size_t j = n; j < k; ++j) {
				array[j] = (float)(rand() / (float)RAND_MAX) * 100 + 10;
			}
		}
		else {
			copy(array, ar, k);
		}
		delete[] ar;
		n = k;

		delete[] parr;
		parr = new float[ceil(n / 2.0)];
		is_parr = false;
	}

	void size() {
		cout << "Size of the array: " << n << '\n';
	}

	friend ostream& operator<<(ostream& stream, const arr& a) {
		stream << "Count elements in the array: " << a.n << '\n';
		for (size_t i = 0; i < a.n; ++i) {
			stream << a.array[i] << ' ';
		}
		stream << '\n';
		return stream;
	}

	void zadanie() {
		size_t u;
		do {
			cout << "Enter index:\n";
			cin >> u;
		} while (u < 0 || u >= n);
		float a;
		cout << "Enter number:\n";
		cin >> a;
		array[u] = a;
		cout << "The operation was completed successfully\n";

	}

	void el_index() {
		size_t u;
		do {
			cout << "Enter index:\n";
			cin >> u;
		} while (u < 0 || u >= n);
		cout << "The element by index: " << array[u] << '\n';
	}

	void min() {
		float m = array[0];
		for (size_t k = 1; k < n; ++k) {
			if (m > array[k]) {
				m = array[k];
			}
		}
		cout << "Minimal element: " << m << '\n';
	}


	void is_sort() {
		bool fl = false;
		for (size_t i = 0; i < n - 1; ++i) {
			if (array[i] > array[i + 1]) {
				cout << "The array is unordered\n";
				fl = true;
				break;
			}
		}
		if (!fl) {
			cout << "The array is ordered\n";
		}
	}

	void podarr() {
		size_t l = 0;
		is_parr = true;
		cout << "Elements at odd indexes: ";
		for (size_t k = 0; k < n; ++k) {
			if (k % 2 != 0) {
				parr[l] = array[k];
				cout << parr[l] << ' ';
				l++;
			}
		}
		cout << '\n';
	}

	~arr() {
		delete[] array;
		delete[] parr;
	}

};

int main() {
	srand(time(nullptr));
	int c;
	arr a;
	do {
		cout << "Choice operation: \n1. set the size of the array\n" <<
			"2. find out the size of the array\n" <<
			"3. set the element of the array by its index\n" << "4. find out the element of the array by its index\n" <<
			"5. find the minimum element of the array\n" << "6. check whether the array is ordered\n" <<
			"7. select from the array an array with elements with odd indexes\n" << "8. Print array\n" << "0. exit\n";
		cin >> c;

		switch (c) {
		case 1:
			a.install_size();
			break;
		case 2:
			a.size();
			break;
		case 3:
			a.zadanie();
			break;
		case 4:
			a.el_index();
			break;
		case 5:
			a.min();
			break;
		case 6:
			a.is_sort();
			break;
		case 7:
			a.podarr();
			break;
		case 8:
			cout << a;
			break;
		case 0:
			break;
		default:
			cout << "Input error. Enter number from 0 to 7\n";
			break;
		}

		cout << '\n';
	} while (c != 0);

	return 0;
}