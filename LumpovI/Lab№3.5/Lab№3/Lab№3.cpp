#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_WORD = 1000;

class Dictionary {
private:
    char eng[MAX_WORD][500];
    char rus[MAX_WORD][500];
    int count;
    int EngInd(char* word) {
        for (int i = 0; i < count; i++)
            if (strcmp(eng[i], word) == 0) return i;
        return -1;
    }
    int RusInd(char* word) {
        for (int i = 0; i < count; i++)
            if (strcmp(rus[i], word) == 0) return i;
        return -1;
    }
public:
    Dictionary() {
        count = 0;
        for (int i = 0; i < MAX_WORD; ++i) {
            eng[i][0] = '\0';
            rus[i][0] = '\0';
        }
    }

    ~Dictionary(){}

    void add() {
        if (count >= MAX_WORD) {
            std::cout << "Dictionary is full!!!\n" << "\n";
            return;
        }
        char en[500], ru[500];
        std::cout << "Russian: \n";
        std::cin >> ru;
        std::cout << "English: \n";
        std::cin >> en;

        if (EngInd(en) != -1) {
            std::cout << "The word already is in the dictionary\n" << "\n";
            return;
        }
        if (RusInd(ru) != -1) {
            std::cout << "The word already is in the dictionary\n" << "\n";
            return;
        }

        strcpy(rus[count], ru);
        strcpy(eng[count], en);

        count++;
        std::cout << "Pair was added\n" << "\n";
    }
    void change() {
        char en[500];

        std::cout << "English: "; std::cin >> en;
        int i = EngInd(en);
        if (i == -1) {
            std::cout << "The word wasn't found\n" << "\n";
            return;
        }

        std::cout << "New translation: ";
        std::cin >> rus[i];
        std::cout << "Translation was updated\n" << "\n";
    }
    void EngToRus() {
        std::cin.ignore();
        char text[500];

        std::cout << "Text: "; std::cin.getline(text, 500);
        char* start = text;

        for (int i = 0; i <= strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (i > 0 && start != &text[i]) {
                    char old = text[i];
                    text[i] = '\0';

                    int ind = EngInd(start);
                    if (ind != -1) {
                        std::cout << rus[ind] << " ";
                    }
                    else {
                        std::cout << "Word [" << start << "] doesn't exist in dictionary. ";
                        std::cout << "Do you want to add this word? (y/n): ";
                        char ans; std::cin >> ans;
                        if (ans == 'y' && count < MAX_WORD) {
                            strcpy(eng[count], start);
                            std::cout << "Translation: "; std::cin >> rus[count];
                            std::cout << "The word was added\n" << "\n";
                            count++;
                        }
                    }
                    text[i] = old;
                    start = &text[i + 1];
                }
            }
        }

        std::cout << std::endl;
    }
    void RusToEng() {
        std::cin.ignore();
        char text[500];
        std::cout << "Text: "; std::cin.getline(text, 500);
        char* start = text;
        for (int i = 0; i <= strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (i > 0 && start != &text[i]) {
                    char old = text[i];
                    text[i] = '\0';

                    int idx = RusInd(start);
                    if (idx != -1) {
                        std::cout << eng[idx] << " " << "\n";
                    }
                    else {
                        std::cout << "Word [" << start << "] doesn't exist in dictionary. ";
                        std::cout << "Do you want to add this word? (y/n): ";
                        char ans; std::cin >> ans;
                        if (ans == 'y' && count < MAX_WORD) {
                            strcpy(rus[count], start);
                            std::cout << "Translation: "; std::cin >> eng[count];
                            std::cout << "The word was added\n" << "\n";
                            count++;
                        }
                    }
                    text[i] = old;
                    start = &text[i + 1];
                }
            }
        }
        std::cout << std::endl;
    }

    void showCount() const { std::cout << "Words: " << count << std::endl << "\n"; }

    void save() const {
        char name[100];
        std::cout << "Filename: ";
        std::cin >> name;
        std::ofstream f(name);
        f << count << std::endl;
        for (int i = 0; i < count; i++)
            f << eng[i] << " " << rus[i] << std::endl;
        f.close();
        std::cout << "Dictionary was saved in " << name << std::endl << "\n";
    }
    void load() {
        char name[100];
        std::cout << "Filename: ";
        std::cin >> name;
        std::ifstream f(name);
        if (!f) {
            std::cout << "Error\n" << "\n";
            return;
        }
        int n; f >> n;
        count = 0;
        for (int i = 0; i < n && i < MAX_WORD; i++) {
            f >> eng[count] >> rus[count];
            count++;
        }
        f.close();
        std::cout << "New dictionary was loaded from " << name << std::endl << "\n";
    }
};
int main() {
    std::cout << "========== English-Russian Dictionary ==========\n";
    Dictionary d;
    int c;
    do {
        std::cout << " 1.Add word in dictionary\n 2.Change word in dictionary\n 3.English to Russian translate\n 4.Russian to English translate\n 5.Count of words in dictionary\n 6.Save dictionary in file\n 7.Load dictionary from file\n 0.Exit\n";
        std::cout << "Choice: "; std::cin >> c;
        switch (c) {
        case 1:
            d.add();
            break;
        case 2:
            d.change();
            break;
        case 3:
            d.EngToRus();
            break;
        case 4:
            d.RusToEng();
            break;
        case 5:
            d.showCount();
            break;
        case 6:
            d.save();
            break;
        case 7:
            d.load();
            break;
        }
    } while (c != 0);
    return 0;
}