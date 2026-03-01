#include <iostream>

using namespace std;

class LongNum {
private:
    // hi, lo - интерпритация верхних и нижних 32 бит соответственно
    unsigned int lo; 
    unsigned int hi; 

    const long long base = 4294967296; // константа 2^32

    __int64 toInt64() const {
        // умножение на base ~ сдвигу на 32 бита влево
        return (__int64)(int)hi * base + (unsigned __int64)lo;
    }

    void fromInt64(__int64 val) {
        // беззнаковое деление даёт правильные биты для отрицательных чисел
        unsigned __int64 uval = (unsigned __int64)val; 
        unsigned __int64 ubase = (unsigned __int64)base;
        lo = (unsigned int)(uval % ubase); 
        hi = (unsigned int)(uval / ubase);
    }

    public:
    LongNum() : lo(0), hi(0) {} 

    LongNum(__int64 val) {
        fromInt64(val);
    }

    LongNum(unsigned int high, unsigned int low): hi(high), lo(low) {}

    // перегрузка всех 5 операторов для работы с LongNum

    LongNum operator+(const LongNum& other) const {
        __int64 result = toInt64() + other.toInt64();
        return LongNum(result);
    }

    LongNum operator-(const LongNum& other) const {
        return LongNum(toInt64() - other.toInt64());
    }

    LongNum operator*(const LongNum& other) const {
        return LongNum(toInt64() * other.toInt64());
    }

    LongNum operator/(const LongNum& other) const {
        return LongNum(toInt64() / other.toInt64());
    }

    LongNum operator%(const LongNum& other) const {
        return LongNum(toInt64() % other.toInt64());
    }

    // перегрузка оператора вывода для объектов класса LongNum
    friend ostream& operator<<(ostream& os, const LongNum& num) {
        os << num.toInt64();
        return os;
    }
};

int main() {
    LongNum Num1(11 * (__int64)1000000000); 
    LongNum Num2(6 * (__int64)1000000000); 

    cout << "Num1 = " << Num1 << '\t' << "Num2 = " << Num2 << '\n' << '\n';
    cout << "Num1 + Num2 = " << (Num1 + Num2) << '\n';
    cout << "Num1 - Num2 = " << (Num1 - Num2) << '\n';
    cout << "Num1 * 2 = " << (Num1 * LongNum(2)) << '\n';
    cout << "Num1 / Num2 = " << (Num1 / Num2) << '\n';
    cout << "Num1 % Num2 = " << (Num1 % Num2) << '\n';
}