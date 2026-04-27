#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

struct Song {
    string title;
    string poet;
    string composer;
    string performer;
    string album;
    Date releaseDate;
};

class Songbook {
private:
    static const int MAX_SONGS = 100;
    Song songs[MAX_SONGS];
    int songCount;

    //Сравнение строк
    bool isFirstStringSmaller(string s1, string s2) {
        int i = 0;
        while (i < s1.length() && i < s2.length()) {
            if (tolower(s1[i]) < tolower(s2[i])) return true;
            if (tolower(s1[i]) > tolower(s2[i])) return false;
            i++;
        }
        return s1.length() < s2.length();
    }


    //Корректность даты
    bool isValidDate(Date d) {
        if (d.year < 1900 || d.year > 2026) return false;
        if (d.month < 1 || d.month > 12) return false;
        if (d.day < 1 || d.day > 31) return false;
        return true;
    }


    //Поиск песни
    int findSongIndex(string title, string performer) {
        for (int i = 0; i < songCount; i++) {
            if (songs[i].title == title && songs[i].performer == performer) {
                return i;
            }
        }
        return -1;
    }


    //Сортировка песен по названию
    void sortSongs() {
        for (int i = 0; i < songCount - 1; i++) {
            for (int j = 0; j < songCount - i - 1; j++) {
                if (!isFirstStringSmaller(songs[j].title, songs[j + 1].title) &&
                    songs[j].title != songs[j + 1].title) {
                    Song temp = songs[j];
                    songs[j] = songs[j + 1];
                    songs[j + 1] = temp;
                }
            }
        }
    }

public:
    Songbook() {
        songCount = 0;
    }

    //Добавить песню
    void addSong() {
        if (songCount >= MAX_SONGS) {
            cout << "The songbook is full" << endl;
            return;
        }

        Song newSong;

        cout << "Enter song title: ";
        cin.ignore();
        getline(cin, newSong.title);

        cout << "Enter performer: ";
        getline(cin, newSong.performer);

        if (findSongIndex(newSong.title, newSong.performer) != -1) {
            cout << "A song with this title and performer already exists" << endl;
            return;
        }

        cout << "Enter poet (lyrics author): ";
        getline(cin, newSong.poet);

        cout << "Enter composer (music author): ";
        getline(cin, newSong.composer);

        cout << "Enter album name: ";
        getline(cin, newSong.album);

        cout << "Enter release date:" << endl;
        cout << "  Day: ";
        cin >> newSong.releaseDate.day;
        cout << "  Month: ";
        cin >> newSong.releaseDate.month;
        cout << "  Year: ";
        cin >> newSong.releaseDate.year;

        if (!isValidDate(newSong.releaseDate)) {
            cout << " Invalid date. Song not added." << endl;
            return;
        }

        songs[songCount] = newSong;
        songCount++;

        sortSongs();

        cout << "Song \"" << newSong.title << "\" added successfully" << endl;
    }

    //Изменить данные песни
    void editSong() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string title, performer;

        cout << "Enter song title to find: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter performer to find: ";
        getline(cin, performer);

        int index = findSongIndex(title, performer);

        if (index == -1) {
            cout << "Song not found" << endl;
            return;
        }

