#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

using namespace std;

bool prov_action(int s) {
	if (s >= 0 && s <= 4) {
		return true;
	}
	else {
		return false;
	}
}

class clocks {
private: 
	int sec, min, hours;
	int sec0, min0, hours0;

public:
	clocks() {
		sec = rand() % 60;
		min = rand() % 60;
		hours = rand() % 24;
		sec0 = sec;
		min0 = min;
		hours0 = hours;
	}

	void install_time() {
		short c = 0;
		cout << "Enter seconds (0-59): " << '\n';
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			c++;
			cin >> sec;
		} while (sec < 0 || sec >= 60);

		c = 0;
		cout << "Enter minutes (0-59): " << '\n';
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			c++;
			cin >> min;
		} while (min < 0 || min >= 60);

		c = 0;
		cout << "Enter hours (0-23): " << '\n';
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			c++;
			cin >> hours;
		} while (hours < 0 || hours >= 24);
		cout << "The time was set successfully" << '\n';
	}

	void print_time() {
		cout << "Time now: " << hours << " hours " << min << " minutes " << sec << " seconds\n";
	}

	void difference() {
		int ins = hours * 3600 + min * 60 + sec;
		int zd = hours0 * 3600 + min0 * 60 + sec0;
		int dif = abs(ins - zd);

		int dhours = dif / 3600;
		int dmin = (dif % 3600) / 60;
		int dsec = dif % 60;

		cout << "The difference is " << dhours << " hours " << dmin << " minutes " << dsec << " seconds\n";
	}

	void sdv() {
		char s;
		short c = 0;
		cout << "Choose which way the time shift will be: '+' or '-'\n";
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			cin >> s;
			c += 1;
		} while (s != '+' && s != '-');

		c = 0;
		int h, m, sc;

		cout << "How much hours to set the offset:\n";
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			cin >> h;
			c += 1;
		} while (h < 0);

		c = 0;
		cout << "How much minutes to set the offset:\n";
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			cin >> m;
			c += 1;
		} while (m < 0);

		c = 0;
		cout << "How much seconds to set the offset:\n";
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			cin >> sc;
			c += 1;
		} while (sc < 0);

		int totalsec = hours * 3600 + min * 60 + sec;
		int sdvsec = h * 3600 + m * 60 + sc;

		if (s == '+') {
			totalsec += sdvsec;
		}
		else {
			totalsec -= sdvsec;
		}

		totalsec %= 24 * 3600;
		if (totalsec < 0) {
			totalsec += 24 * 3600;
		}

		hours = totalsec / 3600;
		min = (totalsec % 3600) / 60;
		sec = totalsec % 60;

		cout << "Time shifted successfully\n";
	}
};


int main() {
	srand(time(nullptr));
	
	int s;
	clocks tim;
	short c = 0;
	do {
		cout << "Select an action: \n" << "1. Set the time\n" << "2. Find out the time\n" << "3. Calculate the difference between the set time and the set time\n"
			<< "4. Shift the time by a preset offset\n" << "0. Exit\n" << '\n';
		do {
			if (c >= 1) {
				cout << "Input error! Try again\n";
			}
			cin >> s;
			c += 1;
		} while (!prov_action(s));
		
		c = 0;

		switch (s) {
		case 1: 
			tim.install_time();
			break;
		case 2: 
			tim.print_time();
			break;
		case 3: 
			tim.difference();
			break;
		case 4: 
			tim.sdv();
			break;
		default: break;
		}
		
		cout << '\n';
	} while (s != 0);
}