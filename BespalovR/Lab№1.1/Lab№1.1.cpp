//Подключение стандартной библиотеки и пространства имён std.
#include <iostream>
using namespace std;


//Математические функции.(НОД алгоритмом Евклида.)
int gcd(int a, int b) {
	while (b != 0) {
		int t = b;
		b = a % b;
		a = t;
	}
	return a;
}


//Сам класс рационального числа.
class RationalNum {

	//Числитель.
	int numerator;
	//Знаменатель.
	unsigned int denominator;

public:

	//Конструктор + по умолчанию с сокращением числителя и знаменателя.
	RationalNum(int numerator_ = 0, unsigned int denominator_ = 1) {
		if (denominator_ != 0) {
			int t = gcd(abs(numerator_), denominator_);
			numerator = numerator_ / t;
			denominator = denominator_ / t;
		}
		else {
			cout << "ERR: DIV BY 0\n";
		}
	}

	//Арифметические операции (и вывод) через перегрузку оперторов.(Некоторые крайние случаи можно оптимизировать. Например сумму и разность дробей с одинаковыми знаменателями.)
	RationalNum operator + (const RationalNum& rn) const{
		return RationalNum(numerator * rn.denominator + rn.numerator * denominator, denominator * rn.denominator);
	}

	RationalNum operator - (const RationalNum& rn) const{
		return RationalNum(numerator * rn.denominator - rn.numerator * denominator, denominator * rn.denominator);
	}

	RationalNum operator * (const RationalNum& rn) const{
		return RationalNum(numerator * rn.numerator , denominator * rn.denominator);
	}

	RationalNum operator / (const RationalNum& rn) const{
		return RationalNum(numerator * rn.denominator, denominator * rn.numerator);
	}

	//Я забыл как делать перегрузку вывода внутри класса, поэтому через friend.
	friend ostream& operator << (ostream& os, const RationalNum& rn);
};


//Вывод с обработкой целых чисел.
ostream& operator << (ostream& os, const RationalNum &rn) {
	if (abs(rn.numerator) % rn.denominator == 0 ) {
		os << rn.numerator / rn.denominator;
		return os;
	}
	os << rn.numerator << '/' << rn.denominator;
	return os;
	
}


//main. Можно проверить корректность операций и поискать ошибки.
int main() {
	//cout << RationalNum(-3, 5) / RationalNum(0,7) << '\n';

}