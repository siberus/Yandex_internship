#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;
//int g_time = 0;
int g_passengersOnPlace = 0;

struct Passenger 
{
    int row;
    char seat;
    int a;
    int currentRow{0};
    int time {0};
    bool inPlace {false};
};

array<string, 30> g_seats{""};

void inputRowSeat(int & p_row, char & p_seat, string p_rowSeat)
{
    p_seat = p_rowSeat[p_rowSeat.length()-1];
    p_row = stoi(p_rowSeat.substr(0, p_rowSeat.length()-1));
    //cout << "row: " << p_row << " seat: " << p_seat << endl;

    return;
}

void initialPassengers(vector<Passenger> & p_passengers, int p_a, int p_row, char p_seat)
{
    Passenger curPassenger;
    curPassenger.a = p_a;
    curPassenger.row = p_row;
    curPassenger.seat = p_seat;
    p_passengers.push_back(curPassenger);
    return;
}
void printPassenger(vector<Passenger>  p_passengers)
{   for (int i = 0; i < p_passengers.size(); i++)
    {
        cout << "Passenger: " << i+1 << endl;
        cout << "Row: " << p_passengers[i].row << endl;
        cout << "Seat: " << p_passengers[i].seat << endl;
        cout << "Composure: " << p_passengers[i].a << endl;
        cout << "___________________"  << endl;
    }


    return;
}

int timeIfNeedChange(int p_row, char p_seat)
{
    int changeTime = 0;
    //Для средних сиидений
    if (p_seat == 'B')
    {
       if (g_seats[p_row-1].find("C") !=  string::npos)
       {
        changeTime +=5;
       }
    }
    if (p_seat == 'E')
    {
       if (g_seats[p_row-1].find("D") !=  string::npos)
       {
        changeTime +=5;
       }
    }
    //Для дальних сидений
    if (p_seat == 'A')
    {
       if ((g_seats[p_row-1].find("C")  !=  string::npos) || (g_seats[p_row-1].find("B")  !=  string::npos))
       {
        changeTime +=5;
       }
       if ((g_seats[p_row-1].find("C")  !=  string::npos) && (g_seats[p_row-1].find("B")  !=  string::npos))
       {
        changeTime +=10;
       }
    }
    if (p_seat == 'F')
    {
       if ((g_seats[p_row-1].find("D")  !=  string::npos) || (g_seats[p_row-1].find("E")  !=  string::npos))
       {
        changeTime +=5;
       }
       if ((g_seats[p_row-1].find("D")  !=  string::npos) && (g_seats[p_row-1].find("E")  !=  string::npos))
       {
        changeTime +=10;
       }

    }
    

    return changeTime;
}

void seatDown(Passenger p_passenger)
{
    if(p_passenger.currentRow == p_passenger.row)
    {
        p_passenger.inPlace = true;
        g_seats[p_passenger.row-1].push_back(p_passenger.seat);
        g_passengersOnPlace++;

    }
    else
    {
        p_passenger.currentRow = p_passenger.row;
        p_passenger.time += (1 + p_passenger.a + timeIfNeedChange(p_passenger.row, p_passenger.seat));
    }
    
    
}

void nextStep(vector<Passenger>  p_passengers)
{

    //g_time++;
    //for (auto it = vec.begin(); it != vec.end(); it++)
   // for (auto &currentPassenger : p_passengers)
    for (auto it = p_passengers.begin(); it != p_passengers.end(); it++)
    {
        
        int index = distance(p_passengers.begin(), it);
        int maxAvailableRow;
        int nextPassenger;

        if (!p_passengers[index].inPlace)
        {
            //Если пассажир первый то его сразу садим
           if (index == 0)
           {
            seatDown(p_passengers[index]);
           }
           //Если второй и последующие проверяем как далеко могут продвинутся
           else
           {
                maxAvailableRow = p_passengers[index-1].row;
                nextPassenger = index-1;
                //Определяем максимальный ряд, путь до которого свободен и номер пассажира впереди
                for (int i = index-1; i <= 0; i--)
                {
                    if(p_passengers[i].inPlace)
                    {
                        maxAvailableRow = p_passengers[i].row;
                        nextPassenger = i+1;
                    }
                }
                //Если путь свободен до нужноо ряда, то начинаем усаживать
                if (maxAvailableRow <= p_passengers[index].row)
                {
                    seatDown(p_passengers[index]);
                }
                //Если путь не свободен до нужного ряда, то продвигаемся вперед и ждем
                else
                {
                    p_passengers[index].currentRow = maxAvailableRow - 1;
                    p_passengers[index].time = p_passengers[nextPassenger-1].time;

                }
           }
        }
    }
    return;
}

int main() 
{

    int numberOfPassengers;
    cin >> numberOfPassengers; 
    vector<Passenger> passengers;
    for (int i = 0; i < numberOfPassengers; i++)
    {
        int a;
        string rowSeat;
        cin >> a >> rowSeat;
        int row;
        char seat;
        inputRowSeat(row, seat, rowSeat);
        initialPassengers(passengers, a, row, seat);
    }
    //printPassenger(passengers);
    while (g_passengersOnPlace < numberOfPassengers)
    {
        nextStep(passengers);
    }
    int totalTime{0};
    for (const auto &p: passengers)
    {   
        if (p.time > totalTime)
        {
            totalTime = p.time;
        }
    }
    cout << totalTime;  


    return 0;
}
