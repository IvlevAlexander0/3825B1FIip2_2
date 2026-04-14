#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;

class UserMenu {
private:
    int numCommands;
    vector<string> commandNames;
    vector<function<double(double)>> functions;
    int lastSelectedCommand;

public:
    UserMenu() : numCommands(0), lastSelectedCommand(-1) {}

    UserMenu(int n) : numCommands(n), lastSelectedCommand(-1) {
        if (n > 0) {
            commandNames.resize(n);
            functions.resize(n);
        }
    }

    ~UserMenu() {}

    void setNumCommands(int n) {
        if (n > 0) {
            numCommands = n;
            commandNames.resize(n);
            functions.resize(n);
        }
        else {
            cout << "Error. The number of commands must be positive" << endl;
        }
    }

    int getNumCommands() const {
        return numCommands;
    }

    void setCommand(int index, const string& name, function<double(double)> func) {
        if (index >= 1 && index <= numCommands) {
            commandNames[index - 1] = name;
            functions[index - 1] = func;
        }
        else {
            cout << "Error. Invalid command number (1-" << numCommands << ")" << endl;
        }
    }

    void display() const {
        if (numCommands == 0) {
            cout << "The menu is empty" << endl;
            return;
        }

        cout << "Menu" << endl;
        for (int i = 0; i < numCommands; i++) {
            cout << i + 1 << ". ";
            if (commandNames[i].empty()) {
                cout << "Not specified";
            }
            else {
                cout << commandNames[i];
            }
            cout << endl;
        }
    }

    void executeCommand() {
        if (numCommands == 0) {
            cout << "Error. The menu does not contain commands" << endl;
            return;
        }

        int choice;
        cout << "Select a menu item (1-" << numCommands << "):\n";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > numCommands) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Wrong choice" << endl;
            return;
        }

        lastSelectedCommand = choice;
        int index = choice - 1;
        if (commandNames[index].empty()) {
            cout << "Error. Command " << choice << " not specified" << endl;
            return;
        }

        if (functions[index] == nullptr) {
            cout << "Error. For the command " << choice << " the function is not set" << endl;
            return;
        }

        cout << "Command selected: " << commandNames[index] << endl;

        double x;
        cout << "Enter the argument (type double):\n";
        cin >> x;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Incorrect number input" << endl;
            return;
        }

        try {
            double result = functions[index](x);
            cout << "Result: " << result << endl;
        }
        catch (...) {
            cout << "Error when executing the function" << endl;
        }
    }

    int getLastSelectedCommand() const {
        if (lastSelectedCommand == -1) {
            cout << "There have been no selections yet" << endl;
        }
        return lastSelectedCommand;
    }
};

double square(double x) {
    return x * x;
}

double cube(double x) {
    return x * x * x;
}

int main() {

    UserMenu menu(3);

    menu.setCommand(1, "The square of a number", square);
    menu.setCommand(2, "The cube of a number", cube);
    menu.setCommand(3, "The sine of the angle (in degrees)", [](double x) {
        return sin(x * 3.141592653589793 / 180.0);
        });

    menu.display();

    char continueChoice;
    do {
        menu.executeCommand();

        int last = menu.getLastSelectedCommand();
        if (last != -1) {
            cout << "The number of the last selected item: " << last << endl;
        }

        cout << "Continue working? (y/n):\n";
        cin >> continueChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl;

    } while (continueChoice == 'y' || continueChoice == 'Y');

    return 0;
}
