#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <tuple>

using namespace std;

regex DATE_REGEX("(([0-2][1-9]|30)[-./](0[469]|11)[-./][1-9]([0-9]*))|(([0-2][1-9]|3[0-1])[-./](0[1358]|1[02])[-./][1-9]([0-9]*))|(([0-2][1-9])[-./]02[-./][1-9]([0-9]*))");

void num_changer(int &number);
bool leap_check(int year);

struct DATE {
    int day;
    int month;
    int year;
    bool leap = false;
    void construct(string dateline) {
        string day_n, month_n, year_n;
        int i = 6;
        while(dateline[i]) {
            year_n += dateline[i];
            i++;
        }
        day = (dateline[0] - '0') * 10 + dateline[1] - '0';
        month = (dateline[3] - '0') * 10 + dateline[4] - '0';
        year = stoi(year_n);
        
        leap = leap_check(year);

        if (month == 2) {
            if (leap == false && day == 29) {
                day = 0;
            }
        }
    }
    void output() {
        string DATEline = "";

        if (day < 10) DATEline += "0" + to_string(day) + ".";
        else DATEline += to_string(day) + ".";
    
        if (month < 10) DATEline += "0" + to_string(month) + ".";
        else DATEline += to_string(month) + ".";
    
        if (year < 1000) {
        int zeroes = 0;
        while (pow(10.0, float(zeroes)) < year) zeroes++;
        while (zeroes != 0) {
            DATEline += "0";
            zeroes--;
        }
    }  
    DATEline += to_string(year) + ' ';

    printf("%s", DATEline.c_str());
    }
    
};

tuple<DATE*, int> array_construct();
tuple<DATE*, int> array_filter(DATE* NF_D_ARR, int N);
void ZDC(DATE &date); //zero day case
void LDC(DATE &date); //last day case
DATE next_date(DATE date);
DATE prev_date(DATE date);
void GEN_OP(DATE* D_ARR, int i, int N);
void time_travel_forward(DATE date);
void time_travel_backward(DATE date);
DATE ST_DATE_IN(string diraction);
void task1(DATE *D_ARR, int N);
void task2(DATE *D_ARR, int N);

int main() {
    DATE *D_ARR, ST_DATE;
    string STARTING_DATE;
    int N;
    tie(D_ARR, N) = array_construct();
    int number;
	num_changer(number);
	while (number) {
		if (number == 1) task1(D_ARR, N);
        if (number == 2) task2(D_ARR, N); 
        if (number == 3) time_travel_forward(ST_DATE_IN("forward"));
        if (number == 4) time_travel_backward(ST_DATE_IN("backward"));
        num_changer(number);
        printf("\n");
    }
    return 0;
}

void num_changer(int &N) {
    printf("\n");
	cout << "Enter the number or 0 to close - ";
	cin >> N;
}

tuple<DATE*, int> array_construct() {
    ifstream DATES;
    string dateline;
    
    int N = 0, i = 1;   
    
    DATES.open("dates.txt");
    while(getline(DATES, dateline)) {
        if (regex_match(dateline, DATE_REGEX)) {
            N++;
        }
        else {
            printf("REGEX ERROR LINE %i\n", i);
        }
        i++;
    }
    printf("\n");
    DATE *D_ARR = new DATE[N];
    DATE *NF_D_ARR = new DATE[N];
    i = 0;
    DATES.close();
    DATES.open("dates.txt");

    while(getline(DATES, dateline)) {
        if (regex_match(dateline, DATE_REGEX)) {
            NF_D_ARR[i].construct(dateline);
            i++;
        }
    }
    DATES.close();
    tie(D_ARR, N) = array_filter(NF_D_ARR, N);
    return make_tuple(D_ARR, N);
}

tuple<DATE*, int> array_filter(DATE *NF_D_ARR, int N) {
    int newN = 0;
    for (int i = 0; i < N; i++) {
        if (NF_D_ARR[i].day != 0) {
            newN++;
        }
    }
    
    DATE* D_ARR = new DATE[newN];
    int k = 0;
    for (int i = 0; i < N; i++) {
        if (NF_D_ARR[i].day != 0) {
            D_ARR[k].day = NF_D_ARR[i].day;
            D_ARR[k].month = NF_D_ARR[i].month;
            D_ARR[k].year = NF_D_ARR[i].year;
            D_ARR[k].leap = NF_D_ARR[i].leap;
            k++;
        }
    }
    return make_tuple(D_ARR, newN);
}

