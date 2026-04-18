#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::getline;
using std::cerr;

void InputСlear() {
	cin.clear();
	cin.ignore(1000, '\n');
}
class Date {
private:
	int day, month, year;
public:
	Date(int d = 0, int m = 0, int y = 0):day(d),month(m),year(y){}
	int GetDay() const { return day; }
	int GetMonth() const { return month; }
	int GetYear() const { return year; }
	void SetDate(int d, int m, int y) { day = d, month = m, year = y; }
	void print() const { std::cout << day << '.' << month << '.' << year; }
};
class Album {
private:
	string album;
public:
	Album(const string& alb = ""):album(alb){}
	string GetAlb() const { return album; }
	void SetAlb(const string& alb) { album = alb; }
	bool isEmpty() const { return album.empty(); }
	void print() const {
		if (album.empty()) {
			cout << "---";
		}
		else {
			cout << album;
		}
	}
};

class Song: public Album, public Date{
private:
	string name;
	string poet;
	string composer;
	string singer;
public:
	Song() : name(""), poet(""), composer(""), singer(""), Album(""), Date(0, 0, 0) {}
	Song(const string& nm, const string& p, const string& comp, const string& sin,
		const string& alb,int d,int m,int y):name(nm), poet(p), composer(comp), singer(sin), Album(alb), Date(d, m, y) {}
	string GetName() const { return name; }
	string GetPoet() const { return poet; }
	string GetComposer() const { return composer; }
	string GetSinger() const { return singer; }
	void SetName(const string& nm) { name = nm; }
	void SetPoet(const string& p) { poet = p; }
	void SetComposer(const string& comp) { composer = comp; }
	void SetSinger(const string& sin) { singer = sin; }
	bool operator<(const Song& other) const {
		if (name != other.name) {
			return name < other.name;
		}
		return singer < other.singer;
	}
	void print() const {
		cout << "Name: " << name;
		cout << "Album: ";
		Album::print();
		cout << '\n';
		cout << "Singer: " << singer;
		cout << "Poet: " << poet;
		cout << "Composer: " << composer << '\n';
		cout << "Release date: ";
		Date::print();
		cout << '\n';
	}
};
class Songster: public Song {
private:
	Song* songs;
	size_t count;

