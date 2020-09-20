#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <tuple>

using namespace std;

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
        if (year % 100 == 0) {
            if (year % 400 == 0) leap = true;
        }
        else if (year % 4 == 0) leap = true;

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
    void next_date(DATE *D_ARR, int i, int N) {
        if(i < N - 1) {
            D_ARR[i+1].output();
        }
        else {
            printf(" LAST ONE");
        }
    }
    void prev_date(DATE *D_ARR, int i) {
        if(i != 0) {
            D_ARR[i-1].output();
        }
        else {
            printf(" FIRST ONE ");
        }
    }
};

tuple<DATE*, int> array_construct();
tuple<DATE*, int> array_filter(DATE* NF_D_ARR, int N);
void GEN_OP(DATE* D_ARR, int i, int N);

int main() {
    DATE *D_ARR;
    int N;
    tie(D_ARR, N) = array_construct();
    
    for(int i = 0; i < N; i++) {
        GEN_OP(D_ARR, i, N);
    }

    for (int i = 1; i < N - 1; i++) {
        if (D_ARR[i].year == D_ARR[i - 1].year && D_ARR[i].year == D_ARR[i + 1].year) {
            GEN_OP(D_ARR, i, N);
        }
    }

    return 0;
}

tuple<DATE*, int> array_construct() {
    ifstream DATES;
    string dateline;
    regex DATE_REGEX("(([0-2][1-9]|30)[-./](0[469]|11)[-./]([0-9]*))|(([0-2][1-9]|3[0-1])[-./](0[1358]|1[02])[-./]([0-9]*))|(([0-2][1-9])[-./]02[-./]([0-9]*))");
    int N = 0, i = 0;   
    
    DATES.open("dates.txt");
    while(getline(DATES, dateline)) {
        if (regex_match(dateline, DATE_REGEX)) {
            N++;
        }
    }
    DATE *D_ARR = new DATE[N];
    DATE *NF_D_ARR = new DATE[N];

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

void GEN_OP(DATE *D_ARR, int i, int N) {
    printf("%i) ", i + 1);
    D_ARR[i].output();
    D_ARR[i].prev_date(D_ARR, i);
    D_ARR[i].next_date(D_ARR, i, N);
    printf("\n");
}