#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
using namespace std;

void addNumber();
void displayRecords();
void searchBySrNo();
void deleteRecord();
void modifyRecord();

class CPP_PhonebookSystem
{
        int srno;
        char name[20];
        char mobile[15];
        char email[30];
        char group[20];
    public:
        int getSrNo()
        {
            return srno;
        }
        void storeData()
        {
            cout<<"* * * * * * * * * CREATE NEW PHONE RECORD * * * * * * * * *\n";
            cout<<"Enter Serial Number : ";
            cin>>srno;
            cin.ignore();
            cout<<"Enter Record Name : ";
            cin.getline(name, 25);
            cout<<"Enter Mobile Number : ";
            cin.getline(mobile, 15);
            cout<<"Enter E-mail Id : ";
            cin.getline(email, 30);
            cout<<"Enter Record Group : ";
            cin.getline(group,20);
            cout<<endl;
        }
        void showData()
        {
            cout<<"\n* * * * * * * * * PHONE BOOK RECORD * * * * * * * * *\n";
            cout<<"Sr.No      : "<<srno<<endl;
            cout<<"Name       : "<<name<<endl;
            cout<<"Mobile No. : "<<mobile<<endl;
            cout<<"Email ID   : "<<email<<endl;
            cout<<"Group      : "<<group<<endl;

        }
}pbs;

void addNumber()
{
    ofstream fout;
    fout.open("PhoneBook.dat", ios::out|ios::binary|ios::app);
    pbs.storeData();
    fout.write((char*)&pbs, sizeof(pbs));
    fout.close();
    cout<<"\nRecord Added To File...\n";
}
void displayRecords()
{
    ifstream fin;
    fin.open("PhoneBook.dat", ios::out|ios::binary|ios::app);
    while(fin.read((char*)&pbs, sizeof(pbs)))
    {
        pbs.showData();
    }
    fin.close();
    cout<<"\nReading Of Data File Completed...\n";
}
void searchBySrNo()
{
    ifstream fin;
    int n, flag=0;
    fin.open("PhoneBook.dat", ios::out|ios::binary|ios::app);
    cout<<"Enter Serial Number Of Record To Display : ";
    cin>>n;
    while(fin.read((char*)&pbs, sizeof(pbs)))
    {
        if(n==pbs.getSrNo())
        {
            pbs.showData();
            flag++;
            cout<<"\n\n...Record Found & Displayed...\n";
        }
    }
    fin.close();
    if(flag==0)
        cout<<"The record of serial number "<<n<<" is not in file...!";
    cout<<"\nReading Of Data File Completed...\n";
}
void deleteRecord()
{
    ifstream fin;
    ofstream fout;
    int n, flag=0;
    fin.open("PhoneBook.dat", ios::out|ios::binary|ios::app);
    fout.open("tempPhoneBook.dat", ios::out|ios::binary);
    cout<<"Enter Serial Number Of Record To Delete : ";
    cin>>n;
    while(fin.read((char*)&pbs, sizeof(pbs)))
    {
        if(n==pbs.getSrNo())
        {
            cout<<"\n\n...The Following Record Is Deleted...\n";
            pbs.showData();
            flag++;
        }
        else
            fout.write((char*)&pbs, sizeof(pbs));
    }
    fin.close();
    fout.close();
    if(flag==0)
        cout<<"The record of serial number "<<n<<" is not in file...!";
    cout<<"\nReading Of Data File Completed...\n";
    remove("PhoneBook.dat");
    rename("tempPhoneBook.dat","PhoneBook.dat");
}
void modifyRecord()
{
    fstream fio;
    int n, flag=0,pos;
    fio.open("PhoneBook.dat", ios::out|ios::binary|ios::in);
    cout<<"Enter Serial Number Of Record To Modify : ";
    cin>>n;
    while(fio.read((char*)&pbs, sizeof(pbs)))
    {
        pos = fio.tellg();
        if(n==pbs.getSrNo())
        {
            cout<<"\n\nThe Following Redord Is Modified...\n";
            pbs.showData();
            flag++;
            cout<<"\nRe-Enter New Details...\n";
            pbs.storeData();
            fio.seekg(pos - sizeof(pbs));
            fio.write((char*)&pbs, sizeof(pbs));
            cout<<"\n...Data Modified Successfully...\n";
        }
    }
    fio.close();
    if(flag==0)
        cout<<"The record of serial number "<<n<<" is not in file...!";
    cout<<"\nReading Of Data File Completed...\n";
}

int main()
{
    int choice;
    do{
        cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * *\n";
        cout<<"               PHONE BOOK MANAGEMENT               \n";
        cout<<"* * * * * * * * * * * * * * * * * * * * * * * * * *\n\n";
        cout<<":::::::::::::::::: PROGRAM MENUS ::::::::::::::::::\n";
        cout<<"1. Save New Phone Record\n";
        cout<<"2. Display All Saved Records\n";
        cout<<"3. Search Specific Record\n";
        cout<<"4. Delete Specific Record\n";
        cout<<"5. Modify Existing Record\n";
        cout<<"6. Exit\n";
        cout<<"Enter Your Choice : ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                addNumber();
                break;
            case 2:
                displayRecords();
                break;
            case 3:
                searchBySrNo();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                modifyRecord();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<"\nInvalid Choice...!";
                exit(0);
        }
    }while (choice);
    getch();
    return 0;
}

