#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::cerr;
using std::getline;

void InputClear() {
	cin.clear();
	cin.ignore(1000, '\n');
}
string safeInpWord(const string& promt) {
	string s;
	while (true) {
		cout << promt;
		getline(cin, s);
		if (!s.empty() && s.find(' ') >= s.length()) {
			return s;
		}
		cout << "Error: word must not contain spaces and cannot be empty\n";
	}
}
string safeInpStr(const string& promt) {
	string s;
	cout << promt;
	getline(cin, s);
	return s;
}
class Trans {
private:
	string eng;
	string rus;
public:
	Trans() :eng(""),rus(""){}
	Trans(const string& en, const string& ru) :eng(en),rus(ru){}
	Trans(const Trans& other) :eng(other.eng), rus(other.rus){}
	~Trans(){}
	Trans& operator=(const Trans& other) {
		if (this != &other) {
			eng = other.eng;
			rus = other.rus;
		}
		return *this;
	}
	string GetEng() const { return eng; }
	string GetRus() const { return rus; }
	void  SetRus(const string& nru) { rus = nru; }
};
class Dictionary {
private:
	Trans* data;
	size_t count;
	int findEng(const string& en) const {
		for (size_t i = 0; i < count; ++i) {
			if (data[i].GetEng() == en) {
				return static_cast<int>(i);
			}
		}
		return -1;
	}
	void addEnt(const Trans& ent) {
		Trans* nData = new Trans[count + 1];
		for (size_t i = 0; i < count; ++i) {
			nData[i] = data[i];
		}
		nData[count] = ent;
		delete[] data;
		data = nData;
		++count;
	}

	bool promt(const string& word, bool isEng) {
		cout << "Word:" << word << '\n' << "Not found. Add it to the dictionary? (y/n):";
		char an;
		cin >> an;
		InputClear();
		if (an == 'y' || an == 'Y') {
			string tr;
			if (isEng) {
				tr = safeInpWord("Enter the translation in Russian:");
				addEnt(Trans(word,tr));
			}
			else{
				tr = safeInpWord("Enter the translation in English:");
				addEnt(Trans(tr, word));
			}
			cout << "Added!\n";
			return true;
		}
		return false;
	}
public:
	Dictionary():data(nullptr), count(0){}
	Dictionary(const Dictionary& other):data(nullptr),count(0){
		if (other.count > 0) {
			data = new Trans[other.count];
			for (size_t i = 0; i < other.count; ++i) data[i] = other.data[i];
			count = other.count;
		}
	}
	~Dictionary(){
		delete[] data;
	}
	Dictionary& operator=(const Dictionary& other){
		if (this != &other) {
			delete[] data;
			if (other.count > 0) {
				data = new Trans[other.count];
				for (size_t i = 0; i < other.count; ++i) data[i] = other.data[i];
				count = other.count;
			}
			else {
				data = nullptr;
				count = 0;
			}
		}
		return *this;
	}
	//1
	void AddWord(const string& en, const string& ru) {
		if (en.empty() || ru.empty()) {
			cout << "Word cannot be empty.\n";
			return;
		}
		if (en.find(' ') < en.length() || ru.find(' ') < ru.length()) {
			cout << "Words must not contain spaces.\n";
			return;
		}
		if (findEng(en) != -1) {
			cout << "Word:" << en << "already exists\n";
			return;
		}
		addEnt(Trans(en, ru));
		cout << "Added:" << en << "->" << ru << '\n';
	}
	//2
	void changeTrans(const string& en) {
		int ind = findEng(en);
		if (ind == -1) {
			if (!promt(en,true)) {
				cout << "Operation cancelled";
			}
			return;
		}
		cout << "Translation:" << data[ind].GetRus() << '\n';
		string nru = safeInpWord("Enter a new translation:");
		data[ind].SetRus(nru);
		cout << "The translation has been changed\n";
	}
	//3
	void EnToRu(const string& en) {
		size_t start = 0;
		while (start < en.length()) {
			while (start < en.length() && en[start] == ' ') {
				++start;
			}
			if (start >= en.length()) {
				break;
			}
			size_t end = en.find(' ', start);
			if (end >= en.length()) {
				end = en.length();
			}
			string word = en.substr(start, end - start);
			int idx = findEng(word);
			if (idx != -1) {
				cout << data[idx].GetRus();
			}
			else {
				if (!promt(en, true)) {
					cout << "The translation was not found\n";
				}
				return;
			}
			start = end;
			if (start < en.length()) cout << ' ';
		}
		cout << '\n';
	}
	//4
	void RuToEn(const string& ru) {
		size_t start = 0;
		while (start < ru.length()) {
			while (start < ru.length() && ru[start] == ' ') ++start;
			if (start >= ru.length()) break;
			size_t end = ru.find(' ', start);
			if (end >= ru.length()) end = ru.length();
			string word = ru.substr(start, end - start);
			string* res = nullptr;
			size_t resC= 0;
			for (size_t i = 0; i < count; ++i) {
				if (data[i].GetRus() == word) {
					string* newTrans = new string[resC + 1];
					for (size_t j = 0; j < resC; ++j) newTrans[j] = res[j];
					newTrans[resC] = data[i].GetEng();
					delete[] res;
					res = newTrans;
					++resC;
				}
			}
			if (resC > 0) {
				for (size_t j = 0; j < resC; ++j) {
					if (j > 0) cout << '/';
					cout << res[j];
				}
				delete[] res;
			}
			else {
				if (!promt(ru, false)) {
					cout << "The translation was not found\n";
				}
				return;
			}
			start = end;
			if (start < ru.length()) cout << ' ';
		}
		cout << '\n';
	}
	//5
	int Size() const { return static_cast<int>(count); }
	//6
	void SaveInFile(const string& fname) {
		std::ofstream file(fname);
		if (!file) {
			cerr << "Error opening the file for writing\n";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			file << data[i].GetEng() << " " << data[i].GetRus() << '\n';
		}
		file.close();
		cout << "Dictionary saved to a file " << fname << '\n';
	}
	//7
	void LoadFile(const string& fname) {
		std::ifstream file(fname);
		if (!file) {
			cerr << "Error opening the file for reading\n";
			return;
		}
		string line;
		int c = 0;
		while (getline(file, line)) {
			if (line.empty()) {
				continue;
			}
			size_t spacePos = line.find(' ');
			if (spacePos < line.length()) {
				string en = line.substr(0, spacePos);
				string ru = line.substr(spacePos + 1);
				if (findEng(en) == -1) {
					addEnt(Trans(en, ru));
					++c;
				}
				else {
					cout << "Word: " << en << " already there\n";
				}
			}
			else {
				cerr << "Error! Incorrect line in the file: " << line << "\n";
			}
		}
		file.close();
		cout << "Uploaded " << c << " words from the file " << fname << '\n';
	}
};