	size_t FindPos(const Song& s) const {
		size_t i = 0;
		while (i < count && songs[i] < s) {
			++i;
		}
		return i;
	}
	int FindInd(const string& nm, const string& sin) const {
		for (size_t i = 0; i < count; ++i) {
			if (songs[i].GetName() == nm && songs[i].GetSinger() == sin) {
				return static_cast<int>(i);
			}
		}
		return -1;
	}
public:
	Songster(): songs(nullptr), count(0) {}
	Songster(const Songster& other) : songs(nullptr), count(other.count) {
		if (count) {
			songs = new Song[count];
			for (size_t i = 0; i < count; ++i) {
				songs[i] = other.songs[i];
			}
		}
	}
	~Songster() {
		delete[] songs;
	}
	//1
	bool addSong(const Song& nsong) {
		if (FindInd(nsong.GetName(), nsong.GetSinger()) != -1) {
			cout << "A song with this title and singer already exists\n";
			return false;
		}
		size_t pos = FindPos(nsong);
		Song* narr = new Song[count + 1];
		for (size_t i = 0; i < pos; ++i) {
			narr[i] = songs[i];
		}
		narr[pos] = nsong;
		for (size_t i = pos; i < count; ++i) {
			size_t nind = i + 1;
			narr[nind] = songs[i];
		}
		delete[] songs;
		songs = narr;
		++count;
		cout << "Song added\n";
		return true;
	}
	//2
	void editSong(const string& nm, const string& sin) {
		int ind = FindInd(nm, sin);
		if (ind == -1) {
			cout << "Song not found\n";
			return;
		}
		Song oldSong = songs[ind];
		string nName, nPoet, nComposer, nSinger, nAlbum;
		int d, m, y;
		cout << "Enter a new name(or '-'): ";
		getline(cin, nName);
		if (nName == "-") {
			nName = oldSong.GetName();
		}
		cout << "Enter a new poet(or '-'): ";
		getline(cin, nPoet);
		if (nPoet == "-") {
			nPoet = oldSong.GetPoet();
		}
		cout << "Enter a new composer(or '-'): ";
		getline(cin, nComposer);
		if (nComposer == "-") {
			nComposer = oldSong.GetComposer();
		}
		cout << "Enter a new singer(or '-'): ";
		getline(cin, nSinger);
		if (nSinger == "-") {
			nSinger = oldSong.GetSinger();
		}
		cout << "Enter a new Album(or '-'): ";
		getline(cin, nAlbum);
		if (nAlbum == "-") {
			nAlbum = oldSong.GetAlb();
		}
		cout << "Enter a new date(day month year, 0 0 0 - leave the previous date): ";
		while (true) {
			cout << "day: ";
			if (cin >> d) {
				if (d >= 1 && d <= 31) break;
				else cout << "The day must be between 1 and 31\n";
			}
			else {
				cout << "Enter an integer\n";
				InputСlear();
			}
		}
		InputСlear();
		while (true) {
			cout << "month: ";
			if (cin >> m) {
				if (m >= 1 && m <= 12) break;
				else cout << "Month must be between 1 and 12\n";
			}
			else {
				cout << "Enter an integer\n";
				InputСlear();
			}
		}
		InputСlear();
		while (true) {
			cout << "year: ";
			if (cin >> y) {
				if (y >= 0 && y <= 3000) break;
				else cout << "The year is entered incorrectly\n";
			}
			else {
				cout << "Enter an integer\n";
				InputСlear();
			}
		}
		InputСlear();
		Song NewSong(nName, nPoet, nComposer, nSinger, nAlbum, d, m, y);
		if (NewSong.GetName() == oldSong.GetName() &&
			NewSong.GetSinger() == oldSong.GetSinger() &&
			NewSong.GetPoet() == oldSong.GetPoet() &&
			NewSong.GetComposer() == oldSong.GetComposer() &&
			NewSong.GetAlb() == oldSong.GetAlb() &&
			NewSong.GetDay() == oldSong.GetDay() &&
			NewSong.GetMonth() == oldSong.GetMonth() &&
			NewSong.GetYear() == oldSong.GetYear()) {
			cout << "No changes made.\n";
			return;
		}
		Song* narr = new Song[count - 1];
		size_t j = 0;
		for (size_t i = 0; i < count; ++i) {
			if (i != static_cast<size_t>(ind)) {
				narr[j++] = songs[i];
			}
		}
		delete[] songs;
		songs = narr;
		--count;
		if (!addSong(NewSong)) {
			addSong(oldSong);
			cout << "Edit cancelled\n";
			return;
		}
		cout << "Information has been changed\n";
	}
	//3
	void FindSong(const string& nm, const string& sin) const {
		int ind = FindInd(nm, sin);
		if (ind == -1) {
			cout << "Song not found\n";
		}
		else {
			songs[ind].print();
		}
	}
	//4
	void FindByPoet(const string& poet) const {
		bool found = false;
		for (size_t i = 0; i < count; ++i) {
			if (songs[i].GetPoet() == poet) {
				songs[i].print();
				found = true;
			}
		}
		if (!found) {
			cout << "there are no songs by this poet\n";
		}
	}
	//5
	void FindByComposer(const string& comp) const {
		bool found = false;
		for (size_t i = 0; i < count; ++i) {
			if (songs[i].GetComposer() == comp) {
				songs[i].print();
				found = true;
			}
		}
		if (!found) {
			cout<< "there are no songs by this composer\n";
		}
	}
	//6
	void FindBySinger(const string& sin) const {
		bool found = false;
		for (size_t i = 0; i < count; ++i) {
			if (songs[i].GetSinger() == sin) {
				songs[i].print();
				found = true;
			}
		}
		if (!found) {
			cout<< "there are no songs by this singer\n";
		}
	}
	//7
	size_t GetCount() const { return count; }
	//8
	void DeleteSong(const string& nm, const string& sin) {
		int ind = FindInd(nm, sin);
		if (ind == -1) {
			cout<< "Song not found\n";
			return;
		}
		Song* narr = new Song[count - 1];
		size_t j = 0;
		for (size_t i = 0; i < count; ++i) {
			if (i != static_cast<size_t>(ind)) {				
				narr[j++] = songs[i];
			}
		}
		delete[] songs;
		songs = narr;
		--count;
		cout << "Deleted song\n";
	}
	//9
	void SaveToFile(const string& fname) const {
		std::ofstream file(fname);
		if (!file) {
			cerr << "Error opening the file for writing\n";
			return;
		}
		for (size_t i = 0; i < count; ++i) {
			const Song& s = songs[i];
			file << s.GetAlb() << "|" << s.GetName()<<"|"<< s.GetSinger()<<"|" << s.GetPoet()<<"|" 
				<< s.GetComposer() << "|" << s.GetDay() << "|" << s.GetMonth() << "|"<< s.GetYear() << "\n";
		}
		file.close();
		cout << "Saved\n";
	}
	//10
	void LoadFromFile(const string& fname) {
		std::ifstream file(fname);
		if (!file) {
			cerr << "Error opening the file for reading\n";
			return;
		}
		string line;
		int loaded = 0;
		while (getline(file, line)) {
			if (line.empty()) {
				continue;
			}
			size_t pos = 0, next;
			string fields[8];
			for (int i = 0; i < 8; ++i) {
				next = line.find(("|"), pos);
				if (next >= line.length()) {
					next = line.length();
				}
				fields[i] = line.substr(pos, next - pos);
				pos = next + 1;
			}
			int d = 0, m = 0, y = 0;
			for (size_t i = 0; i < fields[5].length(); ++i) {
				d = d * 10 + (fields[5][i] - '0');
			}
			for (size_t i = 0; i < fields[6].length(); ++i) {
				m = m * 10 + (fields[6][i] - '0');
			}
			for (size_t i = 0; i < fields[7].length(); ++i) {
				y = y * 10 + (fields[7][i] - '0');
			}
			Song s(fields[0], fields[1], fields[2], fields[3], fields[4], d, m, y);
			if (addSong(s)) {
				++loaded;
			}
		}
		file.close();
		cout << "Uploaded" << loaded << "songs\n";
	}	
};
int main() {
	Songster songster;
	int ch, d, m, y;
	string name, poet, composer, singer, album, filename;
	do {
		cout << "--- Songster ---\n";
		cout << "1.Add a song\n";
		cout << "2.Edit a song\n";
		cout << "3.Find a song by name and singer\n";
		cout << "4.Get all songs by this poet\n";
		cout << "5.Get all songs by this composer\n";
		cout << "6.Get all songs by this singer\n";
		cout << "7.Number of songs\n";
		cout << "8.Delete a song\n";
		cout << "9.Save to file\n";
		cout << "10.Load from file\n";
		cout << "0.Exit\n";
		cout << "Your choice: ";
		cin >> ch;
		cin.ignore();
		switch (ch) {
		case 1: {
			cout << "Album: ";
			getline(cin, album);
			cout << "Name: ";
			getline(cin, name);
			cout << "Singer: ";
			getline(cin, singer);
			cout << "Poet: ";
			getline(cin, poet);
			cout << "Composer: ";
			getline(cin, composer);
			cout << "Date(day month year): ";
			cin >> d >> m >> y;
			songster.addSong(Song(name, poet, composer, singer, album, d, m, y));
			break;
		}
		case 2: {
			cout << "Name: ";
			getline(cin, name);
			cout << "Singer: ";
			getline(cin, singer);
			songster.editSong(name, singer);
			break;
		}
		case 3: {
			cout << "Name: ";
			getline(cin, name);
			cout << "Singer: ";
			getline(cin, singer);
			songster.FindSong(name, singer);
			break;
		}
		case 4: {
			cout << "Poet: ";
			getline(cin, poet);
			songster.FindByPoet(poet);
			break;
		}
		case 5: {
			cout << "Composer: ";
			getline(cin, composer);
			songster.FindByComposer(composer);
			break;
		}
		case 6: {
			cout << "Singer: ";
			getline(cin, singer);
			songster.FindBySinger(singer);
			break;
		}
		case 7: {
			cout << "Number of songs: " << songster.GetCount() << '\n';
			break;
		}
		case 8: {
			cout << "Name: ";
			getline(cin, name);
			cout << "Singer: ";
			getline(cin, singer);
			songster.DeleteSong(name, singer);
			break;
		}
		case 9: {
			cout << "File name:";
			getline(cin, filename);
			songster.SaveToFile(filename);
			break;
		}
		case 10: {
			cout << "File name:";
			getline(cin, filename);
			songster.LoadFromFile(filename);
			break;
		}
		case 0: {
			cout << "End\n";
			break;
		}
		default:
			cout << "Incorrect selection. Try again\n";
		}
	}while (ch != 0);
	return 0;
}
