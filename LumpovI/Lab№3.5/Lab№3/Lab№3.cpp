#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

class Dictionary {
private:
    std::vector<char*> eng;
    std::vector<char*> rus;

    int EngInd(char* word) {
        for (size_t i = 0; i < eng.size(); i++)
            if (strcmp(eng[i], word) == 0) return i;
        return -1;
    }

    int RusInd(char* word) {
        for (size_t i = 0; i < rus.size(); i++)
            if (strcmp(rus[i], word) == 0) return i;
        return -1;
    }

public:
    Dictionary() {}

    ~Dictionary() {
        for (size_t i = 0; i < eng.size(); i++) {
            delete[] eng[i];
            delete[] rus[i];
        }
        eng.clear();
        rus.clear();
    }

    void add() {
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

        char* newEng = new char[strlen(en) + 1];
        char* newRus = new char[strlen(ru) + 1];
        strcpy(newEng, en);
        strcpy(newRus, ru);

        eng.push_back(newEng);
        rus.push_back(newRus);

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

        delete[] rus[i];
        char newRus[500];
        std::cin >> newRus;
        rus[i] = new char[strlen(newRus) + 1];
        strcpy(rus[i], newRus);

        std::cout << "Translation was updated\n" << "\n";
    }

    void EngToRus() {
        std::cin.ignore();
        char text[500];

        std::cout << "Text: "; std::cin.getline(text, 500);
        char* start = text;

        for (int i = 0; i <= (int)strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (start != &text[i]) {
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
                        if (ans == 'y') {
                            char* newEng = new char[strlen(start) + 1];
                            strcpy(newEng, start);
                            eng.push_back(newEng);

                            char newRus[500];
                            std::cout << "Translation: "; std::cin >> newRus;
                            char* newRusStr = new char[strlen(newRus) + 1];
                            strcpy(newRusStr, newRus);
                            rus.push_back(newRusStr);

                            std::cout << "The word was added\n" << "\n";
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

        for (int i = 0; i <= (int)strlen(text); i++) {
            if (text[i] == ' ' || text[i] == '.' || text[i] == ',' || text[i] == '!' || text[i] == '?' || text[i] == '\0') {
                if (start != &text[i]) {
                    char old = text[i];
                    text[i] = '\0';

                    int idx = RusInd(start);
                    if (idx != -1) {
                        std::cout << eng[idx] << " ";
                    }
                    else {
                        std::cout << "Word [" << start << "] doesn't exist in dictionary. ";
                        std::cout << "Do you want to add this word? (y/n): ";
                        char ans; std::cin >> ans;
                        if (ans == 'y') {
                            char* newRus = new char[strlen(start) + 1];
                            strcpy(newRus, start);
                            rus.push_back(newRus);

                            char newEng[500];
                            std::cout << "Translation: "; std::cin >> newEng;
                            char* newEngStr = new char[strlen(newEng) + 1];
                            strcpy(newEngStr, newEng);
                            eng.push_back(newEngStr);

                            std::cout << "The word was added\n" << "\n";
                        }
                    }
                    text[i] = old;
                    start = &text[i + 1];
                }
            }
        }
        std::cout << std::endl;
    }

    void showCount() const {
        std::cout << "Words: " << eng.size() << std::endl << "\n";
    }

    void save() const {
        char name[100];
        std::cout << "Filename: ";
        std::cin >> name;
        std::ofstream f(name);
        f << eng.size() << std::endl;
        for (size_t i = 0; i < eng.size(); i++)
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

        for (size_t i = 0; i < eng.size(); i++) {
            delete[] eng[i];
            delete[] rus[i];
        }
        eng.clear();
        rus.clear();

        size_t n;
        f >> n;
        for (size_t i = 0; i < n; i++) {
            char tempEng[500], tempRus[500];
            f >> tempEng >> tempRus;

            char* newEng = new char[strlen(tempEng) + 1];
            char* newRus = new char[strlen(tempRus) + 1];
            strcpy(newEng, tempEng);
            strcpy(newRus, tempRus);

            eng.push_back(newEng);
            rus.push_back(newRus);
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