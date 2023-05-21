#include <iostream>
#include <array>
#include <iomanip>

using namespace std;
array<string, 7> g_weekdays{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

int emptyDays(string p_weekday)
{
    for (int indexWeekday = 0; indexWeekday < 7; indexWeekday++)
    {
       if (g_weekdays[indexWeekday] == p_weekday)
       {
            for (int numberEmptyDays = 0; numberEmptyDays < indexWeekday; numberEmptyDays++)
            {
                cout << ".. ";
            }
            return indexWeekday;
       }
    }
    return 0;
}

void outputDate(int p_startIndexDay, int p_nDays)
{
    for (int dayNumber = 0; dayNumber < p_nDays; dayNumber++)
    {
        cout << setfill('.') << setw(2) << dayNumber+1 << " ";
        if (!((dayNumber+1+p_startIndexDay)%7)) 
            cout << endl;
    }
    return;
}

int main() 
{
    int nDays;
    string weekday;
    cin >> nDays >> weekday;
    int startIndexDay;
    startIndexDay = emptyDays(weekday);
    outputDate(startIndexDay, nDays); 

    return 0;
}
