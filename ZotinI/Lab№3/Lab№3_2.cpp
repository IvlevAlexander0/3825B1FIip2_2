#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <cctype>

using std::cout;
using std::cin;
using std::string;

class Customfunc {
private:
    string expr;
    double x;
    size_t pos;
    bool matherror;
    string errormsg;

    void spaces() {
        while (pos < expr.length() && isspace(expr[pos])) {
            pos++;
        }
    }

    double get_number() {
        spaces();
        string num;
        while (pos < expr.length() && (isdigit(expr[pos]) || expr[pos] == '.')) {
            num += expr[pos];
            pos++;
        }
        if (!num.empty()) {
            return std::stod(num);
        }
        return 0;
    }

    double get_function() {
        spaces();
        string funcs[] = { "sin", "cos", "tan", "exp", "log", "sqrt", "abs" };

        for (int i = 0; i < 7; ++i) {
            if (expr.substr(pos, funcs[i].length()) == funcs[i]) {
                pos += funcs[i].length();
                spaces();

                if (pos >= expr.length() || expr[pos] != '(') {
                    matherror = true;
                    errormsg = "Invalid function syntax";
                    return 0;
                }
                pos++;
                spaces();

                double arg = expression();
                spaces();

                if (pos >= expr.length() || expr[pos] != ')') {
                    matherror = true;
                    errormsg = "Invalid function syntax";
                    return 0;
                }
                pos++;

                if (funcs[i] == "sin") {
                    return std::sin(arg);
                }
                if (funcs[i] == "cos") {
                    return std::cos(arg);
                }
                if (funcs[i] == "tan") {
                    return std::tan(arg);
                }
                if (funcs[i] == "exp") {
                    return std::exp(arg);
                }
                if (funcs[i] == "log") {
                    if (arg <= 0) {
                        matherror = true;
                        errormsg = "Invalid expression";
                        return 0;
                    }
                    return std::log(arg);
                }
                if (funcs[i] == "sqrt") {
                    if (arg < 0) {
                        matherror = true;
                        errormsg = "Invalid expression";
                        return 0;
                    }
                    return std::sqrt(arg);
                }
                if (funcs[i] == "abs") {
                    return std::abs(arg);
                }
            }
        }
        return 0;
    }

    double get_primary() {
        spaces();

        if (pos >= expr.length()) {
            return 0;
        }

        if (expr[pos] == '(') {
            pos++;
            double result = expression();
            spaces();
            if (pos < expr.length() && expr[pos] == ')') {
                pos++;
            }
            else {
                matherror = true;
                errormsg = "Invalid expression";
                return 0;
            }
            return result;
        }

        if (expr[pos] == 'x') {
            pos++;
            return x;
        }

        size_t saved_pos = pos;
        double num = get_number();
        if (saved_pos != pos) { 
            return num;
        }

        double func_result = get_function();
        if (func_result != 0 || matherror) {
            return func_result;
        }

        if (pos < expr.length() && !isspace(expr[pos])) {
            matherror = true;
            errormsg = "Invalid expression";
            return 0;
        }

        return 0;
    }

    double expression() {
        spaces();
        double result = get_primary();
        spaces();

        while (pos < expr.length() && !matherror) {
            char op = expr[pos];
            if (op == '+' || op == '-') {
                pos++;
                double term = get_primary();
                spaces();
                if (op == '+') {
                    result += term;
                }
                else {
                    result -= term;
                }
            }
            else if (op == '*' || op == '/') {
                pos++;
                double factor = get_primary();
                spaces();
                if (op == '*') {
                    result *= factor;
                }
                else if (op == '/') {
                    if (factor == 0) {
                        matherror = true;
                        errormsg = "Invalid expression";
                        return 0;
                    }
                    result /= factor;
                }
            }
            else {
                break;
            }
        }
        return result;
    }

public:
    Customfunc() : matherror(false), pos(0) {}

