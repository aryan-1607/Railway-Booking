#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct Train
{
    string name;
    int train_no;
    int seatsavailable;
};

class Reservation_system
{
private:
    vector<Train> trains;
    map<int, vector<int>> bookings;
    int nextBookingId = 1;

public:
    Reservation_system()
    {
        trains.push_back({"Vande Bharat", 1265, 96});
        trains.push_back({"Rajdhani Express", 1384, 106});
        trains.push_back({"Local passenger10X", 1655, 85});
    }

    void displayTrains()
    {
        cout << "Trains  available: \n";
        for (auto &t : trains)
        {
            cout << "Train name: " << t.name << endl
                 << "Train number: " << t.train_no << endl
                 << "No. of seats available are: " << t.seatsavailable << endl;
        }
    }

    void bookTicket()
    {
        int trainno, seats;
        cout << "Enter train number: ";
        cin >> trainno;
        cout << "Enter number of seats: ";
        cin >> seats;

        int foundIndex = -1;
        for (int i = 0; i < (int)trains.size(); i++)
        {
            if (trains[i].train_no == trainno)
            {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex != -1 && trains[foundIndex].seatsavailable >= seats)
        {
            trains[foundIndex].seatsavailable -= seats;
            bookings[nextBookingId] = {trainno, seats};
            cout << "Booking successful. Booking ID: " << nextBookingId << "\n";
            nextBookingId++;
        }
        else
        {
            cout << "Booking failed. Not enough seats. Sorry for the inconvenience.\n";
        }
    }

    void cancelTicket()
    {
        int bookingId;
        cout << "Enter booking ID: ";
        cin >> bookingId;
        auto it = bookings.find(bookingId);
        if (it != bookings.end())
        {
            int trainId = it->second[0];
            int seats = it->second[1];
            auto tit = find_if(trains.begin(), trains.end(), [&](Train &t)
                               { return t.train_no == trainId; });
            if (tit != trains.end())
            {
                tit->seatsavailable += seats;
            }
            bookings.erase(it);
            cout << "Cancellation successful.\n";
        }
        else
        {
            cout << "Invalid booking ID.\n";
        }
    }

    void displayBookings()
    {
        if (bookings.empty())
        {
            cout << "No bookings Found. Please recheck the details entered" << endl;
            return;
        }
        cout << "Current Bookings: " << endl;
        for (auto &b : bookings)
        {
            cout << "Booking ID: " << b.first << "  Train ID: " << b.second[0] << "  Seats: " << b.second[1] << "\n";
        }
    }

    void menu()
    {
        int choice;

        do
        {
            cout << "\t\t\t\t==========================Welcome to Train Reservation System==========================\t\t\t" << endl;
            cout << "Choose What you want to do:\n 1.Display trains\n 2.Book Ticket\n 3. Cancel Ticket\n 4.Display Bookings\n 5. Exit\n";
            cin >> choice;
            switch (choice)
            {
            case 1:
                displayTrains();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                displayBookings();
                break;
            case 5:
                cout << "Exiting the system. Thank you for using our service. Please come again\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 5);
    }
};
int main()
{
    Reservation_system rs;
    rs.menu();
    return 0;
}