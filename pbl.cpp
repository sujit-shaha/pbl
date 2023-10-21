#include <iostream>
#include <vector>
#include <string>
#include<fstream>
using namespace std;

class Donor {
public:
    Donor(const string& name, const string& bloodType)
        : name(name), bloodType(bloodType) {}

    void display() const {
        cout << "Name: " << name << " | Blood Type: " << bloodType << endl;
    }

    const string& getBloodType() const {
        return bloodType;
    }

private:
    string name;
    string bloodType;
};

class BloodBank {
public:
    void addDonor(const Donor& donor) {
        donors.push_back(donor);
    }

    void searchDonors(const string& bloodType) {
        cout << "Donors with Blood Type " << bloodType << ":" << endl;
        // for (const Donor& donor : donors) {
        //     if (donor.getBloodType() == bloodType) {
        //         donor.display();
        //     }
        // }
        ifstream fin;
        fin.open("bloodBankDonar.txt");
    if (!fin.is_open()) {
        cerr << "Error opening file!" <<endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        // std::istringstream iss(line);
        string name, blood;
        if (fin >> name >> blood) {
            if (blood == bloodType) {
                std::cout << "Name: " << name << ", Blood Type: " << blood << std::endl;
            }
        }
    }
    fin.close();
}
    

    void displayNotification() const {
        cout << "Notifications: ";
        
        if (notification.empty()) {
            cout << "No notifications." << endl;
        } else {
            for (const string& message : notification) {
                cout << message << " | ";
            }
            cout << endl;
        }
    }

    void createRequest(const string& requestMessage) {
        notification.push_back(requestMessage);
    }

private:
    vector<Donor> donors;
    vector<string> notification;
};

int main() {
    BloodBank bloodBank;
    ifstream fin;
    ofstream fout;


    while (true) {
        cout<<endl;
        cout<<"***************************************"<<endl;
        cout << "Blood Bank Management System Menu:" << endl;
        cout << "1. Add Donor" << endl;
        cout << "2. Search Donors" << endl;
        cout << "3. Display Notifications" << endl;
        cout << "4. Create Blood Request" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout<<endl;

        switch (choice) {
            case 1: {
                string name, bloodType;
                cout << "Enter donor's name: ";
                cin >> name;
                cout << "Enter donor's blood type: ";
                cin >> bloodType;
                Donor donor(name, bloodType);
                bloodBank.addDonor(donor);
                fout.open("bloodBankDonar.txt");
                fout<<name<<bloodType<<endl;
                fout.close();
                cout << "Donor added successfully." << endl;
                break;
            }
            case 2: {
                string bloodType;
                cout << "Enter blood type to search: ";
                cin >> bloodType;
                bloodBank.searchDonors(bloodType);
                break;
            }
            case 3:
                bloodBank.displayNotification();
                break;
            case 4: {
                string requestMessage;
                cout << "Enter blood request message: ";
                cin.ignore();
                getline(cin, requestMessage);
                bloodBank.createRequest(requestMessage);
                cout << "Blood request created successfully." << endl;
                break;
            }
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