    double evaluate(const string& expres, double x_val) {
        expr = expres;
        x = x_val;
        pos = 0;
        matherror = false;
        errormsg = "";

        double result = expression();

        if (matherror) {
            return 0;
        }

        spaces();
        if (pos < expr.length()) {
            matherror = true;
            errormsg = "Invalid expression";
            return 0;
        }

        if (std::isnan(result) || std::isinf(result)) {
            matherror = true;
            errormsg = "Invalid expression";
            return 0;
        }
        return result;
    }

    bool error() const {
        return matherror;
    }

    string errormassage() const {
        return errormsg;
    }

    bool validate_expression(const string& expres) {
        expr = expres;
        x = 0;
        pos = 0;
        matherror = false;
        errormsg = "";

        double result = expression();

        spaces();
        if (pos < expr.length() && !matherror) {
            return false;
        }

        return !matherror;
    }
};

class Tab {
private:
    size_t count;
    double a, b;
    double* res;
    bool wastabulation;
    double st, cur;
    string customExpr;
    Customfunc calculator;

    bool truecount(size_t c) const {
        return c >= 1;
    }

    void step_start() {
        if (count != 1) {
            st = (b - a) / (count - 1);
        }
        else {
            st = 0;
        }
        cur = a;
    }

public:
    Tab(size_t c = 5, double a1 = 10.0, double b1 = 20.0) : res(nullptr), wastabulation(false), customExpr("") {
        if (truecount(c)) {
            count = c;
        }
        else {
            count = 5;
        }

        res = new double[count];

        if (a1 < b1) {
            a = a1;
            b = b1;
        }
        else {
            b = a1;
            a = b1;
        }
        step_start();
    }

    Tab(const Tab& other) : count(other.count), a(other.a), b(other.b), st(other.st), customExpr(other.customExpr), wastabulation(other.wastabulation), res(nullptr) {
        res = new double[count];
        for (size_t i = 0; i < count; ++i) {
            res[i] = other.res[i];
        }
    }

    Tab& operator=(const Tab& other) {
        if (this != &other) {
            delete[] res;

            count = other.count;
            res = new double[count];
            a = other.a;
            b = other.b;
            st = other.st;
            customExpr = other.customExpr;
            wastabulation = other.wastabulation;
            for (size_t i = 0; i < count; ++i) {
                res[i] = other.res[i];
            }
        }
        return *this;
    }

    void set_func() {
        cout << "\nEnter your function f(x)\n";
        cout << "Examples: x*x, sin(x), 2*x+log(x), exp(-x)*cos(x)\n";
        cout << "Your function: ";
        cin.ignore();
        std::getline(cin, customExpr);

        if (customExpr.empty()) {
            cout << "Using default: x\n";
            customExpr = "x";
        }
        Customfunc validator;
        if (!validator.validate_expression(customExpr)) {
            cout << "Error: Invalid function syntax\n";
            cout << "Function not set. Please try again.\n";
            return;
        }

        wastabulation = false;
        cout << "Function set to: f(x) = " << customExpr << "\n";
    }

    void set_count() {
        cout << "Enter the number of tabulation points: ";
        size_t c;
        do {
            cin >> c;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Input error! Enter a number (>=1): ";
            }
        } while (!truecount(c));

        count = c;
        double* nres = new double[c];
        delete[] res;
        res = nres;

