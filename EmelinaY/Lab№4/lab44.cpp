#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;
const int M = 50;
struct datka {
    int d, m, g;
};

struct abon {
    char fam[30];
    char im[30];
    char otch[30];
    char tel[15];
    datka dr;
    int lubim;
};
class Telef {
private:
    abon kniga[M];
    int kol;
    int poiskpoFIO(char f[], char i[], char o[]) {
        for (int v = 0; v < kol; v++)
            if (strcmp(kniga[v].fam, f) == 0 &&
                strcmp(kniga[v].im, i) == 0 &&
                strcmp(kniga[v].otch, o) == 0)
                return v;
        return -1;
    }

    bool sravni(abon a, abon b) {
        if (strcmp(a.fam, b.fam) != 0)
            return strcmp(a.fam, b.fam) > 0;
        if (strcmp(a.im, b.im) != 0)
            return strcmp(a.im, b.im) > 0;
        return strcmp(a.otch, b.otch) > 0;
    }

    void sortirovka() {
        for (int i = 1; i < kol; i++) {
            abon kl = kniga[i];
            int j = i - 1;
            while (j >= 0 && sravni(kniga[j], kl)) {
                kniga[j + 1] = kniga[j];
                j--;
            }
            kniga[j + 1] = kl;
        }
    }
    bool proverkaDaty(int d, int m, int g) {
        if (g < 1900 || g > 2026) return false;
        if (m < 1 || m > 12) return false;

        int dniVMesyace[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((g % 4 == 0 && g % 100 != 0) || (g % 400 == 0))
            dniVMesyace[1] = 29;

        if (d < 1 || d > dniVMesyace[m - 1]) return false;

        return true;
    }
    bool proverkaStroki(char str[]) {
        return strlen(str) > 0;
    }

public:
    Telef() {
        kol = 0;
        cout << "Phone book created\n";
    }
    ~Telef() {
        cout << "Program finished\n";
    }

    void dobavit() {
        if (kol >= M) {
            cout << "Phone book is full\n";
            return;
        }

        abon x;
        do {
            cout << "Last name: "; cin >> x.fam;
            if (!proverkaStroki(x.fam))
                cout << "Last name cannot be empty!\n";
        } while (!proverkaStroki(x.fam));

        do {
            cout << "First name: "; cin >> x.im;
            if (!proverkaStroki(x.im))
                cout << "First name cannot be empty!\n";
        } while (!proverkaStroki(x.im));

        do {
            cout << "Patronymic: "; cin >> x.otch;
            if (!proverkaStroki(x.otch))
                cout << "Patronymic cannot be empty!\n";
        } while (!proverkaStroki(x.otch));

        if (poiskpoFIO(x.fam, x.im, x.otch) != -1) {
            cout << "Contact with this full name already exists\n";
            return;
        }
        cout << "Phone: "; cin >> x.tel;

        do {
            cout << "Birth date (day month year): ";
            cin >> x.dr.d >> x.dr.m >> x.dr.g;
            if (!proverkaDaty(x.dr.d, x.dr.m, x.dr.g))
                cout << "Invalid date! Try again.\n";
        } while (!proverkaDaty(x.dr.d, x.dr.m, x.dr.g));

        x.lubim = 0;

        kniga[kol] = x;
        kol++;
        sortirovka();
        cout << "Contact added\n";
    }
    void izmenit() {
        char f[30], i[30], o[30];
        cout << "Enter full name of contact to edit:\n";
        cout << "Last name: "; cin >> f;
        cout << "First name: "; cin >> i;
        cout << "Patronymic: "; cin >> o;

        int idx = poiskpoFIO(f, i, o);
        if (idx == -1) {
            cout << "Contact not found\n";
            return;
        }

        cout << "\n--- Editing contact ---\n";
        cout << "Current data:\n";
        cout << "Full name: " << kniga[idx].fam << " " << kniga[idx].im << " " << kniga[idx].otch << endl;
        cout << "Phone: " << kniga[idx].tel << endl;
        cout << "Birth date: " << kniga[idx].dr.d << "." << kniga[idx].dr.m << "." << kniga[idx].dr.g << endl;

        int vibor;
        bool izmeneno = false;
        abon novye = kniga[idx];

        do {
            cout << "\nWhat to edit?\n";
            cout << "1. Last name\n";
            cout << "2. First name\n";
            cout << "3. Patronymic\n";
            cout << "4. Phone\n";
            cout << "5. Birth date\n";
            cout << "0. Finish editing\n";
            cout << "-> ";
            cin >> vibor;
            switch (vibor) {
            case 1:
                do {
                    cout << "New last name: "; cin >> novye.fam;
                    if (!proverkaStroki(novye.fam))
                        cout << "Last name cannot be empty!\n";
                } while (!proverkaStroki(novye.fam));
                izmeneno = true;
                break;
            case 2:
                do {
                    cout << "New first name: "; cin >> novye.im;
                    if (!proverkaStroki(novye.im))
                        cout << "First name cannot be empty!\n";
                } while (!proverkaStroki(novye.im));
                izmeneno = true;
                break;
            case 3:
                do {
                    cout << "New patronymic: "; cin >> novye.otch;
                    if (!proverkaStroki(novye.otch))
                        cout << "Patronymic cannot be empty!\n";
                } while (!proverkaStroki(novye.otch));
                izmeneno = true;
                break;
            case 4:
                cout << "New phone: "; cin >> novye.tel;
                izmeneno = true;
                break;
            case 5:
                do {
                    cout << "New birth date (day month year): ";
                    cin >> novye.dr.d >> novye.dr.m >> novye.dr.g;
                    if (!proverkaDaty(novye.dr.d, novye.dr.m, novye.dr.g))
                        cout << "Invalid date!\n";
                } while (!proverkaDaty(novye.dr.d, novye.dr.m, novye.dr.g));
                izmeneno = true;
                break;
            }
        } while (vibor != 0);
        if (izmeneno) {
            if (strcmp(novye.fam, kniga[idx].fam) != 0 ||
                strcmp(novye.im, kniga[idx].im) != 0 ||
                strcmp(novye.otch, kniga[idx].otch) != 0) {

                int exist = poiskpoFIO(novye.fam, novye.im, novye.otch);
                if (exist != -1 && exist != idx) {
                    cout << "Contact with this full name already exists! Edit cancelled.\n";
                    return;
                }
            }

            kniga[idx] = novye;
            sortirovka();
            cout << "Contact edited\n";
        }
        else {
            cout << "No changes made\n";
        }
    }
    void naytipoFIO() {
        char f[30], i[30], o[30];
        cout << "Last name: "; cin >> f;
        cout << "First name: "; cin >> i;
        cout << "Patronymic: "; cin >> o;

        int idx = poiskpoFIO(f, i, o);
        if (idx == -1)
            cout << "Contact not found\n";
        else {
            cout << "Phone: " << kniga[idx].tel << endl;
            cout << "Birth date: " << kniga[idx].dr.d << "." << kniga[idx].dr.m << "." << kniga[idx].dr.g << endl;
            if (kniga[idx].lubim)
                cout << "In favorites\n";
        }
    }
    void naytipotel() {
        char t[15];
        cout << "Phone: "; cin >> t;

        for (int i = 0; i < kol; i++)
            if (strcmp(kniga[i].tel, t) == 0) {
                cout << "Found: " << kniga[i].fam << " " << kniga[i].im << " " << kniga[i].otch << endl;
                return;
            }
        cout << "Contact with this phone not found\n";
    }
    void pobukve() {
        char b;
        cout << "Enter letter: "; cin >> b;
        b = tolower(b);

        int n = 0;
        for (int i = 0; i < kol; i++) {
            char perv = tolower(kniga[i].fam[0]);
            if (perv == b) {
                cout << kniga[i].fam << " " << kniga[i].im << " " << kniga[i].otch << endl;
                n = 1;
            }
        }
        if (!n) cout << "No contacts starting with this letter\n";
    }
    void skolko() {
        cout << "Total contacts: " << kol << endl;
    }
    void vlubimoe() {
        char f[30], i[30], o[30];
        cout << "Last name: "; cin >> f;
        cout << "First name: "; cin >> i;
        cout << "Patronymic: "; cin >> o;

        int idx = poiskpoFIO(f, i, o);
        if (idx == -1)
            cout << "Contact not found\n";
        else {
            kniga[idx].lubim = 1;
            cout << "Contact added to favorites\n";
        }
    }
    void izlubimogo() {
        char f[30], i[30], o[30];
        cout << "Last name: "; cin >> f;
        cout << "First name: "; cin >> i;
        cout << "Patronymic: "; cin >> o;

        int idx = poiskpoFIO(f, i, o);
        if (idx == -1)
            cout << "Contact not found\n";
        else {
            kniga[idx].lubim = 0;
            cout << "Contact removed from favorites\n";
        }
    }
    void pokazatlubim() {
        int n = 0;
        for (int i = 0; i < kol; i++)
            if (kniga[i].lubim == 1) {
                cout << kniga[i].fam << " " << kniga[i].im << " " << kniga[i].otch << " - " << kniga[i].tel << endl;
                n = 1;
            }
        if (!n) cout << "No favorite contacts\n";
    }
    void udalit() {
        char f[30], i[30], o[30];
        cout << "Last name: "; cin >> f;
        cout << "First name: "; cin >> i;
        cout << "Patronymic: "; cin >> o;

        int idx = poiskpoFIO(f, i, o);
        if (idx == -1)
            cout << "Contact not found\n";
        else {
            for (int j = idx; j < kol - 1; j++)
                kniga[j] = kniga[j + 1];
            kol--;
            cout << "Contact deleted\n";
        }
    }
    void save() {
        char name[100];
        cout << "File name: "; cin >> name;

        ofstream f(name);
        if (!f) {
            cout << "Error creating file\n";
            return;
        }

        f << kol << endl;
        for (int i = 0; i < kol; i++) {
            f << kniga[i].fam << "|" << kniga[i].im << "|" << kniga[i].otch << "|"
                << kniga[i].tel << "|" << kniga[i].dr.d << "|" << kniga[i].dr.m << "|"
                << kniga[i].dr.g << "|" << kniga[i].lubim << endl;
        }
        f.close();
        cout << "Data saved to file " << name << endl;
    }

    void load() {
        char name[100];
        cout << "File name: "; cin >> name;

        ifstream f(name);
        if (!f) {
            cout << "Error opening file\n";
            return;
        }

        int n;
        f >> n;

        if (n < 0 || n > M) {
            cout << "Invalid file\n";
            f.close();
            return;
        }
        kol = 0;
        char buf[300];
        f.getline(buf, 300);
        for (int i = 0; i < n && i < M; i++) {
            abon x;
            f.getline(buf, 300);

            char* p = strtok(buf, "|");
            if (p) strcpy(x.fam, p); else continue;
            p = strtok(NULL, "|");
            if (p) strcpy(x.im, p); else continue;
            p = strtok(NULL, "|");
            if (p) strcpy(x.otch, p); else continue;
            p = strtok(NULL, "|");
            if (p) strcpy(x.tel, p); else continue;
            p = strtok(NULL, "|");
            if (p) x.dr.d = atoi(p); else continue;
            p = strtok(NULL, "|");
            if (p) x.dr.m = atoi(p); else continue;
            p = strtok(NULL, "|");
            if (p) x.dr.g = atoi(p); else continue;
            p = strtok(NULL, "|");
            if (p) x.lubim = atoi(p); else continue;

            kniga[kol] = x;
            kol++;
        }
        f.close();
        cout << "Loaded " << kol << " contacts from file " << name << endl;

        if (kol > 0)
            sortirovka();
    }
    void vse() {
        if (kol == 0) {
            cout << "Phone book is empty\n";
            return;
        }
        cout << "\n--- All contacts ---\n";
        for (int i = 0; i < kol; i++) {
            cout << i + 1 << ". " << kniga[i].fam << " " << kniga[i].im << " " << kniga[i].otch;
            if (kniga[i].lubim) cout << " ★";
            cout << endl;
        }
    }
};
int main() {
    Telef a;
    int v;
    do {
        cout << "\n=== PHONE BOOK ===\n";
        cout << "1. Add contact\n";
        cout << "2. Edit contact\n";
        cout << "3. Find by full name\n";
        cout << "4. Find by phone\n";
        cout << "5. Contacts by letter\n";
        cout << "6. Number of contacts\n";
        cout << "7. Add to favorites\n";
        cout << "8. Remove from favorites\n";
        cout << "9. Show favorites\n";
        cout << "10. Delete contact\n";
        cout << "11. Save to file\n";
        cout << "12. Load from file\n";
        cout << "13. Show all\n";
        cout << "0. Exit\n";
        cout << "Choose option: ";
        cin >> v;

        switch (v) {
        case 1: a.dobavit(); break;
        case 2: a.izmenit(); break;
        case 3: a.naytipoFIO(); break;
        case 4: a.naytipotel(); break;
        case 5: a.pobukve(); break;
        case 6: a.skolko(); break;
        case 7: a.vlubimoe(); break;
        case 8: a.izlubimogo(); break;
        case 9: a.pokazatlubim(); break;
        case 10: a.udalit(); break;
        case 11: a.save(); break;
        case 12: a.load(); break;
        case 13: a.vse(); break;
        case 0: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (v != 0);

    return 0;
}