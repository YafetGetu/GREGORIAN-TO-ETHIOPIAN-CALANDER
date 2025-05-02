#include <iostream>
#include <iomanip> // Using this library to help for alignment

using namespace std;

int main() {
    start:
    int year;
    cout << "Enter year(Julian or Gregorian):";
    cin >> year;

    // Constants
    const string monthNames[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    const int daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    const string ethiopianMonthNames[13] = {
        "Meskerem", "Tikimt", "Hidar", "Tahisas", "Tir", "Yekatit",
        "Megabit", "Miyazia", "Ginbot" ,"Sene", "Hamle", "Nehase", "Pagume"
    };
    int daysInMonthEthiopian[13] = {
        30, 30, 30, 30, 30, 30,
        30, 30, 30, 30, 30, 30, 5
    };
    const string daysOfWeek[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    // Month codes for non-leap and leap years
    const int monthCodes[12] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    const int monthCodesLeap[12] = {6, 2, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};

    // Determine if it's a leap year
    bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (year<1752){
        isLeapYear = (year % 4 == 0);
    }
    bool isLeapYearEthiopian = ((year - 8) % 4 == 3);


    // Adjust days in months for leap years
    int daysInMonthAdjusted[12];
    for (int i = 0; i < 12; ++i) {
        daysInMonthAdjusted[i] = daysInMonth[i];
    }
    if (isLeapYear) {
        daysInMonthAdjusted[1] = 29; // February in a leap year
    }
    if (isLeapYearEthiopian) {
        daysInMonthEthiopian[12] = 6; // Pagume in a leap year
    }

    // Calculate Year Code
    int YY = year % 100;
    int yearCode = (YY + (YY / 4)) % 7;

    // Calculate Century Code
    int century = year / 100;
    int centuryCode;
    if (century % 4 == 0) {
        centuryCode = 6;
    } else if (century % 4 == 1) {
        centuryCode = 4;
    } else if (century % 4 == 2) {
        centuryCode = 2;
      if (year<1753)
        centuryCode = (18-(year/100)%7);
    } else {
        centuryCode = 0;
    }

    // Calculate the day of the week for January 1st
    int monthCode = isLeapYear ? monthCodesLeap[0] : monthCodes[0];
    int total = (yearCode + monthCode + centuryCode + 1) % 7;
    int firstDayOfWeek = total; // 0 is Sunday, 1 is Monday, ..., 6 is Saturday
    if (year<1753)
        firstDayOfWeek = total-3;
    if (year<1700)
        firstDayOfWeek = total+3;
    if (year<1500)
        firstDayOfWeek = total;
    if (year<1400)
        firstDayOfWeek = total+1;
    if (year<1300)
        firstDayOfWeek = total;
    if (year<1000)
        firstDayOfWeek = total-2;
    if (year<900)
        firstDayOfWeek = total+4;

    if (year<700)
        firstDayOfWeek = total;
    if (year<600)
        firstDayOfWeek = total+2;
    if (year<500)
        firstDayOfWeek = total-6;
    if (year<300)
        firstDayOfWeek = total;
    if (year<200)
        firstDayOfWeek = total-1;
    if (year<100)
        firstDayOfWeek = total-2;

    // Ethiopian starting date
    int ethiopianDay = ((year-9)%4)==3 ? 22 : 23; // Tahisas 22 or 23 for gregorian  date
      if (year==1900) // including 1900 and the years before the jan 1 day wasn't constant so we use if statments.
        ethiopianDay = 23;
      else if (year>1800 && year<1900)
        ethiopianDay = ((year-9)%4)==3 ? 23 : 24;
      else if (year==1800)
        ethiopianDay = 24;
      else if (year>1752 && year<1800)
        ethiopianDay = ((year-9)%4)==3 ? 24 : 25;
      else if (year>2100)
        ethiopianDay = ((year-9)%4==3 ? 21 : 22);
      else if (year<=1752)
        ethiopianDay = ((year-9)%4==3 ? 6 : 6); // Found date for Julian calander jan 1
    int ethiopianMonth = 4; // Tahisas
      if (year<1752){
        ethiopianMonth = 5; // Tir
      }


    // Print the calendar
    for (int month = 0; month < 12; ++month) {
        cout << "     " << monthNames[month] << " " << year << " / "
             << ethiopianMonthNames[ethiopianMonth - 1] << "-"
             << ethiopianMonthNames[(ethiopianMonth % 13 == 0) ? 1 : (ethiopianMonth % 13)]
             <<"  " << year-8 <<"-"<<year-7
             << endl;
        cout << "|-------------------------------------------------------|" << endl;
        cout << "|  Sun  |  Mon  |  Tue  |  Wed  |  Thu  |  Fri  |  Sat  |" << endl;
        cout << "|-------------------------------------------------------|" << endl;

        // Print leading spaces for the first week if the first day of the week is
        // Sunday then there is no leading spaces.
        for (int i = 0; i < firstDayOfWeek; ++i) {

            cout << "|       ";
        }

        // Print all days of the month and Ethiopian dates below

        for (int day = 1; day <= daysInMonthAdjusted[month]; ++day) {
            if (year == 1752 && month == 8 && day > 2 && day < 14) {


                day = 14;// Skip the missing days in September 1752

            }


            cout << "|" << setw(7) << day;

            if ((day + firstDayOfWeek) % 7 == 0) {
                cout << "|" << endl; // When ever the week ends it outputs |.

                //To Print Ethiopian dates
                for (int i = day - 6; i <= day; ++i) {
                    if (i <= 0) {
                        cout << "|       ";
                    } else {
                        cout << "|" << setw(2) << ethiopianDay << "     ";
                        ethiopianDay++;
                        if (ethiopianDay > daysInMonthEthiopian[ethiopianMonth - 1]) {
                            ethiopianDay = 1;
                            ethiopianMonth++;
                            if (ethiopianMonth > 13) {
                                ethiopianMonth = 1;
                            }
                        }
                    }
                }
                cout << "|" << endl;
                cout << "|-------------------------------------------------------|" << endl;
            }
        }

        // If the last day of the month does not end the week, print remaining spaces
        if ((daysInMonthAdjusted[month] + firstDayOfWeek) % 7 != 0) {
            int remainingDays = 7 - (daysInMonthAdjusted[month] + firstDayOfWeek) % 7;
            for (int i = 0; i < remainingDays; ++i) {
                cout << "|       ";
            }
            cout << "|" << endl;

            // Print Ethiopian dates for the remaining days of the last week
            for (int i = (daysInMonthAdjusted[month] - ((daysInMonthAdjusted[month] + firstDayOfWeek) % 7)); i < daysInMonthAdjusted[month]; ++i) {
                cout << "|" << setw(2) << ethiopianDay << "     ";
                ethiopianDay++;

                if (ethiopianDay > daysInMonthEthiopian[ethiopianMonth - 1]) {
                    ethiopianDay = 1;
                    ethiopianMonth++;
                    if (ethiopianMonth > 13) {
                        ethiopianMonth = 1;
                    }
                }
            }
            for (int i = (daysInMonthAdjusted[month] + firstDayOfWeek) % 7; i < 7; ++i) {
                cout << "|       ";
            }
            cout << "|" << endl;
            cout << "|-------------------------------------------------------|" << endl;
        }

        // Calculate the first day of the next month
        if (month < 11) {
            firstDayOfWeek = (firstDayOfWeek + daysInMonthAdjusted[month]) % 7;
        }
    }
    cout << "Do you want to see another year (Y or y for yes)" << endl;
    string ans;
    cin >> ans;

    if (ans == "Y" || ans == "y")
        goto start;

    return 0;
}