        step_start();
        cout << "Number of points set to " << count << "\n";
    }

    void print_count() const {
        cout << "Current number of points: " << count << '\n';
    }

    void set_otr() {
        double a1, b1;
        cout << "Enter start of tabulation: ";
        cin >> a1;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input error.\n";
            return;
        }

        cout << "Enter end of tabulation: ";
        cin >> b1;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input error.\n";
            return;
        }

        if (a1 < b1) {
            a = a1;
            b = b1;
        }
        else {
            b = a1;
            a = b1;
        }

        step_start();
    }

    void print_otr() const {
        cout << "Start of tabulation: " << a << '\n';
        cout << "End of tabulation: " << b << '\n';
    }

    void tabulation() {
        if (customExpr.empty()) {
            cout << "Function is not set\n";
            return;
        }

        bool haserrors = false;
        int errorcount = 0;
        double x = a;

        cout << "Tabulating f(x) = " << customExpr << "\n";

        for (size_t i = 0; i < count; ++i) {
            Customfunc tempCalc;
            res[i] = tempCalc.evaluate(customExpr, x);

            if (tempCalc.error()) {
                haserrors = true;
                errorcount++;
                res[i] = NAN;
            }

            x += st;
        }

        if (!haserrors) {
            cout << "Tabulation completed successfully.\n";
        }
        else {
            cout << "Tabulation completed with " << errorcount << " error(s).\n";
        }

        wastabulation = true;
    }

    void print_tabulation() const {
        if (res == nullptr || !wastabulation) {
            cout << "No results\n";
        }
        else {
            cout << "\n========================================\n";
            cout << "f(x) = " << customExpr << "\n";
            cout << "========================================\n";
            cout << "    x        |        f(x)\n";
            cout << "----------------------------------------\n";

            double x = a;
            int errorCount = 0;

            for (size_t i = 0; i < count; ++i) {
                cout.precision(6);
                cout << std::fixed;
                cout.width(12); cout << std::right << x << " | ";

                if (std::isnan(res[i])) {
                    cout.width(12); cout << std::right << "undefined";
                    errorCount++;
                }
                else if (std::isinf(res[i])) {
                    cout.width(12); cout << std::right << "infinity";
                    errorCount++;
                }
                else {
                    cout.width(12); cout << std::right << res[i];
                }
                cout << '\n';
                x += st;
            }
            cout << "========================================\n";

            if (errorCount > 0) {
                cout << "Note: " << errorCount << " point(s) had errors\n";
            }
        }
    }

    void savetofile(const string& name, bool append = true) {
        if (res == nullptr || !wastabulation) {
            cout << "No results to save.\n";
            return;
        }

        std::ofstream file;
        if (append) {
            file.open(name, std::ios::app);
        }
        else {
            file.open(name);
        }

        if (file.is_open()) {
            if (append) {
                file << "\n========================================\n";
                file << "New tabulation results:\n";
            }

            file << "f(x) = " << customExpr << "\n";
            file << "========================================\n";
            file << "    x        |        f(x)\n";
            file << "----------------------------------------\n";

            double x = a;
            for (size_t i = 0; i < count; ++i) {
                file.precision(6);
                file << std::fixed;
                file.width(12); file << std::right << x << " | ";

                if (std::isnan(res[i])) {
                    file.width(12); file << std::right << "undefined";
                }
                else if (std::isinf(res[i])) {
                    file.width(12); file << std::right << "infinity";
                }
                else {
                    file.width(12); file << std::right << res[i];
                }
                file << '\n';
                x += st;
            }
            file << "========================================\n";
            file.close();

            cout << "Results saved to " << name << "\n";
        }
        else {
            cout << "File opening error\n";
        }
    }

    ~Tab() {
        delete[] res;
    }
};

int main() {
    size_t s;
    Tab t;

    do {
        cout << "\n---Function tabulator---\n";
        cout << "1. set the current function\n";
        cout << "2. set the current number of tabulation points\n";
        cout << "3. find out the current number of tabulation points\n";
        cout << "4. set a tabulation segment\n";
        cout << "5. find out the tabulation segment\n";
        cout << "6. perform tabulation of the function\n";
        cout << "7. output tabulation results\n";
        cout << "8. save tabulation results to a file\n";
        cout << "0. exit\n";
        cout << "Choice: ";

        cin >> s;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (s) {
        case 1:
            t.set_func();
            break;
        case 2:
            t.set_count();
            break;
        case 3:
            t.print_count();
            break;
        case 4:
            t.set_otr();
            break;
        case 5:
            t.print_otr();
            break;
        case 6:
            t.tabulation();
            break;
        case 7:
            t.print_tabulation();
            break;
        case 8: {
            cout << "Choose whether you want to rewrite(0) or add (1) to the file." << '\n';
            size_t k;
            do {
                cin >> k;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }
            } while (k != 1 && k != 0);
            if (k == 0) {
                t.savetofile("Tab.txt", false);
            }
            else {
                t.savetofile("Tab.txt", true);
            }
            break;
        }
        case 0:
            break;
        default:
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (s != 0);

    return 0;
}
