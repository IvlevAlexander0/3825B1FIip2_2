#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

struct Date {
    int day;
    int month;
    int year;
};

struct Time {
    int hour;  
};


struct Observation {
    Date date;
    Time time;
    double temperature;
    bool isSet;
};

class Thermometer {
private:
    static const int MAX_DAYS = 365;
    static const int HOURS_PER_DAY = 24;

    Observation*** history;
    int totalDays;

    Date startDate;
    Time startTime;

    bool isLeapYear(int year) const {
        if (year % 400 == 0) return true;
        if (year % 100 == 0) return false;
        if (year % 4 == 0) return true;
        return false;
    }

    int daysInMonth(int month, int year) const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if (month == 2 && isLeapYear(year)) {
            return 29;
        }

        return days[month - 1];
    }

    int dateToDayIndex(const Date& date) const {
        int dayIndex = 0;

        for (int m = 1; m < date.month; ++m) {
            dayIndex += daysInMonth(m, date.year);
        }

        dayIndex += (date.day - 1);

        return dayIndex;
    }

    bool isValidDate(const Date& date) const {
        if (date.year < 0)
            return false;
        if (date.month < 1 || date.month > 12)
            return false;
        if (date.day < 1 || date.day > daysInMonth(date.month, date.year))
            return false;
        return true;
    }

    bool isValidTime(const Time& time) const {
        return (time.hour >= 0 && time.hour < 24);
    }

    Date dayIndexToDate(int dayIndex) const {
        Date result;
        result.year = startDate.year;
        result.month = 1;

        while (dayIndex >= daysInMonth(result.month, result.year)) {
            dayIndex -= daysInMonth(result.month, result.year);
            ++result.month;
        }

        result.day = dayIndex + 1;
        return result;
    }

