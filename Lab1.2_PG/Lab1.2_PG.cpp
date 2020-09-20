#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

struct DATE {
    int day;
    int month;
    int year;
    void construct(string dateline) {
        string day_n, month_n, year_n;
        day_n = dateline[0] + dateline[1];
        month_n = dateline[3] + dateline[4];
        int i = 6;
        while(dateline[i]) {
            year_n += dateline[i];
            i++;
        }

        day = stoi(day_n);
        month = stoi(month_n);
        year = stoi(year_n);
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
    DATEline += to_string(year);

    printf("%s\n", DATEline.c_str());
    }
    void go_next(DATE *ARR, int i) {
        if(i != sizeof(ARR) / sizeof(ARR[0]) - 1) {
            i++;
            day = ARR[i].day;
            month = ARR[i].month;
            year = ARR[i].year;
        }
        else {
            printf("Its the last one in list");
        }
    }
    void go_back(DATE *ARR, int i) {
        if(i != 0) {
            i--;
            day = ARR[i].day;
            month = ARR[i].month;
            year = ARR[i].year;
        }
        else {
            printf("Its the first one on list");
        }
    }
};

DATE *array_construct();

int main() {
    DATE *D_ARR = array_construct();

    return 0;
}

DATE *array_construct() {
    ifstream DATES;
    DATES.open("dates.txt");
    string dateline;
    regex DATE_REGEX("(([0-2][1-9]|30)[-./\\](0[469]|11)[-./\\]([0-9]*)) || (([0-2][1-9]|3[0-1])[-./\\](0[1358]|1[02])[-./\\]([0-9]*)) || (([0-2][1-9])[-./\\]02[-./\\]([0-9]*))");
    int N = 0, i = 0;
    while(getline(DATES, dateline)) N++;
    DATES.seekg(0);
    DATE *D_ARR = new DATE[N];
    DATE *non_filtered_D_ARR = new DATE[N];
    while(getline(DATES, dateline)) {
        if (regex_match(dateline, DATE_REGEX)) {
            D_ARR[i].construct(dateline);
            i++;
        }
    }

    DATES.close();
    return D_ARR;
}
