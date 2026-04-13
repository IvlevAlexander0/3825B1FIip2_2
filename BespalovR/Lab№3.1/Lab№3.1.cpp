/*3.1. Ряд Тейлора
Разработать класс Ряд Тейлора.
Класс должен формировать ряд Тейлора для выбранной функции из списка поддерживаемых с
заданным числом членов ряда в точке разложения 0 (ряд Маклорена). Минимальный список
функций: arcsin(x), arccos(x), ln(1+x) и одна любая на выбор.
Класс должен содержать необходимые служебные методы (конструкторы, деструктор и пр.).
Класс должен предоставлять следующие операции: 1) задать текущую функцию, 2) узнать
текущую функцию, 3) задать текущее число членов ряда, 4) узнать текущее число членов ряда,
5) выдать формулу члена ряда для выбранной функции, 6) выдать формулу и значение
заданного члена ряда в выбранной точке x, 7) рассчитать значение ряда в выбранной точке x
(то есть приближенное значение функции), 8) вывести отклонение значения ряда в выбранной
точке x от эталонного значения текущей функции в данной точке (эталонное значение
вычисляется, используя соответствующую функцию из стандартной библиотеки C++).*/


#define PI 3.141592653589793
#include <iostream>
#include <string>
using std::string;
using std::cout;


//Enum названий функций для читаемости ,
    enum FunctionType {
    ARCSIN,
    ARCCOS,
    LN_1PLUSX,
    SIN
};


//Структура для пункта 6,
struct TermInfo {
    string formula = "";
    double value = 0.0;
};


class TaylorSeries {

private:

    //Выбранная функция,
    FunctionType current_function;

    //Число членов ряда,
    size_t terms_count;

    //Вспомогательный метод вычисления факториала,
    size_t factorial(size_t n) const {
        if (n <= 1) {
            return 1;
        }
        size_t result = 1;
        for (size_t i = 2; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

    //Вспомогательный метод вычисления коэфицента члена ряда,
    double getCoefficient(size_t n) const {

        switch (current_function) {

        case ARCSIN: {
            double numerator = factorial(2 * n);
            double denominator = pow(2, 2 * n) * pow(factorial(n), 2) * (2 * n + 1);
            return numerator / denominator;
        }
        case ARCCOS: {
            double numerator = factorial(2 * n);
            double denominator = pow(2, 2 * n) * pow(factorial(n), 2) * (2 * n + 1);
            return numerator / denominator;
        }
        case LN_1PLUSX:
            return pow( -1, n ) / (n + 1);

        case SIN:
            return pow( -1, n ) / factorial(2 * n + 1);

        default:
            return 0.0;

        }
    }

    //Вспомогательный метод вычисления члена ряда,
    double calculateTerm(size_t n, double x) const {
        double coeff = getCoefficient(n);
        switch (current_function) {

        case ARCSIN:
            if (abs(x) > 1) {
                throw std::out_of_range("Arcsin is defined on [-1;1]");
            }
            return coeff * pow(x, 2 * n + 1);

        case ARCCOS:
            if (abs(x) > 1) {
                throw std::out_of_range("Arccos is defined on [-1;1]");
            }
            return coeff * pow(x, 2 * n + 1);

        case LN_1PLUSX:
            if ( x <= -1 || x > 1) {
                throw std::out_of_range("Ln(1+x) is defined on (-1;1]");
            }
            return coeff * pow(x, n + 1);

        case SIN:
            return coeff * pow(fmod(x,2 * PI), 2 * n + 1);

        default:
            return 0.0;

        }
    }

public:

    //Констркутор (по умолчанию),
    TaylorSeries(FunctionType func = ARCSIN, size_t terms = 1): current_function(func), terms_count(terms) {
        if (terms <= 0) {
            throw std::invalid_argument("Terms count must be positive.");
        }
    }

    //Деструктор ( по умолчанию, массивов нет, у string есть свой деструктор),
    ~TaylorSeries() = default;

    //1) задать текущую функцию,
    void setFunction(FunctionType func) {
        current_function = func;
    }

    //2) узнать текущую функцию,
    FunctionType getFunction() const {
        return current_function;
    }

    //3) задать текущее число членов ряда,
    void setTermsCount(size_t count) {
        if (count > 0) {
            terms_count = count;
        }
        else {
            throw std::invalid_argument("Terms count must be positive.");
        }
    }

    //4) узнать текущее число членов ряда,
    size_t getTermsCount() const {
        return terms_count;
    }

    //5) выдать формулу члена ряда для выбранной функции,
    string getTermFormula() const {
        switch (current_function) {
        case ARCSIN:
            return "((2n)! / (2^(2n) * (n!)^2 * (2n+1))) * x^(2n+1)";
        case ARCCOS:
            return "pi/2 - ((2n)! / (2^(2n) * (n!)^2 * (2n+1))) * x^(2n+1)";
        case LN_1PLUSX:
            return "(-1)^(n+1) * x^n / n";
        case SIN:
            return "(-1)^n * x^(2n+1) / (2n+1)!";
        default:
            return "Unknown function.";
        }
    }

    //6) выдать формулу и значение заданного члена ряда в выбранной точке x,
    TermInfo getTermInfo(size_t n, double x) const {
        TermInfo result;
        result.formula = getTermFormula();
        result.value = calculateTerm(n, x);
        return result;
    }

    //) рассчитать значение ряда в выбранной точке x (то есть приближенное значение функции),
    double calculateSeries(double x) const {
        double result = 0.0;
        for (size_t n = 0; n < terms_count; ++n) {
            result += calculateTerm(n, x);
        }
        if (current_function == ARCCOS) {
            return PI / 2 - result;
        }
        return result;
    }

    //8) вывести отклонение значения ряда в выбранной точке x от эталонного значения текущей функции в данной точке(эталонное значение вычисляется, используя соответствующую функцию из стандартной библиотеки C++).
    double getDeviation(double x) const {
        double series_value = calculateSeries(x);
        double exact_value;
        switch (current_function) {
        case ARCSIN: 
            exact_value = asin(x); 
            break;
        case ARCCOS: 
            exact_value = acos(x); 
            break;
        case LN_1PLUSX: 
            exact_value = log(1 + x); 
            break;
        case SIN: 
            exact_value = sin(x); 
            break;
        default: 
            exact_value = 0.0; 
            break;
        }
        return abs(series_value - exact_value);
    }

};


int main() {
    try {
        TaylorSeries func(SIN, 5);
        cout << func.getDeviation(3.413) << std::endl << func.getTermFormula() << std::endl << func.getTermsCount() << std::endl << func.getFunction() << std::endl << func.calculateSeries(18743.1426) << std::endl;
        func.setFunction(ARCCOS);
        func.setTermsCount(9);
        cout << func.getDeviation(0.782653) << std::endl << func.getTermFormula() << std::endl << func.getTermsCount() << std::endl << func.getFunction() << std::endl << func.calculateSeries(0.1426) << std::endl;
        cout << func.getDeviation(3.413) << std::endl << func.getTermFormula() << std::endl << func.getTermsCount() << std::endl << func.getFunction() << std::endl << func.calculateSeries(18743.1426) << std::endl;
    }
    catch (std::invalid_argument e) {
        cout << "Terms count must be positive.\n";
    }
    catch (std::out_of_range e) {
        cout << "Func is not defined for that x.\n";
    }
    return 0;
}
