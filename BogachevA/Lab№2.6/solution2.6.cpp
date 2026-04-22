#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <unordered_set>
bool IsLatin(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
class string {
private:
    char* str;
    size_t length_;
public:
    explicit string() : str(new char[1]), length_(0) {
        str[0] = '\0';
    }
    string(size_t len, const char* str_) {
        if (str_ == nullptr || len == 0) {
            str = new char[1];
            str[0] = '\0';
            length_ = 0;
            return;
        }
        length_ = (len < 40) ? len : 40;
        try {
            str = new char[length_ + 1];
            strncpy(str, str_, length_);
            str[length_] = '\0';   
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            str = new char[1];
            str[0] = '\0';
            length_ = 0;
        }
    }
    string(const string& other) : length_(other.length_) {
        str = new char[length_ + 1];
        strncpy(str, other.str, length_);
        str[length_] = '\0';
    }
    ~string() {
        delete[] str;
    }
    string& operator=(const string& other) {
        if (this != &other) {
            delete[] str;
            length_ = other.length_;
            str = new char[length_ + 1];
            strncpy(str, other.str, length_);
            str[length_] = '\0';
        }
        return *this;
    }
    void setstring(const char* str_) {
        if (str_ == nullptr) {
            delete[] str;
            str = new char[1];
            str[0] = '\0';
            length_ = 0;
            return;
        }
        size_t len = strlen(str_);
        len = (len > 40) ? 40 : len;
        delete[] str;
        try {
            str = new char[len + 1];
            strncpy(str, str_, len);
            str[len] = '\0';
            length_ = len;
        }
        catch (const std::exception& ex) {
            std::cout << ex.what() << std::endl;
            str = new char[1];
            str[0] = '\0';
            length_ = 0;
        }
    }
    size_t length() const {
        return length_;
    }
    char getChar(size_t i) const {
        return (i < length_) ? str[i] : '\0';
    }
    void changeChar(size_t i, char c) {
        if (i < length_) {
            str[i] = c;
        }
        else {
            std::cout << "index is out of range" << std::endl;
        }
    }
    string substr(size_t begin, size_t end) const {
        if (begin >= end || end > length_) {
            std::cout << "incorrect data" << std::endl;
            return string();
        }
        size_t subLen = end - begin;
        char* temp = new char[subLen + 1];
        for (size_t i = 0; i < subLen; ++i) {
            temp[i] = str[begin + i];
        }
        temp[subLen] = '\0';
        string substring(subLen, temp);
        delete[] temp;
        return substring;
    }
    bool isPalindrome() const {
        if (length_ <= 1) return true;
        for (size_t i = 0; i < length_ / 2; ++i) {
            if (str[i] != str[length_ - 1 - i]) return false;
        }
        return true;
    }    int countLatin() const {
        int count = 0;
        for (size_t i = 0; i < length_; ++i) {
            char current = str[i];
            if (IsLatin(current)) {
                bool alreadyCounted = false;
                for (size_t j = 0; j < i; ++j) {
                    if (str[j] == current) {
                        alreadyCounted = true;
                        break;
                    }
                }
                if (!alreadyCounted) {
                    ++count;
                }
            }
        }
        return count;
    }
    friend std::ostream& operator<<(std::ostream& os, const string& s) { 
        os << s.str;
        return os;
    }
};
int main() {
    int choice;
    string s;
    std::cout << "Enter" << std::endl;
    std::cout << "'1' if you want to specify a string" << std::endl;
    std::cout << "'2' if you want to find the length of a string" << std::endl;
    std::cout << "'3' if you want to get a character in a string by index" << std::endl;
    std::cout << "'4' if you want to change an element in a string at a given index" << std::endl;
    std::cout << "'5' if you want to select a substring" << std::endl;
    std::cout << "'6' if you want to find out whether a string is a palindrome" << std::endl;
    std::cout << "'7' if you want to find the number of different Latin letters in a string" << std::endl;
    std::cout << "'0' if you want to finish" << std::endl;
    do {
        std::cin >> choice;
        switch (choice) {
        case 1: {
            std::cout << "Enter the string" << std::endl;
            std::cin.ignore(); 
            char s_[41];
            std::cin.getline(s_, 41); 
            s.setstring(s_);
            std::cout << "Your string is - " << s << std::endl;
            break;
        }
        case 2:
            std::cout << s.length() << std::endl;
            break;
        case 3: {
            size_t id;
            std::cout << "Enter index" << std::endl;
            std::cin >> id;
            std::cout << s.getChar(id) << std::endl;
            break;
        }
        case 4: {
            size_t id;
            char c;
            std::cout << "Enter index and new character" << std::endl;
            std::cin >> id >> c;
            s.changeChar(id, c);
            std::cout << "Now your string is - " << s << std::endl;
            break;
        }
        case 5: {
            size_t begin, end;
            std::cout << "Enter begin and end" << std::endl;
            std::cin >> begin >> end;
            string sub = s.substr(begin, end);
            std::cout << "Substring is - " << sub << std::endl;
            break;
        }
        case 6:
            std::cout << (s.isPalindrome() ? "Yes" : "No") << std::endl;
            break;
        case 7:
            std::cout << s.countLatin() << std::endl;
            break;
        case 0:
            break;
        default:
            std::cout << "incorrect choice" << std::endl;
            break;
        }
    } while (choice != 0);
    return 0;
}