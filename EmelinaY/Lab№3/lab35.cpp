#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int MAX = 100;

class Dictionary {
private:
    char eng[MAX][50];
    char rus[MAX][50];
    int count;
    int findEng(char* word) {
        for (int i = 0; i < count; i++)
            if (strcmp(eng[i], word) == 0) return i;
        return -1;
    }
    int findRus(char* word) {
        for (int i = 0; i < count; i++)
            if (strcmp(rus[i], word) == 0) return i;
        return -1;
    }
public:
    Dictionary() {
        count = 0;
        for (int i = 0; i < MAX; i++) {
            eng[i][0] = '\0';
            rus[i][0] = '\0';
        }
    }
    void add() {
        if (count >= MAX) { cout << "Full\n"; return; }
        char e[50], r[50];
        cout << "English: "; cin >> e;
        cout << "Russian: "; cin >> r;
        if (findEng(e) != -1) { cout << "Exists\n"; return; }
        strcpy(eng[count], e);
        strcpy(rus[count], r);
        count++;
        cout << "OK\n";
    }
    void change() {
        char e[50];
        cout << "English: "; cin >> e;
        int i = findEng(e);
        if (i == -1) { cout << "Not found\n"; return; }
        cout << "New translation: "; cin >> rus[i];
        cout << "OK\n";
    }
    void engToRus() {
        cin.ignore();
        char text[500];
        cout << "Text: "; cin.getline(text, 500);
        char* start = text;
        for (int i = 0; i <= strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (i > 0 && start != &text[i]) {
                    char old = text[i];
                    text[i] = '\0';

                    int idx = findEng(start);
                    if (idx != -1) {
                        cout << rus[idx] << " ";
                    }
                    else {
                        cout << "[" << start << "] ";
                        cout << "Add? (y/n): ";
                        char ans; cin >> ans;
                        if (ans == 'y' && count < MAX) {
                            strcpy(eng[count], start);
                            cout << "Translation: "; cin >> rus[count];
                            count++;
                        }
                    }
                    text[i] = old;
                    start = &text[i + 1];
                }
            }
        }

        cout << endl;
    }
    void  rusToEng() {
        cin.ignore();
        char text[500];
        cout << "Text: "; cin.getline(text, 500);
        char* start = text;
        for (int i = 0; i <= strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (i > 0 && start != &text[i]) {
                    char old = text[i];
                    text[i] = '\0';

                    int idx = findRus(start);
                    if (idx != -1) {
                        cout << eng[idx] << " ";
                    }
                    else {
                        cout << "[" << start << "] ";
                        cout << "Add? (y/n): ";
                        char ans; cin >> ans;
                        if (ans == 'y' && count < MAX) {
                            strcpy(rus[count], start);
                            cout << "Translation: "; cin >> eng[count];
                            count++;
                        }
                    }
                    text[i] = old;
                    start = &text[i + 1];
                }
            }
        }
        cout << endl;
    }

    void showCount() { cout << "Words: " << count << endl; }

    void save() {
        char name[100];
        cout << "Filename: "; cin >> name;
        ofstream f(name);
        f << count << endl;
        for (int i = 0; i < count; i++)
            f << eng[i] << " " << rus[i] << endl;
        f.close();
        cout << "Saved\n";
    }
    void load() {
        char name[100];
        cout << "Filename: "; cin >> name;
        ifstream f(name);
        if (!f) { cout << "Error\n"; return; }
        int n; f >> n;
        count = 0;
        for (int i = 0; i < n && i < MAX; i++) {
            f >> eng[count] >> rus[count];
            count++;
        }
        f.close();
        cout << "Loaded\n";
    }
};
int main() {
    Dictionary d;
    int c;
    do {
        cout << "\n1.Add 2.Change 3.Eng->Rus 4.Rus->Eng 5.Count 6.Save 7.Load 0.Exit\n";
        cout << "Choice: "; cin >> c;
        switch (c) {
        case 1: d.add(); break;
        case 2: d.change(); break;
        case 3: d.engToRus(); break;
        case 4: d.rusToEng(); break;
        case 5: d.showCount(); break;
        case 6: d.save(); break;
        case 7: d.load(); break;
        }
    } while (c != 0);
    return 0;
}