public:
    Thermometer() {
        startDate.day = 1;
        startDate.month = 1;
        startDate.year = 2000;
        startTime.hour = 0;
        totalDays = MAX_DAYS;

        history = new Observation * *[totalDays];

        for (int i = 0; i < totalDays; ++i) {
            history[i] = new Observation * [HOURS_PER_DAY];

            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                history[i][j] = nullptr;
            }
        }
    }

    ~Thermometer() {
        for (int i = 0; i < totalDays; ++i) {
            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                if (history[i][j] != nullptr) {
                    delete history[i][j];
                }
            }
            delete[] history[i];
        }
        delete[] history;
    }

    void setStartDateTime() {
        Date date;
        Time time;

        std::cout << "Enter start date (day month year): ";
        std::cin >> date.day >> date.month >> date.year;

        std::cout << "Enter start time (0-23): ";
        std::cin >> time.hour;

        if (!isValidDate(date)) {
            std::cout << "Error: incorrect date\n" << std::endl;
            return;
        }
        if (!isValidTime(time)) {
            std::cout << "Error: incorrect time\n" << std::endl;
            return;
        }

        for (int i = 0; i < totalDays; ++i) {
            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                if (history[i][j] != nullptr) {
                    delete history[i][j];
                    history[i][j] = nullptr;
                }
            }
        }

        startDate = date;
        startTime = time;
    }

    void getStartDateTime() const {
        std::cout << "Date: ";

        if (startDate.day < 10) std::cout << "0";
        std::cout << startDate.day << ".";

        if (startDate.month < 10) std::cout << "0";
        std::cout << startDate.month << "." << startDate.year << std::endl;

        std::cout << "Time: ";

        if (startTime.hour < 10) std::cout << "0";
        std::cout << startTime.hour << ":00" << std::endl;
    }

    void setObservation() {
        Date date;
        Time time;
        double temperature;

        std::cout << "Enter date of observation: ";
        std::cin >> date.day >> date.month >> date.year;

        std::cout << "Enter time of observation(0-23): ";
        std::cin >> time.hour;

        std::cout << "Enter temperature: ";
        std::cin >> temperature;

        if (!isValidDate(date) || !isValidTime(time)) {
            std::cout << "Error: incorret date or time\n" << std::endl;
            return;
        }

        int dayIndex = dateToDayIndex(date);

        if (dayIndex < 0 || dayIndex >= totalDays) {
            std::cout << "Error: date is out of range\n" << std::endl;
            return;
        }

        int hourIndex = time.hour;

        if (history[dayIndex][hourIndex] != nullptr) {
            delete history[dayIndex][hourIndex];
        }

        Observation* obs = new Observation;
        obs->date = date;
        obs->time = time;
        obs->temperature = temperature;
        obs->isSet = true;

        history[dayIndex][hourIndex] = obs;
        std::cout << "Observation was added\n" << std::endl;
    }

    void getTemperature() const {
        Date date;
        Time time;

        std::cout << "Enter date of observation: ";
        std::cin >> date.day >> date.month >> date.year;

        std::cout << "Enter time of observation(0-23): ";
        std::cin >> time.hour;

        if (!isValidDate(date) || !isValidTime(time)) {
            std::cout << "Error: incorrect date or time\n" << std::endl;
            return;
        }

        int dayIndex = dateToDayIndex(date);

        if (dayIndex < 0 || dayIndex >= totalDays) {
            std::cout << "Error: date is out of range\n" << std::endl;
            return;
        }

        int hourIndex = time.hour;

        if (history[dayIndex][hourIndex] == nullptr) {
            std::cout << "Error: observation wasn't found\n" << std::endl;
            return;
        }

        std::cout << "Temperature: " << history[dayIndex][hourIndex]->temperature << " °C" << std::endl;
    }

    void setDailyObservations() {
        Date date;
        double temperatures[24];

        std::cout << "Enter date: ";
        std::cin >> date.day >> date.month >> date.year;

        if (!isValidDate(date)) {
            std::cout << "Error: inccorect date\n" << std::endl;
            return;
        }

        int dayIndex = dateToDayIndex(date);

        if (dayIndex < 0 || dayIndex >= totalDays) {
            std::cout << "Error: date is out of range\n" << std::endl;
            return;
        }

        std::cout << "Enter temperature for 24 hours: " << std::endl;
        for (int hour = 0; hour < 24; ++hour) {
            std::cin >> temperatures[hour];
        }

        for (int hour = 0; hour < 24; ++hour) {
            Time t;
            t.hour = hour;

            if (history[dayIndex][hour] != nullptr) {
                delete history[dayIndex][hour];
            }

            Observation* obs = new Observation;
            obs->date = date;
            obs->time = t;
            obs->temperature = temperatures[hour];
            obs->isSet = true;

            history[dayIndex][hour] = obs;
        }

        std::cout << "Series of observation were added\n" << std::endl;
    }

    void getAverageDailyTemperature() const {
        Date date;

        std::cout << "Enter date: ";
        std::cin >> date.day >> date.month >> date.year;

        if (!isValidDate(date)) {
            std::cout << "Error: incorrect date\n" << std::endl;
            return;
        }

        int dayIndex = dateToDayIndex(date);

        if (dayIndex < 0 || dayIndex >= totalDays) {
            std::cout << "Error: date is out of range\n" << std::endl;
            return;
        }

        double sum = 0;
        int count = 0;

        for (int hour = 0; hour < HOURS_PER_DAY; ++hour) {
            if (history[dayIndex][hour] != nullptr) {
                sum += history[dayIndex][hour]->temperature;
                ++count;
            }
        }

        if (count == 0) {
            std::cout << "Error: observation wasn't found\n" << std::endl;
            return;
        }

        std::cout << "Avg temp for date: " << date.day << "." << date.month << "." << date.year << ": " << (sum / count) << " °C (for " << count << " observations)" << std::endl;
    }

    void getAverageMonthlyTemperature() const {
        int month;
        int choice;

        std::cout << "Enter month(1-12): ";
        std::cin >> month;

        if (month < 1 || month > 12) {
            std::cout << "Error: incorrect month\n" << std::endl;
            return;
        }

        std::cout << "Choose time of day:\n";
        std::cout << "  1 - Day (6:00 - 17:59)\n";
        std::cout << "  2 - Night (18:00 - 5:59)\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        bool isDay;
        if (choice == 1) {
            isDay = true;
        }
        else if (choice == 2) {
            isDay = false;
        }
        else {
            std::cout << "Error: incorrect choice\n" << std::endl;
            return;
        }

        double sum = 0.0;
        int count = 0;

        for (int dayOfYear = 0; dayOfYear < totalDays; ++dayOfYear) {
            Date currentDate = dayIndexToDate(dayOfYear);


            if (currentDate.month != month) continue;

            if (isDay) {
                for (int h = 6; h <= 17; ++h) {
                    if (history[dayOfYear][h] != nullptr) {
                        sum += history[dayOfYear][h]->temperature;
                        ++count;
                    }
                }
            }
            else {
                for (int h = 0; h <= 5; ++h) {
                    if (history[dayOfYear][h] != nullptr) {
                        sum += history[dayOfYear][h]->temperature;
                        ++count;
                    }
                }
                for (int h = 18; h <= 23; ++h) {
                    if (history[dayOfYear][h] != nullptr) {
                        sum += history[dayOfYear][h]->temperature;
                        ++count;
                    }
                }
            }
        }

        if (count == 0) {
            std::cout << "Error: no observation for that month\n" << std::endl;
            return;
        }

        const char* months[] = {
            "", "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };

        std::cout << "Average " << (isDay ? "day" : "night") << " temperature for " << months[month] << ": " << (sum / count) << " °C (for " << count << " observation)" << std::endl;
    }

    void saveToFile() const {
        char filename[256];

        std::cout << "Enter filename: ";
        std::cin >> filename;

        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cout << "Error: file cannot be openned\n" << std::endl;
            return;
        }

        file << startDate.day << " " << startDate.month << " " << startDate.year << std::endl;
        file << startTime.hour << std::endl;

        int totalObs = 0;
        for (int i = 0; i < totalDays; ++i) {
            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                if (history[i][j] != nullptr) {
                    ++totalObs;
                }
            }
        }

        file << totalObs << std::endl;

        for (int i = 0; i < totalDays; ++i) {
            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                if (history[i][j] != nullptr) {
                    file << history[i][j]->date.day << " " << history[i][j]->date.month << " " << history[i][j]->date.year << " " << history[i][j]->time.hour << " " << history[i][j]->temperature << std::endl;
                }
            }
        }

        file.close();
        std::cout << "History saved in file \"" << filename << "\" (" << totalObs << " writes)" << std::endl;
    }

    void loadFromFile() {
        char filename[256];

        std::cout << "Enter filename: ";
        std::cin >> filename;

        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cout << "Error: file cannot be openned\n" << std::endl;
            return;
        }

        for (int i = 0; i < totalDays; ++i) {
            for (int j = 0; j < HOURS_PER_DAY; ++j) {
                if (history[i][j] != nullptr) {
                    delete history[i][j];
                    history[i][j] = nullptr;
                }
            }
        }

        file >> startDate.day >> startDate.month >> startDate.year;
        file >> startTime.hour;

        int totalObs;
        file >> totalObs;

        for (int i = 0; i < totalObs; ++i) {
            Date d;
            Time t;
            double temp;

            file >> d.day >> d.month >> d.year >> t.hour >> temp;

            if (!isValidDate(d) || !isValidTime(t)) {
                std::cout << "Warning: incorrecr write in file was skipped\n" << std::endl;
                continue;
            }

            int dayIndex = dateToDayIndex(d);

            if (dayIndex < 0 || dayIndex >= totalDays) {
                std::cout << "Warning: date is out of range was skipped." << std::endl;
                continue;
            }

            int hourIndex = t.hour;

            if (history[dayIndex][hourIndex] != nullptr) {
                delete history[dayIndex][hourIndex];
            }

            Observation* obs = new Observation;
            obs->date = d;
            obs->time = t;
            obs->temperature = temp;
            obs->isSet = true;

            history[dayIndex][hourIndex] = obs;
        }

        file.close();
        std::cout << "History was loaded from \"" << filename << "\" (" << totalObs << " writes)" << std::endl;
    }

};

