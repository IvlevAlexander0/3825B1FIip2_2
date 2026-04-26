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

#define _USE_MATH_DEFINES
#include <iostream>
#include <string>
#include <cmath>
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

public:
    //Констркутор (по умолчанию),
    TaylorSeries(FunctionType func = ARCSIN, size_t terms = 1): current_function(func), terms_count(terms) {
        if (terms <= 0) {
            cout << "Terms count must be positive.(Constr)\n";
        }
    }

    //Деструктор ( по умолчанию, массивов нет, у string есть свой деструктор),
    ~TaylorSeries() = default;

    //1) задать текущую функцию,
    void setFunction(FunctionType func) noexcept {
        current_function = func;
    }

    //2) узнать текущую функцию,
    FunctionType getFunction() const noexcept {
        return current_function;
    }

    //3) задать текущее число членов ряда,
    bool setTermsCount(size_t count) noexcept {
        if (count > 0) {
            terms_count = count;
            return true;
        }
        else {
            cout << "Terms count must be positive.(STC)\n";
            return false;
        }
    }

    //4) узнать текущее число членов ряда,
    size_t getTermsCount() const noexcept {
        return terms_count;
    }

    //5) выдать формулу члена ряда для выбранной функции,
    string getTermFormula() const noexcept {
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
    TermInfo getTermInfo(size_t n, double x) const noexcept {
        TermInfo result;
        result.formula = getTermFormula();
        double term = x;
        for (size_t i = 1; i < n; ++i) {
            term *= getNextTermMultiplier(i, x);
        }
        result.value = term;
        return result;
    }

    //7) рассчитать значение ряда в выбранной точке x, (рекуррентное вычисление)
    double calculateSeries(double x) const noexcept {
        if (terms_count == 0) {
            cout << "Terms count must be positive.(CalcSer)\n";
            return NAN;
        }
        double result = 0.0;
        double term = x;
        result += term;
        for (size_t n = 1; n < terms_count; ++n) {
            term *= getNextTermMultiplier(n, x);  
            if (std::isnan(term)) {
                return NAN;
            }
            result += term;
        }
        if (current_function == ARCCOS) {
            return M_PI / 2 - result;
        }
        return result;
    }

    // Вспомогательный метод для рекуррентного множителя, (term[n] / term[n-1])
    double getNextTermMultiplier(size_t n, double x) const noexcept {
        switch (current_function) {
        case ARCSIN:
        case ARCCOS:
            if (abs(x) > 1) {
                cout << "Arcsin is defined on[-1;1]\n";
                return NAN;
            }
            return (x * x) * (2.0 * n - 1.0) * (2.0 * n - 1.0) / (2.0 * n) / (2.0 * n + 1.0);
        case LN_1PLUSX:
            if (x <= -1 || x > 1) {
                cout << "Ln(1 + x) is defined on(-1;1]\n";
                return NAN;
            }
            return -x * n / (n + 1.0);
        case SIN:
            return -(x * x) / ((2.0 * n) * (2.0 * n + 1.0));
        default:
            return NAN;
        }
    }

    //8) вывести отклонение значения ряда в выбранной точке x от эталонного значения текущей функции в данной точке(эталонное значение вычисляется, используя соответствующую функцию из стандартной библиотеки C++).
    double getDeviation(double x) const noexcept {
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
            exact_value = NAN; 
            break;
        }
        if (std::isnan(abs(series_value - exact_value)) && !(std::isnan(series_value))) {
            cout << "Function doesn't exist for that x.\n";
        }
        return abs(series_value - exact_value);
    }

};


int main() {
    TaylorSeries func(ARCSIN);
    for (size_t i = 1; i < 50; ++i) {
        func.setTermsCount(i);
        cout << func.getDeviation(.82) << std::endl;
    }
    return 0;
}
