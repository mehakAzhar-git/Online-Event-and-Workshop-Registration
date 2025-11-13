#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
class Person {
protected:
    string name, email;

public:
    Person(string n = "", string e = "") : name(n), email(e) {}
    virtual void displayInfo() = 0;
};
class Event {
public:
    int id;
    string title;
    string date;
    string time;
    string venue;
    string description;
    double fee;

    Event(int i = 0, string t = "", string d = "", string tm = "", string v = "", string desc = "", double f = 0.0)
        : id(i), title(t), date(d), time(tm), venue(v), description(desc), fee(f) {}

    void displayEvent() {
        cout << "\n--------------------------------------";
        cout << "\nEvent ID   : " << id;
        cout << "\nTitle      : " << title;
        cout << "\nDate       : " << date;
        cout << "\nTime       : " << time;
        cout << "\nVenue      : " << venue;
        cout << "\nDescription: " << description;
        cout << "\nFee        : Rs." << fee;
        cout << "\n--------------------------------------\n";
    }
};
class Registration {
public:
    string userName;
    string eventTitle;

    Registration(string u = "", string e = "") : userName(u), eventTitle(e) {}

    void saveToFile() {
        ofstream fout("registrations.txt", ios::app);
        fout << userName << " | " << eventTitle << "\n";
        fout.close();
    }

    static void showRegistrations() {
        ifstream fin("registrations.txt");
        string line;
        cout << "\n===== All Registrations =====\n";
        while (getline(fin, line)) {
            cout << line << "\n";
        }
        fin.close();
    }
};

class Admin : public Person {
public:
    Admin(string n = "", string e = "") : Person(n, e) {}

    void displayInfo() override {
        cout << "\n[ADMIN] Name: " << name << " | Email: " << email << "\n";
    }

    void addEvent(vector<Event>& events) {
        int id;
        string title, date, time, venue, desc;
        double fee;

        cout << "\nEnter Event ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Date (DD/MM/YYYY): ";
        getline(cin, date);
        cout << "Enter Time (HH:MM AM/PM): ";
        getline(cin, time);
        cout << "Enter Venue: ";
        getline(cin, venue);
        cout << "Enter Description: ";
        getline(cin, desc);
        cout << "Enter Fee: ";
        cin >> fee;

        events.push_back(Event(id, title, date, time, venue, desc, fee));
        cout << "\n? Event added successfully!\n";
    }

    void viewRegistrations() {
        Registration::showRegistrations();
    }
};
class User : public Person {
public:
    User(string n = "", string e = "") : Person(n, e) {}

    void displayInfo() override {
        cout << "\n[USER] Name: " << name << " | Email: " << email << "\n";
    }

    void viewEvents(vector<Event>& events) {
        cout << "\n===== Available Events =====\n";
        if (events.empty()) {
            cout << "No events available yet!\n";
            return;
        }
        for (size_t i = 0; i < events.size(); i++) {
            events[i].displayEvent();
        }
    }

    void registerEvent(vector<Event>& events) {
        if (events.empty()) {
            cout << "\nNo events available to register.\n";
            return;
        }

        int id;
        cout << "\nEnter Event ID to Register: ";
        cin >> id;

        bool found = false;
        for (size_t i = 0; i < events.size(); i++) {
            if (events[i].id == id) {
                Registration r(name, events[i].title);
                r.saveToFile();
                cout << "\nCongratulations " << name << "! You have successfully registered for '" << events[i].title << "'.\n";
                found = true;
                break;
            }
        }
        if (!found)
            cout << "\n Event not found!\n";
    }
};
void preloadEvents(vector<Event>& events) {
    events.push_back(Event(101, "AI & Machine Learning Workshop", "05/09/2025", "10:00 AM", "Main Auditorium", "Learn the basics of AI & ML with live projects.", 1500));
    events.push_back(Event(102, "Digital Marketing Bootcamp", "10/09/2025", "02:00 PM", "Seminar Hall 2", "Master SEO, social media marketing & paid ads.", 1200));
    events.push_back(Event(103, "Cyber Security Training", "15/09/2025", "11:00 AM", "Lab 3", "Hands-on ethical hacking & cyber defense training.", 2000));
}
int main() {
    vector<Event> events;
    preloadEvents(events);
    Admin admin("Mehak", "admin@event.com");

    int choice;
    while (true) {
        cout << "\n\t\t\t\t\t\t========== Online Event & Workshop Registration ==========";
        cout << "\n1. Admin Login";
        cout << "\n2. User Login";
        cout << "\n3. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int adminChoice;
            while (true) {
                cout << "\n===== Admin Menu =====";
                cout << "\n1. Add Event";
                cout << "\n2. View Registrations";
                cout << "\n3. Back";
                cout << "\nEnter Choice: ";
                cin >> adminChoice;

                if (adminChoice == 1) {
                    admin.addEvent(events);
                } else if (adminChoice == 2) {
                    admin.viewRegistrations();
                } else if (adminChoice == 3) {
                    break;
                } else {
                    cout << "Invalid choice!\n";
                }
            }
        } 
        else if (choice == 2) {
            string uname, email;
            cout << "\nEnter Your Name: ";
            cin.ignore();
            getline(cin, uname);
            cout << "Enter Your Email: ";
            getline(cin, email);

            User user(uname, email);
            int userChoice;
            while (true) {
                cout << "\n===== User Menu =====";
                cout << "\n1. View Events";
                cout << "\n2. Register for Event";
                cout << "\n3. Back";
                cout << "\nEnter Choice: ";
                cin >> userChoice;

                if (userChoice == 1) {
                    user.viewEvents(events);
                } else if (userChoice == 2) {
                    user.registerEvent(events);
                } else if (userChoice == 3) {
                    break;
                } else {
                    cout << "Invalid choice!\n";
                }
            }
        } 
        else if (choice == 3) {
            cout << "\nThank you for using the system. Goodbye!\n";
            break;
        } 
        else {
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}
