#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>

using namespace std;

bool prov_action(int a) {
    if (a >= 0 && a <= 3) {
        return true;
    }
    else {
        return false;
    }
}

class WeightConverter {
private:
    double kilograms;  

public:
    WeightConverter() {
        kilograms = 0.0;
    }

    WeightConverter(double kg) {
        kilograms = kg;
    }
    void setKilograms(double kg) {
        kilograms = kg;
    }

    double getKilograms() {
        return kilograms;
    }

    double getPharmacyPounds() {
        return kilograms * 2.679;
    }

    double getPoods() {
        return kilograms / 16.38;
    }

    void print() {
        cout << fixed << setprecision(3);
        cout << "Weight: " << kilograms << " kg" << '\n';
        cout << "In pharmacy pounds: " << getPharmacyPounds() << " lb" << '\n';
        cout << "In poods: " << getPoods() << " pood" << '\n';
    }
};

int main() {
    int a;
    double kg;
    WeightConverter weight; 

    cout << "=== WEIGHT CONVERTER ===\n";
    cout << "(Pharmacy pounds and poods)\n\n";

    do {
        cout << "Menu:\n";
        cout << "1. Set weight in kilograms\n";
        cout << "2. Show weight in kilograms\n";
        cout << "3. Show weight in all units\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> a;

        cout << '\n';

        switch (a) {
        case 1:
            cout << "Enter weight in kilograms: ";
            cin >> kg;
            weight.setKilograms(kg);
            cout << "Weight set successfully!\n";
            break;

        case 2:
            cout << "Weight in kilograms: " << weight.getKilograms() << " kg\n";
            break;

        case 3:
            weight.print();
            break;

        case 0:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Wrong choice! Please select 0-3.\n";
        }

        cout << '\n';
    } while (a != 0);

    return 0;
}