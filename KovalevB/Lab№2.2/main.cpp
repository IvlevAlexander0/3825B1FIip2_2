#include <iostream>
#include <vector>

using std::cin, std::cout;

class Polynom{
    private:
    int degree;
    std::vector <double>v;

    public:
    Polynom(): degree(0), v(1, 0) {
    }
    
    Polynom(int d_): degree(0), v(1,0) {
        SetDegree(d_);
    }

    void SetDegree(int n) {
        if (n < 0 || n > 12) {
            cout << "Error: degree must be in [0, 12]\n";
            return;
        }
        degree = n;
        v.assign(n + 1, 0);
    }

    void SetCoeff() {
        cout << '\n' << "Input coefficents:" << '\n';
        for (int i = 0; i <= degree; ++i) {
            cin >> v[i];
        }
        cout << '\n';
    }

    void DegreeCheck() const {
        cout << "Polynomial degree: " << degree << '\n';
    }

    void CoeffbyNum(int n) const {
        if (n >= 0 && n <= degree) cout << "Coefficient by x^" << n << ": " << v[n] << '\n';
        else cout << "Invalid power" << '\n';
    }
    
    double AtPoint(double x) const {
        double result = v[degree];

        for (int i = degree - 1; i >= 0; --i) {
        result = result * x + v[i];
        }
        return result;
    }

    Polynom Derivative() const{ 
        if (degree == 0) {
            return Polynom();
        }

        Polynom res;    
        res.degree = degree - 1;
        res.v.resize(degree);
        for (int i = 1; i <= degree; ++i) {
            res.v[i - 1] = v[i] * i;
        }

        return res;
    }

    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            degree = other.degree;
            v = other.v;
        }
        return *this;
    }

    // деструктор по факту не нужен, т.к vector сам освобождает память
    ~Polynom() {}

    Polynom(const Polynom& other) : degree(other.degree), v(other.v) {}

    friend std::ostream& operator<<(std::ostream& os, const Polynom& p) {
        // флаг под знак первого элемента
        bool first = true;
        for (int i = p.degree; i >= 0 ; --i) {
            // члены с нулевыми коэффициентами не выводим
            if (p.v[i] == 0) continue;
            double absval = std::abs(p.v[i]);

            // ставим знак при коэффициенте у старшего члена только если он < 0 
            if (!first)
                os << (p.v[i] > 0 ? " + " : " - ");
            else if (p.v[i] < 0)
                os << "-";

            // 1x = x, поэтому единички при иксах не выводим (+ учитываем константу)
            if (absval != 1 || i == 0) os << absval;
            if (i > 0) os << "x";
            if (i > 1) os << "^" << i;

            first = false;
        }
        // если first == 1, значит => не зашли в цикл => полином = 0
        if (first) os << "0";
        return os;
    }
};

// собственно тестирование всего функционала
int main() {
    Polynom zero;
    cout << "Default polynom: " << zero << "\n\n";

    Polynom bad1(-1);   
    Polynom bad2(13);   
    Polynom ok(12);     
    cout << "\n";

    Polynom p;
    p.SetDegree(3);
    p.SetCoeff();
    cout << "p = " << p << "\n";

    p.SetDegree(100);
    cout << "After SetDegree(100), p = " << p << "\n\n";

    p.DegreeCheck();
    p.CoeffbyNum(0);   
    p.CoeffbyNum(3);   
    p.CoeffbyNum(5);   
    cout << "\n";

    cout << "p(0)  = " << p.AtPoint(0)  <<"\n";
    cout << "p(1)  = " << p.AtPoint(1)  <<"\n";
    cout << "p(-1) = " << p.AtPoint(-1) << "\n\n";

    Polynom dp = p.Derivative();
    cout << "p  = " << p  << "\n"; 
    cout << "p' = " << dp << "\n"; 
    cout << "p'' = " << dp.Derivative() << "\n\n";

    Polynom constant;
    constant.SetDegree(0);
    constant.SetCoeff();  
    cout << "constant  = " << constant << "\n";
    cout << "constant' = " << constant.Derivative() << "\n\n";

    Polynom copy1(p);         
    Polynom copy2; copy2 = p; 

    p.SetDegree(1);
    p.SetCoeff();  
    cout << "p = " << p << "\n";
    cout << "copy1 = " << copy1 << "\n";
    cout << "copy2 = " << copy2 << "\n\n";
}