int main() {
	Dictionary dict;
	int ch;
	char c;
	string word, fname;
	do {
		cout << "--- Translator Dictionary ---\n";
		cout << "1. Add a word and translation\n";
		cout << "2. Change the translation of an English word\n";
		cout << "3. Translate from English to Russian\n";
		cout << "4. Translate from Russian to English\n";
		cout << "5. Number of words in the dictionary\n";
		cout << "6. Save to file\n";
		cout << "7. Load from file\n";
		cout << "0. Exit\n";
		cout << "Your choice: ";
		while (!(cin >> ch)) {
			InputClear();
			cout << "Invalid input. Enter a number: ";
		}
		InputClear();
		switch (ch) {
		case 1: {
			string ru, en;
			en = safeInpWord("Enter the English word: ");
			ru = safeInpWord("Enter the Russian word: ");
			dict.AddWord(en, ru);
			break;
		}
		case 2: {
			word = safeInpWord("Enter the English word: ");
			dict.changeTrans(word);
			break;
		}
		case 3: {
			word = safeInpStr("Enter the English word: ");
			dict.EnToRu(word);
			break;
		}
		case 4: {
			word = safeInpStr("Enter the Russian word: ");
			dict.RuToEn(word);
			break;
		}
		case 5: {
			cout << "In the dictionary " << dict.Size() << " words\n";
			break;
		}
		case 6: {
			fname = safeInpWord("File name to save: ");
			dict.SaveInFile(fname);
			break;
		}
		case 7: {
			fname = safeInpWord("File name to upload: ");
			dict.LoadFile(fname);
			break;
		}
		case 0:
			cout << "End\n";
			break;

		default:
			cout << "Incorrect selection. Try again\n";
		}
	}while (ch != 0);
	return 0;
}
