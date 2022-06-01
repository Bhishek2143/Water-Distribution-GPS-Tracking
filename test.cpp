#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
using namespace std;
class Connection
{
        int Connectionnumber;
        char name[50];
        char addr[50];
        float deposit;

public:
        void create_Connection();
        void show_Connection();
        void modify_Connection();
        void deposit_funds(int);
        void get_report();
        int get_Connectionnumber();
};

void Connection::create_Connection()
{
        Connectionnumber = rand();
        cout << "\nThe Connection Number is : " << Connectionnumber;
        cout << "\nEnter The Name of The Connection Holder : ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\nEnter Your Address : ";
        cin.getline(addr, 50);
        cout << "\nExpenses for one month : Rs1560";
        deposit=1560.0;
        cout << "\n\n\nConnection Created Successfully...";
}

void Connection::show_Connection()
{
        cout << "\nConnection Number: " << Connectionnumber;
        cout << "\nConnection Holder Name: " << name;
        cout << "\nConnection Holder Address: " << addr;
		cout << "\nAmount Due: " << deposit;
}

void Connection::modify_Connection()
{
        cout << "\nConnection Number: " << Connectionnumber;
        cout << "\nModify Connection Holder Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "\nModify Connection Holder Address : ";
        cin.getline(addr, 50);
}

void Connection::deposit_funds(int x)
{
        deposit += x;
}

void Connection::get_report()
{
        cout << Connectionnumber << setw(17) << " " << name << setw(10) << " " << deposit << setw(8) << " " << addr << endl;
}

int Connection::get_Connectionnumber()
{
        return Connectionnumber;
}

void write_Connection();
void modify_Connection(int);
void delete_Connection(int);
void display_all();
void deposit(int, int);

int main()
{
        srand(time(0));
        char opt;
        int num;
		for (;;)
        {
                system("cls");
                cout << "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "\n\t\t.....WELCOME TO WATER SUPPLY BILLING SYSTEM.....\n";
                cout << "\n\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                cout << "\n\t\tPress 1 to Start a New Water Connection";
                cout << "\n\t\tPress 2 to Check for Dues";
                cout << "\n\t\tPress 3 to Close a Water Connection";
                cout << "\n\t\tPress 4 to See all Records";
                cout << "\n\t\tPress 5 to Modify your Details";
                cout << "\n\t\tPress 6 to Exit the Program";
                cout << "\n\n\t\tOption: ";
                cin >> opt;
                system("cls");
                switch (opt)
                {
                case '1':
                        write_Connection();
                        break;
                case '2':
                        cout << "\n\n\tEnter The Connection No. : ";
                        cin >> num;
                        deposit(num, 1);
                        break;
                case '3':
                        cout << "\n\n\tEnter The Connection No. : ";
                        cin >> num;
                        delete_Connection(num);
                        break;
                case '4':
                    {
                   		display_all();
                   		break;
					}
                case '5':
                        cout << "\n\n\tEnter The Connection No. : ";
                        cin >> num;
                        modify_Connection(num);
                        break;
                case '6':
                        cout << "\n\n\tThanks for using Water Supply Management System";
                        break;
                default:
                        cout << "Invalid Option\n";
                }
                cin.ignore();
                cin.get();
                if (opt == '6')
                        break;
        }
        return 0;
}

void write_Connection()
{
        Connection ac;
        ofstream outFile;
        outFile.open("Connection.dat", ios::binary | ios::app);
        ac.create_Connection();
        outFile.write(reinterpret_cast<char *>(&ac), sizeof(Connection));
        outFile.close();
}

void modify_Connection(int n)
{
        bool found = false;
        Connection ac;
        fstream File;
        File.open("Connection.dat", ios::binary | ios::in | ios::out);
        if (!File)
        {
                cout << "File could not be open !! Press any Key...";
                return;
        }
        while (!File.eof() && found == false)
        {
                File.read(reinterpret_cast<char *>(&ac), sizeof(Connection));
                if (ac.get_Connectionnumber() == n)
                {
                        ac.show_Connection();
                        cout << "\n\nEnter The New Details of Connection: " << endl;
                        ac.modify_Connection();
                        int pos = (-1) * static_cast<int>(sizeof(Connection));
                        File.seekp(pos, ios::cur);
                        File.write(reinterpret_cast<char *>(&ac), sizeof(Connection));
                        cout << "\n\n\t Record Updated...";
                        found = true;
                }
        }
        File.close();
        if (found == false)
                cout << "\n\n Record Not Found ";
}

void delete_Connection(int n)
{
        Connection ac;
        ifstream inFile;
        ofstream outFile;
        inFile.open("Connection.dat", ios::binary);
        if (!inFile)
        {
                cout << "File could not be open !! Press any Key...";
                return;
        }
        outFile.open("Temp.dat", ios::binary);
        inFile.seekg(0, ios::beg);
        while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Connection)))
        {
                if (ac.get_Connectionnumber() != n)
                {
                        outFile.write(reinterpret_cast<char *>(&ac), sizeof(Connection));
                }
        }

        inFile.close();
        outFile.close();
        remove("Connection.dat");
        rename("Temp.dat", "Connection.dat");
        cout << "\n\n\tRecord Deleted...";
}

void display_all()
{
        int bankPassword = 203, enteredPassword;
        cout << "Enter the SYSTEM PASSWORD: \n";
        cin >> enteredPassword;
        if (enteredPassword == bankPassword)
        {
                Connection ac;
                ifstream inFile;
                inFile.open("Connection.dat", ios::binary);
                if (!inFile)
                {
                        cout << "File could not be open !! Press any Key...";
                        return;
                }

                cout << "\n\n\t\tConnection Holder List\n\n";
                cout << "===================================================================================\n";
                cout << "Connection No. |           Name           |   Dues   |           Address           \n";
                cout << "===================================================================================\n";
                while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(Connection)))
                {
                        ac.get_report();
                }
                inFile.close();
                
        }
        else {
                cout << "Please enter the correct password.\n";
        }
}

void deposit(int n, int option)
{
        int amt;
        bool found = false;
        Connection ac;
        fstream File;
        File.open("Connection.dat", ios::binary | ios::in | ios::out);
        if (!File)
        {
                cout << "File could not be open !! Press any Key...";
                return;
        }
        while (!File.eof() && found == false)
        {
                File.read(reinterpret_cast<char *>(&ac), sizeof(Connection));
                if (ac.get_Connectionnumber() == n)
                {
                        ac.show_Connection();
                                cout << "\n\n\tAMOUNT TO BE DEPOSITED PER MONTH: Rs 1200 + 30% of the Water Bill (ignore if already paid)";
                                cout << "\n\n\tTOTAL AMOUNT : Rs 1200 + Rs 360 (30%) = Rs 1560";
                                amt=1560;
								ac.deposit_funds(amt);
                        int pos = (-1) * static_cast<int>(sizeof(ac));
                        File.seekp(pos, ios::cur);
                        File.write(reinterpret_cast<char *>(&ac), sizeof(Connection));
                        cout << "\n\n\t Record Updated";
                        found = true;
                }
        }
        File.close();
        if (found == false)
                cout << "\n\n Record Not Found ";
}