        int choice;
        cout << "\nWhat would you like to edit?" << endl;
        cout << "1 - Title" << endl;
        cout << "2 - Poet" << endl;
        cout << "3 - Composer" << endl;
        cout << "4 - Performer" << endl;
        cout << "5 - Album" << endl;
        cout << "6 - Release date" << endl;
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin, songs[index].title);
            sortSongs();
            break;
        case 2:
            cout << "Enter new poet: ";
            cin.ignore();
            getline(cin, songs[index].poet);
            break;
        case 3:
            cout << "Enter new composer: ";
            cin.ignore();
            getline(cin, songs[index].composer);
            break;
        case 4:
            cout << "Enter new performer: ";
            cin.ignore();
            getline(cin, songs[index].performer);
            break;
        case 5:
            cout << "Enter new album: ";
            cin.ignore();
            getline(cin, songs[index].album);
            break;
        case 6:
            cout << "Enter new release date:" << endl;
            cout << "  Day: ";
            cin >> songs[index].releaseDate.day;
            cout << "  Month: ";
            cin >> songs[index].releaseDate.month;
            cout << "  Year: ";
            cin >> songs[index].releaseDate.year;
            if (!isValidDate(songs[index].releaseDate)) {
                cout << "Invalid date. Changes not saved." << endl;
                return;
            }
            break;
        default:
            cout << "Invalid choice" << endl;
            return;
        }

        cout << "Song updated successfully" << endl;
    }

    //Найти песню по названию и исполнителю
    void findSong() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string title, performer;
        cout << "Enter song title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter performer: ";
        getline(cin, performer);

        int index = findSongIndex(title, performer);

        if (index == -1) {
            cout << "Song not found" << endl;
            return;
        }

        cout << "\nSong found" << endl;
        cout << "Title: " << songs[index].title << endl;
        cout << "Poet: " << songs[index].poet << endl;
        cout << "Composer: " << songs[index].composer << endl;
        cout << "Performer: " << songs[index].performer << endl;
        cout << "Album: " << songs[index].album << endl;
        cout << "Release date: " << songs[index].releaseDate.day << "."
            << songs[index].releaseDate.month << "." << songs[index].releaseDate.year << endl;
    }

    //Выдать все песни заданного поэта
    void showSongsByPoet() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string poet;
        cout << "Enter poet name: ";
        cin.ignore();
        getline(cin, poet);

        bool found = false;
        cout << "\nSongs with poet \"" << poet << "\":" << endl;

        for (int i = 0; i < songCount; i++) {
            if (songs[i].poet == poet) {
                cout << "- " << songs[i].title << " (performed by " << songs[i].performer << ")" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No songs found for this poet" << endl;
        }
    }

    //Выдать все песни заданного композитора
    void showSongsByComposer() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string composer;
        cout << "Enter composer name: ";
        cin.ignore();
        getline(cin, composer);

        bool found = false;
        cout << "\nSongs with composer \"" << composer << "\":" << endl;

        for (int i = 0; i < songCount; i++) {
            if (songs[i].composer == composer) {
                cout << "- " << songs[i].title << " (performed by " << songs[i].performer << ")" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No songs found for this composer" << endl;
        }
    }

    //Выдать все песни заданного исполнителя
    void showSongsByPerformer() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string performer;
        cout << "Enter performer name: ";
        cin.ignore();
        getline(cin, performer);

        bool found = false;
        cout << "\nSongs performed by \"" << performer << "\":" << endl;

        for (int i = 0; i < songCount; i++) {
            if (songs[i].performer == performer) {
                cout << "- " << songs[i].title << " (poet: " << songs[i].poet
                    << ", composer: " << songs[i].composer << ")" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No songs found for this performer" << endl;
        }
    }

    //Узнать текущее число песен
    void showSongCount() {
        cout << "Current number of songs in the songbook: " << songCount << endl;
        cout << "Maximum capacity: " << MAX_SONGS << endl;
    }

    //Удалить песню
    void deleteSong() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string title, performer;
        cout << "Enter song title to delete: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter performer to delete: ";
        getline(cin, performer);

        int index = findSongIndex(title, performer);

        if (index == -1) {
            cout << "Song not found" << endl;
            return;
        }

        for (int i = index; i < songCount - 1; i++) {
            songs[i] = songs[i + 1];
        }

        songCount--;
        cout << "Song \"" << title << "\" deleted successfully" << endl;
    }

    //Сохранить песенник в файл
    void saveToFile() {
        if (songCount == 0) {
            cout << "The songbook is empty" << endl;
            return;
        }

        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        ofstream file(filename.c_str());

        if (!file.is_open()) {
            cout << "Cannot open file for writing" << endl;
            return;
        }

        file << songCount << endl;

        for (int i = 0; i < songCount; i++) {
            file << songs[i].title << endl;
            file << songs[i].poet << endl;
            file << songs[i].composer << endl;
            file << songs[i].performer << endl;
            file << songs[i].album << endl;
            file << songs[i].releaseDate.day << " "
                << songs[i].releaseDate.month << " "
                << songs[i].releaseDate.year << endl;
        }

        file.close();
        cout << "Songbook saved to file \"" << filename << "\" successfully ("
            << songCount << " songs saved)" << endl;
    }

    //Считать песенник из файла
    void loadFromFile() {
        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        ifstream file(filename.c_str());

        if (!file.is_open()) {
            cout << "Cannot open file for reading" << endl;
            return;
        }

        songCount = 0;

        int count;
        file >> count;
        file.ignore();

        for (int i = 0; i < count && i < MAX_SONGS; i++) {
            getline(file, songs[i].title);
            getline(file, songs[i].poet);
            getline(file, songs[i].composer);
            getline(file, songs[i].performer);
            getline(file, songs[i].album);
            file >> songs[i].releaseDate.day
                >> songs[i].releaseDate.month
                >> songs[i].releaseDate.year;
            file.ignore();

            songCount++;
        }

        file.close();
        sortSongs();
        cout << "Songbook loaded from file \"" << filename << "\" successfully ("
            << songCount << " songs loaded)" << endl;
    }
};  


int main() {
    Songbook songbook;
    int choice;

    cout << "========== SONGBOOK ==========" << endl;

    do {
        cout << "\nMenu" << endl;
        cout << "1. Add a song" << endl;
        cout << "2. Edit a song" << endl;
        cout << "3. Find a song by title and performer" << endl;
        cout << "4. Show all songs by poet" << endl;
        cout << "5. Show all songs by composer" << endl;
        cout << "6. Show all songs by performer" << endl;
        cout << "7. Show current number of songs" << endl;
        cout << "8. Delete a song" << endl;
        cout << "9. Save songbook to file" << endl;
        cout << "10. Load songbook from file" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Please enter a number" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            songbook.addSong();
            break;
        case 2:
            songbook.editSong();
            break;
        case 3:
            songbook.findSong();
            break;
        case 4:
            songbook.showSongsByPoet();
            break;
        case 5:
            songbook.showSongsByComposer();
            break;
        case 6:
            songbook.showSongsByPerformer();
            break;
        case 7:
            songbook.showSongCount();
            break;
        case 8:
            songbook.deleteSong();
            break;
        case 9:
            songbook.saveToFile();
            break;
        case 10:
            songbook.loadFromFile();
            break;
        case 0:
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 0);

    return 0;
}