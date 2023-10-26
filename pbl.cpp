#include <iostream>
#include <vector>
#include <string>
#include<fstream>
using namespace std;
class Donor {
public:
    Donor(const string& name, const string& bloodType,float &quantity)
        : name(name), bloodType(bloodType), quantity(quantity) {}
    virtual void display() const {
        cout << "Name: " << name << " | Blood Type: " << bloodType << " | Total blood denoted in lifespan: "<<quantity<< endl;
    }
    const string& getBloodType() const {
        return bloodType;
    }
    const string& getName() const {
        return name;
    }
    float& getQuantity()
    {
        return quantity;
    }
    float quantity;
private:
    string name;
    string bloodType;
};
class BloodBank {
public:
    static int count;
    void addDonor(const Donor& donor) {
        donors.push_back(donor);
        count++;
    }
    static int get_count()
    {
        return count;
    }
    void display()
    {
        cout<<"Total "<<get_count()<<" peoples denoted their blood."<<endl;
        for (int i = 0; i < donors.size(); i++){
            donors[i].display();
    }
    }
    int search(const string &name)
    {
        bool found=false;
        for (int i = 0; i < donors.size(); i++){
            if (donors[i].getName() == name)
            {
                found=true;
                return i;
            }
    }
    if(!found)
    {
        cout << "No such person exists in the database!" << endl;
        return -1;
    }
    }
    int frequency(const string &name)
    {
        int freq=0;
        for (int i = 0; i < donors.size(); i++){
            if (donors[i].getName() == name)
            {
                freq++;
            }
    }
    return freq;
    }
    void replace(const Donor& donor,int index,float qty)
    {
        donors[index].quantity+=qty;
        cout<<"Blood quantity updated to : "<<donors[index].quantity<<endl;
        donors.pop_back();
        count--;
    }
    void searchDonors(const string& bloodType) {
        cout << "Donors with Blood Type " << bloodType << ":" << endl;
//        for (const Donor& donor : donors) {
//            if (donor.getBloodType() == bloodType) {
//                donor.display();}}
	int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt",ios::app);
    if (!fin.is_open()) {
        cerr << "Error opening file!" <<endl;
        return;
    }

    string line;
    fin.seekg(0,fin.beg);
    while (getline(fin, line)) {
        string name, blood;
        if (fin >> name >> blood) {
            if (blood == bloodType) {
                cout << "Name: " << name << ", Blood Type: " << blood << endl;
                found =1;
            }
        }
    }
    if(found==0)
    cout<<"Data not found";
    fin.close();
}


    void displayNotification() {
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
int BloodBank::count=0;

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
        cout << "5. Display list of donors"<<endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout<<endl;
        switch (choice) {
            case 1: {
                string name, bloodType;
                float qty;
                int freq;
                cout << "Enter donor's name: ";
                cin >> name;
                cout << "Enter donor's blood type: ";
                cin >> bloodType;
                cout<<"Enter donor's denoted blood quantity: ";
                cin>>qty;
                Donor donor(name, bloodType,qty);
                bloodBank.addDonor(donor);
                if(bloodBank.frequency(name)!=1)
                {
                    cout<<"Frequent Donor"<<endl;
                    if(bloodBank.search(name)!=-1 )
                    {
                        bloodBank.replace(donor,bloodBank.search(name),qty);
                    }
                }
                fout.open("bloodBankDonar.txt",ios::app);
                fout<<name << " "<<bloodType<<" "<< qty <<" "<<endl;
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
                bloodBank.display();
                break;
            case 6:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}