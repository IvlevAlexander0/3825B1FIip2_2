#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::string;
using std::cin;
using std::cout;
using std::vector;
using std::cerr;
using std::getline;

void InputClear() {
	cin.clear();
	cin.ignore(1000, '\n');
}
string safeInpStr(const string& promt) {
	string s;
	cout << promt;
	getline(cin,s);
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
	vector<Trans> rec;
	int findEng(const string& en) const {
		for (size_t i = 0; i < rec.size(); ++i) {
			if (rec[i].GetEng() == en) {
				return i;
			}
		}
		return -1;
	}
	bool promt(const string& word, bool isEng) {
		cout << "Word:" << word << '\n' << "Not found. Add it to the dictionary? (y/n):";
		char an;
		cin >> an;
		InputClear();
		if (an == 'y' || an == 'Y') {
			string tr;
			if (isEng) {
				tr = safeInpStr("Enter the translation in Russian:");
				rec.push_back(Trans(word, tr));
			}
			else{
				tr = safeInpStr("Enter the translation in English:");
				rec.push_back(Trans(tr, word));
			}
			cout << "Added!\n";
			return true;
		}
		return false;
	}
public:
	Dictionary(){}
	Dictionary(const Dictionary& other):rec(other.rec){}
	~Dictionary(){}
	Dictionary& operator=(const Dictionary& other){
		if (this != &other) {
			rec = other.rec;
		}
		return *this;
	}
	//1
	void AddWord(const string& en, const string& ru) {
		if (findEng(en) != -1) {
			cout << "Word:" << en << "already exists\n";
			return;
		}
		rec.push_back(Trans(en, ru));
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
		cout << "Translation:" << rec[ind].GetRus() << '\n';
		string nru;
		nru = safeInpStr("Enter a new translation:");
		rec[ind].SetRus(nru);
		cout << "The translation has been changed\n";
	}
	//3
	void EnToRu(const string& en) {
		int ind = findEng(en);
		if (ind == -1) {
			if (!promt(en, true))
				cout << "The translation was not found\n";
			return;
		}
		cout << en << " -> " << rec[ind].GetRus() << '\n';
	}
	//4
	void RuToEn(const string& ru) {
		vector<string> res;
		for (size_t i = 0; i < rec.size(); ++i) {
			if (rec[i].GetRus() == ru) {
				res.push_back(rec[i].GetEng());
			}
		}
		if (res.empty()) {
			if (!promt(ru, false)) {
				cout << "The translation was not found\n";
			}
			return;
		}
		cout << ru << "->";
		for (size_t j = 0; j < res.size(); ++j) {
			if (j > 0) {
				cout << ", ";
			}
			cout << res[j];
		}
		cout << '\n';
	}
	//5
	int Size() const { return rec.size(); }
	//6
	void SaveInFile(const string& fname) {
		std::ofstream file(fname);
		if (!file) {
			cerr << "Error opening the file for writing\n";
			return;
		}
		for (size_t i = 0; i < rec.size(); ++i) {
			file << rec[i].GetEng() << " " << rec[i].GetRus() << '\n';
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
					rec.push_back(Trans(en, ru));
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
			en = safeInpStr("Enter the English word: ");
			ru = safeInpStr("Enter the Russian word: ");
			dict.AddWord(en, ru);
			break;
		}
		case 2: {
			word = safeInpStr("Enter the English word: ");
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
			fname = safeInpStr("File name to save: ");
			dict.SaveInFile(fname);
			break;
		}
		case 7: {
			fname = safeInpStr("File name to upload: ");
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
