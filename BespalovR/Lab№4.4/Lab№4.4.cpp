/*4.4. Контакты
Разработать класс Контакты.
Класс должен хранить информацию о контактах владельца. Каждый контакт содержит
следующие данные: фамилия; имя; отчество; телефон; день рождения (день, месяц, год);
признак, относится ли контакт к избранным. Контакты хранятся упорядоченно по фамилии,
имени, отчеству. Фамилия, имя, отчество (ФИО) являются обязательными полями.
Класс должен содержать необходимые служебные методы.
Класс должен предоставлять следующие операции: 
1) создать новый контакт,
2) изменить выбранный контакт,
3) найти контакт по ФИО,
4) найти контакт по телефону,
5) вывести все контакты на заданную букву,
6) узнать текущее число контактов,
7) внести контакт в список избранных,
8) удалить контакт из списка избранных,
9) вывести все избранные контакты,
10) удалить контакт,
11) сохранить контакты в файл,
12) считать контакты из файла.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::invalid_argument;
using std::out_of_range;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::istream;
using std::string;
using std::vector;
using std::cout;
using std::endl;

//Класс даты для хранения дней рождения
class Date {
    unsigned short day, month, year;
    bool isLeapYear(unsigned short year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
public:
    Date(unsigned short day_ = 1, unsigned short month_ = 1, unsigned short year_ = 1) {
        if (month_ == 0 || month_ > 12 || day_ == 0 || day_ > 31) {
            cout << "ERR:Invalid date.\n";
            throw invalid_argument("Invalid date.");
        }
        unsigned short daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (isLeapYear(year_)) { daysInMonth[2] = 29; }
        if (day_ > daysInMonth[month_]) {
            cout << "ERR:Invalid date.\n";
            throw invalid_argument("Invalid date.");
        }
        day = day_;
        month = month_;
        year = year_;
    }
    //Ввод/вывод
    friend ostream& operator << (ostream& os, const Date& date) {
        os << date.day << '.' << date.month << '.' << date.year;
        return os;
    }
    friend istream& operator >>(istream& is, Date& date) {
        char dot1, dot2;
        is >> date.day >> dot1 >> date.month >> dot2 >> date.year;
        if (dot1 != '.' || dot2 != '.') {
            cout << "ERR:Invalid date format.\n";
            throw invalid_argument("Invalid date format.");
        }
        return is;
    }
};


//Класс одного контакта, Контактная книжка - вектор из контактов и операции с ними
class Contact {
private:
    //Имя, отчество, фамилия, номер, день рождения, избранный
    string first_name;
    string middle_name;
    string last_name;
    string phone_number;
    Date birth_date;
    bool isfavourite;
public:
    //Конструктор от ФИО, номера и опционально даты(Порядок корявый, ИОФ, но пусть будет так)
    Contact(string first_name_ ="", string middle_name_="", string last_name_="", string phone_number_="", Date birth_date_ = Date(1, 1, 1)) : first_name(first_name_), middle_name(middle_name_), last_name(last_name_), phone_number(phone_number_), birth_date(birth_date_), isfavourite(false) {
        //Проверка на корректность формата номера(цифры+*#),сообщение об ошибке, выброс ошибки
        for (size_t i = 0; i < phone_number_.size(); ++i) {
            if (phone_number_[i] != '+' && phone_number_[i] != '*' && phone_number_[i] != '#' && (phone_number_[i] > '9' || phone_number_[i] < '0')) {
                cout << "ERR:Invalid phone number.\n";
                throw invalid_argument("Invalid phone number.");
                break;
            }
        }
    }
    //Геттеры, необходимы для записи в файл
    string getFirstName() const { return first_name; }
    string getMiddleName() const { return middle_name; }
    string getLastName() const { return last_name; }
    string getPhone() const { return phone_number; }
    Date getBirthDate() const { return birth_date; }
    //Операции со статусом избранное
    void AddToFav() { isfavourite = true; }
    void RemFrFav() { isfavourite = false; }
    bool IsFavourite() const { return isfavourite; }
    //Перегрузка меньше для сортировки списка контактов
    bool operator < (const Contact& other) const {
        if (last_name != other.last_name) {
            return last_name < other.last_name;
        }
        if (first_name != other.first_name) {
            return first_name < other.first_name;
        }
        return middle_name < other.middle_name;
    }
    //Пункты 3 и 4
    bool MatchesFullName(const string& n, const string& m, const string& l) const {
        return first_name == n && middle_name == m && last_name == l;
    }
    bool MatchesPhone(const string& phone) const {
        return phone_number == phone;
    }
    bool StartsWithLetter(char letter) const {
        return last_name.size() != 0 && last_name[0] == letter;
    }
    //Ввод/вывод
    friend ostream& operator << (ostream& os, const Contact& contact) {
        os << contact.last_name << ' ' << contact.first_name << ' ' << contact.middle_name << ' ' << contact.phone_number << ' ' << contact.birth_date << ' ' << contact.isfavourite ? 1 : 0;
        return os;
    }
    friend istream& operator >>(istream& is, Contact& contact) {
        contact.isfavourite = false;
        is >> contact.last_name >> contact.first_name >> contact.middle_name >> contact.phone_number >> contact.birth_date >> contact.isfavourite;
        if (contact.last_name.size() == 0 || contact.first_name.size() == 0 || contact.middle_name.size() == 0) {
            cout << "ERR:Empty fields.\n";
            throw invalid_argument("Empty fields.");
        }
        return is;
    }
};


//Класс контактной книжки, служебный метод упорядочивания контактов
class ContactsBook {
private:
    vector<Contact> contacts;
    void sortContacts() {
        size_t n = contacts.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (contacts[j + 1] < contacts[j]) {
                    Contact temp = contacts[j+1];
                    contacts[j + 1] = contacts[j];
                    contacts[j] = temp;
                }
            }
        }
    }
public:
    //Единственное поле - вектор, поэтому конструктор от компилятора. 

    // 1) Создать новый контакт
    void addContact(Contact new_contact) {
        contacts.push_back(new_contact);
        sortContacts();
    }

    // 2) Изменить выбранный контакт
    void editContact(int index, Contact updatedContact) {
        if (index >= contacts.size() || index < 0) {
            cout << "ERR:Index out of range.\n";
            throw out_of_range("Index out of range.");
        }
        contacts[index] = updatedContact;
        sortContacts(); 
    }

    // 3) Найти контакт по ФИО
    long long findContactByFullName(const string& first_name, const string& middle_name, const string& last_name) const {
        for (long long i = 0; i < contacts.size(); ++i) {
            if (contacts[i].MatchesFullName(first_name, middle_name, last_name)) {
                return i;
            }
        }
        return -1;
    }
    // 4) Найти контакт по телефону
    long long findContactByPhone(const string& phone) const {
        for (long long i = 0; i < contacts.size(); ++i) {
            if (contacts[i].MatchesPhone(phone)) {
                return i;
            }
        }
        return -1;
    }
    // 5) Вывести все контакты на заданную букву
    void printContactsByLetter(char letter) const {
        bool found = false;
        for (size_t i = 0; i < contacts.size(); ++i) {
            if (contacts[i].StartsWithLetter(letter)) {
                std::cout << contacts[i] << endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No contacts found starting with '" << letter << "'.\n";
        }
    }
    // 6) Узнать текущее число контактов
    size_t getContactCount() const { return contacts.size(); }
    // 7) Внести контакт в список избранных
    void addToFavourites(int index) {
        if (index >= contacts.size() || index < 0) {
            cout << "ERR:Index out of range.\n";
            throw out_of_range("Index out of range.");
        }
        contacts[index].AddToFav();
    }
    // 8) Удалить контакт из списка избранных
    void removeFromFavourites(int index) {
        if (index >= contacts.size() || index < 0) {
            cout << "ERR:Index out of range.\n";
            throw out_of_range("Index out of range.");
        }
        contacts[index].RemFrFav();
    }
    // 9) Вывести все избранные контакты
    void printFavourites() const {
        bool found = false;
        for (size_t i = 0; i < contacts.size(); ++i) {
            if (contacts[i].IsFavourite()) {
                std::cout << contacts[i] << endl;
                found = true;
            }
        }
        if (!found) {
            std::cout << "No favourite contacts.\n";
        }
    }
    // 10) Удалить контакт
    void deleteContact(int index) {
        if (index >= contacts.size() || index < 0) {
            cout << "ERR:Index out of range.\n";
            throw std::out_of_range("Index out of range.");
        }
        contacts.erase(contacts.begin() + index);
    }
    // 11) Сохранить контакты в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "ERR:Cannot open file for writing: " << filename << endl;
            throw;
        }
        file << contacts.size() << '\n'; 
        for (size_t i = 0; i < contacts.size(); ++i) {
            file << contacts[i] << '\n';
        }
        file.close();
        cout << "Contacts saved to " << filename << " successfully.\n";
    }
    // 12) Считать контакты из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "ERR:Cannot open file for reading: " << filename << endl;
            throw;
        }
        contacts.clear();
        size_t count;
        file >> count;
        for (size_t i = 0; i < count; ++i) {
            Contact contact;
            file >> contact;
            if (file.fail()) {
                cout << "ERR:Failed to read contact at line " << (i + 1) << endl;
                file.close();
                throw;
            }
            contacts.push_back(contact);
        }
        file.close();
        sortContacts();
        cout << "Contacts loaded from " << filename << " successfully." << endl;
    }
    //Вывод всего, в критериях не было но для удобаства добавил
    void printAll() const {
        for (size_t i = 0; i < contacts.size(); ++i) {
            cout << i << ": " << contacts[i] << endl;
        }
    }
};


int main() {
    ContactsBook book;
    book.addContact(Contact("Ivan", "Ivanovich", "Ivanov", "+79991234567", Date(15, 3, 1990)));
    book.addContact(Contact("Alexander", "Sergeyevich", "Petrov", "+79999876543", Date(10, 7, 1985)));
    book.addContact(Contact("Anna", "Michailovna", "Sidorova", "+79991112233", Date(22, 12, 1992)));
    book.addToFavourites(0);
    cout << "\n=== Favourites ===\n";
    book.printFavourites();
    book.saveToFile("contacts.txt");
    ContactsBook book2;
    book2.loadFromFile("contacts.txt");
    cout << "\n=== Loaded contacts ===\n";
    book2.printAll();
    return 0;
}