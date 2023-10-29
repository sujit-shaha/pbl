#include <iostream>
#include <vector>
#include <string>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
class Donor {
public:
     Donor(const string &name, const string &bloodGroup, float &quantity, int &age)
        : name(name), bloodGroup(bloodGroup), quantity(quantity), age(age) {}
    virtual void display() const
    {
        cout << "Name: " << name << " | Age: " << age << " | Blood Group: " << bloodGroup << " | Total blood denoted in lifespan: " << quantity << endl;
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
    float quantity;
private:
    int age;
    string name;
    string bloodGroup;
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
        map<string,list<string>> m;
        // cout<<"Total "<<get_count()<<" peoples denoted their blood."<<endl;
        // for (int i = 0; i < donors.size(); i++){
        //     donors[i].display();

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
        float qty;
        int age;
        if (fin >> name >> blood >> qty >> age) {
           m[blood].push_back("name : " + name+" Quantity : "+to_string(qty)+" Age : "+to_string(age));
        }
    }
    map<string,list<string>>::iterator i = m.begin();
    for(i;i!=m.end();i++){
        cout<<endl<<i->first<<" :\n";
        list<string>::iterator j = i->second.begin();
        while(!i->second.empty())
        {
            auto j = i->second;
            cout<<"\t"<<j.front();
            i->second.pop_front();
        }
        
    }
    
    fin.close();
    
    }
    float search(const string name1)
    {
//       cout << "Donors with Blood Type " << bloodType << ":" << endl;
//        for (const Donor& donor : donors) {
//            if (donor.getBloodType() == bloodType) {
//                donor.display();}}
	int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt",ios::app);
    if (!fin.is_open()) {
        cerr << "Error opening file!" <<endl;
        return -1;
    }

    string line;
    fin.seekg(0,fin.beg);
    while (getline(fin, line)) {
        string name, blood;
        float qty;
        if (fin >> name >> blood >> qty) {
            if (name == name1) {
//                cout << "Name: " << name << ", Blood Type: " << blood << " Quantity : "<<qty<<endl;
                fin.close();
                return qty;
                
            }
        }
    }
    
    cout<<"Data not found";
    return 0;
    fin.close();
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
        ofstream fout;
    	
//        donors[index].quantity+=qty;
//        cout<<"Blood quantity updated to : "<<quantity<<endl;
//        donors.pop_back();
		float quantity = search(donor.getName());
		quantity+=qty;
		removeDonor(donor.getName());
		fout.open("bloodBankDonar.txt",ios::app);
                fout<<donor.getName() << " "<<donor.getbloodGroup()<<" "<< quantity <<" "<<donor.getAge()<<" "<<endl;
                fout.close();
        count--;
    }
    int searchDonors(const string& bloodType) {
        cout << "Donors with Blood Group " << bloodType << ":" << endl;
//        for (const Donor& donor : donors) {
//            if (donor.getBloodType() == bloodType) {
//                donor.display();}}
	int found = 0;
        ifstream fin;
        fin.open("bloodBankDonar.txt",ios::app);
    if (!fin.is_open()) {
        cerr << "Error opening file!" <<endl;
        return -1;
    }

    string line;
    fin.seekg(0,fin.beg);
    while (getline(fin, line)) {
        string name, blood;
        float qty;
        int age;
        if (fin >> name >> blood >> qty>> age) {
            if (blood == bloodType) {
                cout << "Name: " << name << ", Blood Group: " << blood << " Quantity : "<<qty<<" Age : "<<age<<endl;
                fin.close();
                return 1;
                
            }
        }
    }
    
    cout<<"Data not found";
    return 0;
    fin.close();
}

