#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
using namespace std;
enum class Method {
	left,right, middle
};
class integralCalculator {
private:
	double (*func)(double);
	double alimit;
	double blimit;
	int N;
	Method method;
public:
	explicit integralCalculator(double (*f)(double) = nullptr, double a = 0.0, double b = 1.0, int  n = 1, Method method_ = Method::left)
		:func(f), alimit(a), blimit(b), N(n), method(method_) {}
	~integralCalculator()=default;
	void setFunction(double (*f)(double)) { 
		func = f;
	}
	void setLimits() { 
		double a, b;
		cin >> a >> b;
		if (a > b) {
			swap(a, b);
		}
	    alimit = a; 
	    blimit = b; 
	}
	void getLimits() const{
		cout << "Limits are:" <<' '<<  alimit << ' ' << blimit << endl;
	}
	void setSegments() {
		int n;
		cin >> n;
		if (n <= 0) {
			throw invalid_argument("Number of segments must be more than 0");
		}
		N = n;
	}
	void setMethod() {
		cout << "Set the method 1-left, 2-right, 3-middle" << endl;
		char choice;
		cin >> choice;
		switch (choice) {
		case '1':
			method = Method::left;
			break;
		case '2':
			method = Method::right;
			break;
		case '3': 
			method = Method::middle;
			break;
		default:
			throw invalid_argument("Incorrect choice");
		}
		cin.ignore();
	}
	double calculate() const {
		if (func == nullptr) {
			throw runtime_error("No funtion setted");
		}
		double h = (blimit - alimit) / N;
		double sum = 0.0;
		switch (method) {
		case Method::left:
			for (int i = 0; i < N; ++i)
				sum += func(alimit + i * h);
			break;
		case Method::right:
			for (int i = 1; i <= N; ++i)
				sum += func(alimit + i * h); // оставил метод в public так как есть такой пункт в задании и теоритически этот метод может пригодиться пользователю
			break;
		case Method::middle:
			for (int i = 0; i < N; ++i)
				sum += func(alimit + (i + 0.5) * h);
			break;
		}
		double result = sum * h;
		return result;
	} 
	void getResult() const {
		double result = calculate();
		cout << "The value is approximately equal to " << setprecision(5) << result << endl;
	}
};
double thirdDegree(double x) { // использовал как пример протому что легко самому посчитать, корректность сверял с подсчетом вручную
	return x * x * x;
}
int main() {
	cout << "Enter '1' to set limits, '2' to set the number of segments, '3' to set method, '4' to get limits or '5' to get the result. Enter '0' if u want to finish. Care: function must be setted before the start!"
		<< endl;
	integralCalculator integral(exp);
	char choice;
	while (1) {
		cin >> choice;
		switch (choice) {
		case '1':
			integral.setLimits();
			break;
		case '2':
			integral.setSegments();
			break;
		case '3':
			integral.setMethod();
			break;
		case '4':
			integral.getLimits();
			break;
		case '5':
			integral.getResult();
			break;
		case '0':
			return 0;
		default:
			throw invalid_argument("incorrect choice");
		}
	}
}