void ZDC(DATE &date) {
    if (date.day == 0) {
        if (date.month == 3) {
            date.day = 28 + date.leap;
            date.month -= 1;
        }
        else {
            if (date.month < 8) {
                if (date.month == 1) {
                    date.day = 31;
                    date.month = 12;
                    date.year--;
                    date.leap = leap_check(date.year);
                }
                else {
                    date.month--;
                    date.day = 30 + date.month % 2;
                }
            }
            else {
                date.month--;
                date.day = 31 - date.month % 2;
            }
        }
    }
}

void LDC(DATE &date) {
    if(date.month == 2) { 
        if(date.day > (28 + (date.leap))) {
            date.month++;
            if(date.month > 12) {
                date.year++;
                date.month = 1;
                date.leap = leap_check(date.year);
            }
            date.day = 1;
        }
    }
    else {
        if (date.month < 8) {
            if(date.day > (30 + date.month % 2)) {
                date.month++;
                if(date.month > 12) {
                    date.year++;
                    date.month = 1;
                    date.leap = leap_check(date.year);
                }
                date.day = 1;
            }
        }
        else {
            if(date.day > (31 - date.month % 2)) {
                date.month++;
                if(date.month > 12) {
                    date.year++;
                    date.month = 1;
                    date.leap = leap_check(date.year);
                }
                date.day = 1;
            }
        }
    }
}

DATE next_date(DATE date) {
    date.day += 1;
    LDC(date);
    return date;
}

DATE prev_date(DATE date) {
    date.day -= 1;
    ZDC(date);
    return date;
}

void GEN_OP(DATE *D_ARR, int i, int N) {
    printf("%i) ", i + 1);
    D_ARR[i].output();
    prev_date(D_ARR[i]).output();
    next_date(D_ARR[i]).output();
    printf("\n");
}

bool leap_check(int year) {
    bool leap = false;
    if (year % 100 == 0) {
        if (year % 400 == 0) leap = true;
    }
    else {
        if (year % 4 == 0) leap = true;
    }
    return leap;
}

void task1(DATE *D_ARR, int N) {
    for(int i = 0; i < N; i++) {
        GEN_OP(D_ARR, i, N);
    }

}

void task2(DATE *D_ARR, int N) {
    for (int i = 1; i < N - 1; i++) {
        if (D_ARR[i].year == D_ARR[i - 1].year && D_ARR[i].year == D_ARR[i + 1].year){
            GEN_OP(D_ARR, i, N);
        }
    }
}

void time_travel_forward(DATE date) {

    int days;
    printf("Enter the amount of days to add: ");
    cin >> days;

    while (days > 0) {
        date.day++;
        LDC(date);
        days--;
    }
    date.output();
}

void time_travel_backward(DATE date) {

    int days;
    printf("Enter the amount of days to substruct: ");
    cin >> days;
    
    while (days != 0) {
        date.day--;
        ZDC(date);
        days--;
    }
    date.output();
}
DATE ST_DATE_IN(string diraction) {
    DATE ST_DATE;
    string STARTING_DATE;
    cout << "Pls enter the starting date to time travel " + diraction + "(xx.xx.xxxx or with any other delimeter and year) - ";
    cin >> STARTING_DATE;
    while (regex_match(STARTING_DATE, DATE_REGEX) != true) {
        cout << "Pls enter valid date - ";
        cin >> STARTING_DATE;
    }
    ST_DATE.construct(STARTING_DATE);
    while (ST_DATE.day == 0) {
        cout << "Pls enter valid date - ";
        cin >> STARTING_DATE;
        while (regex_match(STARTING_DATE, DATE_REGEX) != true) {
            cout << "Pls enter valid date - ";
            cin >> STARTING_DATE;
        }
        ST_DATE.construct(STARTING_DATE);
    }
    return ST_DATE;
}