void removeDonor(string data){
//	cout<<"Giving blood of donor : "<<data<<" : "<<endl;
//	ifstream infile("bloodBankDonar.txt",ios::app);
//	ofstream outfile("temp.txt");
//	infile.seekg(0,infile.beg);
//	if(!infile){
//		cerr << "Error opening file!" <<endl;
//        return;
//	}
//	
//	string line;
//	while(getline(infile,line)){
//		if(line.find(data)==string::npos){
//			outfile<<line<<endl;
//		}
//	}
//	infile.close();
//	outfile.close();
//	
//	remove("bloodBankDonar.txt");
//	rename("temp.txt","bloodBankDonar.txt");



    ifstream infile("bloodBankDonar.txt");
    ofstream outfile("temp.txt");
    if (!infile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        if (line.find(data) == string::npos) {
            outfile << line << endl;
        }
    }
    infile.close();
    outfile.close();

    remove("bloodBankDonar.txt");
    rename("temp.txt", "bloodBankDonar.txt");


}

void donateBlood(){
	cout<<"Enter which blood group you want : ";
	string bloodGroup;
	cin>>bloodGroup;
	cout<<"Enter the quantity of blood required : ";
	float quant;
	cin>>quant;
	 ifstream fin;
        fin.open("bloodBankDonar.txt",ios::app);
    if (!fin.is_open()) {
        cerr << "Error opening file!" <<endl;
        return ;
    }

    string line;
    fin.seekg(0,fin.beg);
    while (getline(fin, line)) {
        string name, blood;
        float qty;
        int age;
        if (fin >> name >> blood >> qty>> age) {
            if (blood == bloodGroup) {
            	if(qty >= quant){
            	removeDonor(name);
				if((qty-quant)!=0)
                {
                	ofstream fout;
                	fout.open("bloodBankDonar.txt",ios::app);
                fout<<name << " "<<blood<<" "<< qty-quant <<" "<<age<<" "<<endl;
                fout.close();
				}
				cout<<"Donar found"<<endl;
                cout << "Name: " << name << ", Blood Group: " << blood << " Quantity : "<<qty<<" Age : "<<age<<endl;
                fin.close();
                return;
            }
            }
        }
    }
    
    cout<<"Data not found";
    return ;
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
    fout.open("bloodBankDonar.txt",ios::app);
//    fout<<endl;
    fout.close();


    while (true) {
       A: cout<<endl;
        cout<<"***************************************"<<endl;
        cout << "Blood Bank Management System Menu:" << endl;
        cout << "1. Add Donor" << endl;
        cout << "2. Search Donors" << endl;
        cout << "3. Display Notifications" << endl;
        cout << "4. Create Blood Request" << endl;
        cout << "5. Display list of donors"<<endl;
        cout << "6. Give Blood" << endl;
        cout << "7. Exit"<<endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        cout<<endl;
        switch (choice) {
            case 1: {
            string name, bloodGroup;
            float qty;
            int freq, age;
            string greeting;
            cout << "Enter donor's name: ";
            cin >> name;
            cout << "Enter donor's blood group: ";
            cin >> bloodGroup;
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
            B:
            cout << "Enter quantity of blood in litres, donor want to donate: ";
            cin >> qty;
            try
            {
                string s = "Thank you!!! but you can not donate more than 500 ml of blood.";
                if (qty > 0.5)
                    throw s;
            }
            catch (string s)
            {
                cout << s << endl;
                goto B;
            }
            Donor donor(name, bloodGroup, qty, age);
                bloodBank.addDonor(donor);
                if(bloodBank.search(donor.getName())!=0)
                {
                    cout<<"Frequent Donor"<<endl;
                   
                    bloodBank.replace(donor,bloodBank.search(name),qty);
                    break;
                }
                else{
                fout.open("bloodBankDonar.txt",ios::app);
                fout<<name << " "<<bloodGroup<<" "<< qty <<" "<<age<<endl;
                fout.close();
                cout << "Donor added successfully." << endl;
                break;
            }
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
            case 6:{
//            	string bloodType;
//                cout << "Enter blood type to search: ";
//                cin >> bloodType;
//            	bloodBank.removeDonor(bloodType);
				bloodBank.donateBlood();
            	break;
            }
            case 7:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
