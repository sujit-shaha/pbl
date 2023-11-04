#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Donor
{
public:
    Donor(const string name, const string bloodGroup, float quantity, int age, const string mobile_no, const string city)
        : name(name), bloodGroup(bloodGroup), quantity(quantity), age(age), mobile_no(mobile_no), city(city) {}
    virtual void display() const
    {
        cout << "Name: " << name << " | Age: " << age << " | Blood Group: " << bloodGroup << " | Total blood denoted in lifespan: " << quantity << " | Mobile Number: " << mobile_no << " | City: " << city << endl;
    }
    const string &getbloodGroup() const
    {
        return bloodGroup;
    }
    const string &getName() const
    {
        return name;
    }
    float &getQuantity()
    {
        return quantity;
    }
    int getAge() const
    {
        return age;
    }
    const string &getMobile_no() const
    {
        return mobile_no;
    }
    const string &getCity() const
    {
        return city;
    }
    float quantity;

private:
    int age;
    string name;
    string bloodGroup;
    string city;
    string mobile_no;
};
class BloodBank
{
public:
    map<string, int> blooodGroup;

    inline string greeting()
    {
        string s = "Thank you for visiting ,donating your blood and saving one more life !!!";
        return s;
    }
    static int count;
    void addDonor(const Donor &donor)
    {
        donors.push_back(donor);
        count++;
    }
    static int get_count()
    {
        return count;
    }
    void display()
    {
        map<string, list<string>> m;

        ifstream fin;
        fin.open("bloodBankDonar.txt", ios::app);
        if (!fin.is_open())
        {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        fin.seekg(0, fin.beg);
        while (getline(fin, line))
        {
            string name, blood, city, mobile_no;
            float qty;
            int age;
            if (fin >> name >> blood >> qty >> age >> mobile_no >> city)
            {
                m[blood].push_back("name : " + name + " Quantity : " + to_string(qty) + " Age : " + to_string(age) + " Mobile no.: " + mobile_no + " City : " + city);
            }
        }
        map<string, list<string>>::iterator i = m.begin();
        for (i; i != m.end(); i++)
        {
            cout <<endl
                  <<i->first << " :";
            list<string>::iterator j = i->second.begin();
            while (!i->second.empty())
            {
                auto j = i->second;
                cout << "\n" << j.front();
                i->second.pop_front();
            }
            cout<<endl;
        }

        fin.close();
    }
    float search(const string name1)
    {

        int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt", ios::app);
        if (!fin.is_open())
        {
            cerr << "Error opening file!" << endl;
            return -1;
        }

        string line;
        fin.seekg(0, fin.beg);
        while (getline(fin, line))
        {
            string name, blood, mobile_no, city;
            float qty;
            if (fin >> name >> blood >> qty >> mobile_no >> city)
            {
                if (name == name1)
                {
                    fin.close();
                    return qty;
                }
            }
        }

        cout << "Data not found";
        return 0;
        fin.close();
    }

    int frequency(const string &name)
    {
        int freq = 0;
        for (int i = 0; i < donors.size(); i++)
        {
            if (donors[i].getName() == name)
            {
                freq++;
            }
        }
        return freq;
    }
    void replace(const Donor &donor, int index, float qty)
    {
        ofstream fout;
        float quantity = search(donor.getName());
        quantity += qty;
        removeDonor(donor.getName());
        fout.open("bloodBankDonar.txt", ios::app);
        fout << donor.getName() << " " << donor.getbloodGroup() << " " << quantity << " " << donor.getAge() << " " << donor.getMobile_no() << " " << donor.getCity() << " " << endl;
        fout.close();
        count--;
    }
    int searchDonors(const string &bloodType)
    {

        int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt", ios::app);
        if (!fin.is_open())
        {
            cerr << "Error opening file!" << endl;
            return -1;
        }

        string line;
        fin.seekg(0, fin.beg);
        while (getline(fin, line))
        {
            string name, blood, mobile_no, city;
            float qty;
            int age;
            if (fin >> name >> blood >> qty >> age >> mobile_no >> city)
            {
                if (blood == bloodType)
                {
                    cout << "Name: " << name << " Blood Group: " << blood << " Quantity : " << qty << " Age : " << age << " Mobile no.: " << mobile_no << " City: " << city << endl;
                    found++;
                }
            }
        }
        return found;
        fin.close();
    }
    int donorNum(const string &bloodType)
    {
        int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt", ios::app);
        if (!fin.is_open())
        {
            cerr << "Error opening file!" << endl;
            return -1;
        }

        string line;
        fin.seekg(0, fin.beg);
        while (getline(fin, line))
        {
            string name, blood, mobile_no, city;
            float qty;
            int age;
            if (fin >> name >> blood >> qty >> age >> mobile_no >> city)
            {
                if (blood == bloodType)
                {
                    found++;
                }
            }
        }
        return found;
        fin.close();
    }

    void removeDonor(string data)
    {

        ifstream infile("bloodBankDonar.txt");
        ofstream outfile("temp.txt");
        if (!infile.is_open())
        {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        while (getline(infile, line))
        {
            if (line.find(data) == string::npos)
            {
                outfile << line << endl;
            }
            else
            {
                cout << "Data removed" << endl;
            }
        }
        infile.close();
        outfile.close();

        remove("bloodBankDonar.txt");
        rename("temp.txt", "bloodBankDonar.txt");
    }

    void donateBlood()
    {
        cout << "Enter which blood group you want : ";
        string bloodGroup;
        cin >> bloodGroup;
        cout << "Enter the quantity of blood required : ";
        float quant;
        cin >> quant;
        ifstream fin;
        fin.open("bloodBankDonar.txt", ios::app);
        if (!fin.is_open())
        {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        fin.seekg(0, fin.beg);
        while (getline(fin, line))
        {
            string name, blood, mobile_no, city;
            float qty;
            int age;
            if (fin >> name >> blood >> qty >> age >> mobile_no >> city)
            {
                if (blood == bloodGroup)
                {
                    if (qty >= quant)
                    {
                        if ((qty - quant) != 0)
                        {
                            fin.close();
                            Donor donor(name, blood, (qty - quant), age, mobile_no, city);
                            replace(donor, 0, (-quant));
                            cout << "Donar found" << endl;
                            cout << "Name: " << name << ", Blood Group: " << blood << " Quantity : " << qty << " Age : " << age << " Mobile no.: " << mobile_no << "City: " << city << endl;
                            return;
                        }
                        else
                        {
                            fin.close();
                            removeDonor(name);
                            return;
                        }
                    }
                }
            }
        }
        cout << "Sorry we apologize But requested blood group or blood quantity is not available " << endl;
    }

    void displayNotification()
    {
        cout << "Notifications: ";

        if (notification.empty())
        {
            cout << "No notifications." << endl;
        }
        else
        {
            for (const string &message : notification)
            {
                cout << message << " | ";
            }
            cout << endl;
        }
    }
    void createRequest(const string &requestMessage)
    {
        notification.push_back(requestMessage);
    }

    void displayQuantity()
    {
        blooodGroup.insert(pair<string, int>("O+", donorNum("O+")));
        blooodGroup.insert(pair<string, int>("O-", donorNum("O-")));
        blooodGroup.insert(pair<string, int>("A+", donorNum("A+")));
        blooodGroup.insert(pair<string, int>("A-", donorNum("A-")));
        blooodGroup.insert(pair<string, int>("B+", donorNum("B+")));
        blooodGroup.insert(pair<string, int>("B-", donorNum("B-")));
        blooodGroup.insert(pair<string, int>("AB+", donorNum("AB+")));
        blooodGroup.insert(pair<string, int>("AB-", donorNum("AB-")));

        map<string, int>::iterator i = blooodGroup.begin();
        for (i; i != blooodGroup.end(); i++)
        {
            cout << i->first << " : " << i->second << endl;
        }
    }

private:
    vector<Donor> donors;
    vector<string> notification;
};
int BloodBank::count = 0;

int main()
{
    BloodBank bloodBank;
    ifstream fin;
    ofstream fout;
    array<string, 8> arr;
    arr = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};

    bloodBank.displayQuantity();
    while (true)
    {
    A:

        cout << endl;
        cout << "***************************************" << endl;
        cout << "Blood Bank Management System Menu:" << endl;
        cout << "1. Add Donor" << endl;
        cout << "2. Search Donors" << endl;
        cout << "3. Display Notifications" << endl;
        cout << "4. Create Blood Request" << endl;
        cout << "5. Display list of donors" << endl;
        cout << "6. Give Blood" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            string name, bloodGroup, mobile_no, city;
            float qty;
            int freq = 0, age;
            string greeting;
            cout << "Enter donor's name: ";
            cin >> name;
        B:
            cout << "Enter donor's blood group: ";
            cin >> bloodGroup;
            try
            {
                for (int i = 0; i < arr.size(); ++i)
                {
                    if (bloodGroup == arr[i])
                        freq = 1;
                }
                string s = "Please tell us your correct blood group.";
                if (!freq)
                    throw s;
            }
            catch (string s)
            {
                cout << s << endl;
                goto B;
            }

            cout << "Enter donor's age: ";
            cin >> age;
            try
            {
                string s1 = "We are really appreciate your willingness but you can't donate your blood since your are not 18 yrs yet.";
                string s2 = "We are really appreciate your willingness but you can't donate your blood since your are aged person.";
                if (age < 18)
                    throw s1;
                if (age > 65)
                    throw s2;
            }
            catch (string s)
            {
                cout << s << endl;
                goto A;
            }
        C:
            cout << "Enter quantity of blood in ml, donor want to donate: ";
            cin >> qty;
            try
            {
                string s = "Thank you!!! but you can not donate more than 500 ml of blood.";
                if (qty > 500)
                    throw s;
            }
            catch (string s)
            {
                cout << s << endl;
                goto C;
            }
            D:
            cout << "Enter donor's mobile number for further emergency contacts: ";
            cin >> mobile_no;
            try
            {
                string s=" Please provide us real mobile number.";
                if(mobile_no.length()!=10)
                throw s;
            }
            catch(string s)
            {
                cout<<s<<endl;
                goto D;
            }
            cout << "Enter donor city for further emergency contacts: ";
            cin >> city;
            Donor donor(name, bloodGroup, qty, age, mobile_no, city);
            bloodBank.addDonor(donor);
            if (bloodBank.search(donor.getName()) != 0)
            {
                cout << "Frequent Donor" << endl;
                bloodBank.greeting();
                bloodBank.replace(donor, bloodBank.search(name), qty);
                break;
            }
            else
            {
                fout.open("bloodBankDonar.txt", ios::app);
                fout << name << " " << bloodGroup << " " << qty << " " << age << " "<<mobile_no<<" "<<city<< endl;
                fout.close();
                bloodBank.greeting();
                cout << "Donor added successfully." << endl;
                break;
            }
        }
        case 2:
        {
            string bloodType;
            cout << "Enter blood type to search: ";
            cin >> bloodType;
            cout << "Donors with Blood Group " << bloodType << ":" << endl;
            int n = bloodBank.searchDonors(bloodType);
            if (n == 0)
            {
                cout << "Donor not found " << endl;
            }
            break;
        }
        case 3:
            bloodBank.displayNotification();
            break;
        case 4:
        {
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
        {
            bloodBank.donateBlood();
            break;
        }
        case 7:
            cout << "Working hours of Blood Camp is over !!! Closing the Blood Camp." << endl;
            cout << "See you tomorrow." << endl;
            return 0;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