int main() {
    std::cout << "========== THERMOMETR ==========\n";
    Thermometer thermometer;
    int choice;

    do {
        std::cout << " 1. Set start date and time\n";
        std::cout << " 2. Show start date and time\n";
        std::cout << " 3. Add observation\n";
        std::cout << " 4. Show temperature for date and time\n";
        std::cout << " 5. Set series of observation for date(24 hours)\n";
        std::cout << " 6. Average temperature for choosen date\n";
        std::cout << " 7. Average date/night temperaure for choosen month\n";
        std::cout << " 8. Save journal in file\n";
        std::cout << " 9. Load journal from file\n";
        std::cout << " 0. Exit\n" << std::endl;

        std::cout << "Choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Error: enter correct number(0-9)" << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            thermometer.setStartDateTime();
            break;
        case 2:
            thermometer.getStartDateTime();
            break;
        case 3:
            thermometer.setObservation();
            break;
        case 4:
            thermometer.getTemperature();
            break;
        case 5:
            thermometer.setDailyObservations();
            break;
        case 6:
            thermometer.getAverageDailyTemperature();
            break;
        case 7:
            thermometer.getAverageMonthlyTemperature();
            break;
        case 8:
            thermometer.saveToFile();
            break;
        case 9:
            thermometer.loadFromFile();
            break;
        case 0:
            std::cout << "Goodbye!\n" << std::endl;
            break;
        default:
            std::cout << "Error: incorrect choice\n" << std::endl;
        }
    } while (choice != 0);

    return 0;
}