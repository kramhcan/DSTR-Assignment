#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include "station.h"
#include "queue.h"
#include "payment.h"

using namespace std;

void SelectPaymentOrStation(string role);
void DisplaySelectSearchBy();
string EST(int hour, int minute, int duration);

Node* head = NULL;
Station station;
PaymentNode* pHead = NULL;
PaymentList pList;
Queue q(255);

PaymentNode* sortedHead = NULL;

#pragma region StationList
void Station::DisplayAdminMenu(Node* hd)
{
    int selection;
    cout<<"\nWelcome back, Admin. What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. View all stations\n2. View Station Details\n3. Add a new station\n4. Show Payment Menu\n5. Exit system\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    //If selection is outside the range of optioons
    if (selection <= 0 || selection > 4) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayAdminMenu(hd);
    }
    if (selection == 1) { return ViewAllStations(hd, "admin");}
    if (selection == 2) { return ViewStationDetails(hd, "admin");}
    if (selection == 3) {
        // int stationCount = 0;
        // stationCount = DisplaySelectionOfPositionsReturnCount(hd);
        int addSelection;
        cout<<"*========PLEASE SELECT========*\n";
        cout<<"1. Front\n2. End\n";
        cout<<"*=============================*\n";
        cout<<"Selection >> "; 
        cin>>addSelection;
        if (addSelection <= 0 || addSelection > 2) {
            cout<<"\nInvalid option, please select again.\n"<<endl;
            return DisplayAdminMenu(hd);
        }
        if (addSelection == 1){ DisplayInsertFrontForm(hd, "", "", 0); }
        if (addSelection == 2){ DisplayInsertBackForm(hd, "", "", 0); }
    } 
    if (selection == 4) { return pList.DisplayAdminMenu(pHead); }
    return;
}
#pragma endregion

#pragma region Queue
    void Queue::Enqueue(string usr, string pwd, string fstName, string lstName, string rl)
    {
        if(capacity == rear) 
        {
            printf("\nQueue is full\n");
            return;
        }
        else
        {
            username[rear] = usr;
            password[rear] = pwd;
            role[rear] = rl;
            rear++;
        }
        return;
    }

    void Queue::LoginUser(Node* hd, Station st)
    {
        string usr, pwd;
        cout<<"\nPlease enter your Username : ";
        cin >> usr ;
        cout<<"Please enter your Password : ";
        cin >> pwd ;

        int res = ValidateLogin(usr, pwd);
        if (res == 1 ) {
            return SelectPaymentOrStation("admin");
        } else if (res == 2) {
            return SelectPaymentOrStation(usr);
        }
        cout<<"Username or Password is incorrect!\n";
        return LoginUser(hd, st);
    }

    int Queue::ValidateLogin(string usr, string pwd)
    {
        for (int i = front; i <= rear; i++)
        {
            if (usr == username[i] && pwd == password[i]) {
                if (role[i] == "admin"){ return 1; }
                if (role[i] == "member"){ return 2; }
            }
        }
        return 0;
    }

    void Queue::RegisterUser(Node* hd, Station st)
    {
        string usr, pwd, fstName, lstName;
        cout<<"\nWelcome!\nPlease enter your desired Username : ";
        cin >> usr ;
        if(CheckExistingUsername(usr) == true){
            cout << "\n****Username already taken!****\n";
            return RegisterUser(hd, st);
        }
        cout<<"Please enter your desired Password : ";
        cin >> pwd ;

        cout<<"Please enter your first name : ";
        cin >> fstName ;

        cout<<"Please enter your last name : ";
        cin >> lstName ;

        Enqueue(usr, pwd, fstName, lstName, "member");
        cout<<"New member created!\n";
        return;
    }

    bool Queue::CheckExistingUsername(string usr)
    {
        for (int i = front; i <= rear; i++)
        {
            if(usr == username[i])
            { return false; }
        }
        return true;
    }

#pragma endregion

#pragma region PaymentList

// void PaymentList::ViewPaymentDetails(PaymentNode * pHead, string role, string id, string usr)
// {
//     //admin view
//     PaymentNode *curr = pHead;
//     int size = GetListSize(pHead);
//     int page = 1, input = 0, tId = 0;

//     while(curr->PaymentID != id)
//         curr = curr->next;
    
//     while(page)
//     {
//         cout << "\n========================Ticket["<<id<<"]========================\n";
//         cout << "Ticket ID : " << curr->PaymentID <<endl;
//         cout << "Username : " << curr->Username <<endl;
//         cout << "First : " << curr->FirstName <<endl;
//         cout << "Last Name : " << curr->LastName <<endl;
//         cout << "Start Station ID : " << curr->StartID <<endl;
//         cout << "Start Station Name : " << curr->StartName <<endl;
//         cout << "End Station ID : " << curr->EndID <<endl;
//         cout << "End Station Name : " << curr->EndName <<endl;
//         cout << "Travel Duration : " << curr->Duration <<" minutes" <<endl;
//         cout << "Ticket Cost : RM " << curr->Amount <<endl;
//         cout << "Time created : " << curr->Date;
//         cout << "============================================================\n" << endl;
//         cout << "Return To List [1]\n";
//         cout << "Selection >> ";
//         cin >> input;
//         if(input == 3){
//             break;
//         }
//     }  
// }

#pragma endregion

#pragma region non-member methods

void DisplayStartOptions(Queue q, Node* hd, Station st)
{
    string selection;
    cout<<"\n*****KUALA LUMPUR LIGHT RAIL TRANSIT (LRT) TICKET PURCHASE SYSTEM*****" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Login Member\n2. Register Member\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    int selectionInt = 0;
    try
    {
        selectionInt = stoi(selection);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return DisplayStartOptions(q, hd, st);
    }
    
    if(selectionInt == 1) { return q.LoginUser(hd, st); }
    if(selectionInt == 2) { 
        q.RegisterUser(hd, st);
    } else {
        cout<<"\nInvalid option, please select again.\n";
        return DisplayStartOptions(q, hd, st);
    }
}

void SelectPaymentOrStation(string role)
{
    if (role == "admin")
    {
    int selection;
    cout<<"\n*****KUALA LUMPUR LIGHT RAIL TRANSIT (LRT) TICKET PURCHASE SYSTEM*****" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Payments\n2. Stations\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    if(selection == 1) { return pList.DisplayAdminMenu(pHead); }
    if(selection == 2) { return station.DisplayAdminMenu(head); } 
    }
    
    return pList.DisplayMemberMenu(pHead, role);
    
    cout<<"\nInvalid option, please select again.\n";
    return SelectPaymentOrStation(role);
}

void DisplaySelectSearchBy()
{
    cout<<"================= Search Payments By ==================" << endl;
    cout<<"1. Username\n2. First Name\n3. Last Name\n4. Start Station\n5. End Station\n6. Back" << endl;
    cout<<"=======================================================" <<endl;
    cout<<"Selection >> ";
}
#pragma endregion


int main()
{
    //Add default stations
    station.AddStationBack(&head, "SS01", "Titiwangsa", "N/A", "N/A", 0);
    station.AddStationBack(&head, "SS02", "PTWC", "SS01", "Titiwangsa", 4);
    station.AddStationBack(&head, "SS03", "Sultan Ismail", "SS02", "PTWC", 8);
    station.AddStationBack(&head, "SS04", "Majlis Jamek", "SS03", "Sultan Ismail", 8);
    station.AddStationBack(&head, "SS05", "Plaza Rakyat", "SS04", "Majlis Jamek", 6);
    station.AddStationBack(&head, "SS06", "Hang Tuah", "SS05", "Plaza Rakyat", 10);
    station.AddStationBack(&head, "SS07", "Pudu", "SS06", "Hang Tuah", 5);
    station.AddStationBack(&head, "SS08", "Chan Sow Lin", "SS07", "Pudu", 5);

    //Add default users
    q.Enqueue("usr0", "1234", "Mark", "Chan", "admin");
    q.Enqueue("usr1", "1234", "Chong", "Kyle","admin");
    q.Enqueue("usr2", "1234", "Pek", "Yen", "admin");
    q.Enqueue("usr3", "1234", "Joo", "Ee", "admin");
    q.Enqueue("mbr1", "1234", "Generic", "User", "member");

    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);

    //header pointer, username, first name, last name, ic, first station id
    //,first station name, last station id, last station name, cost
    //, distance, current date time, departure time
    pList.AddPayment(&pHead, "member1", "Member", "Dummy", "012345678901", "SS01" , "Titiwangsa", "SS03", "Sultan Ismail", 1.2, 12, dt, "4:20PM");
    pList.AddPayment(&pHead, "member2", "Member", "Two", "012345678901", "SS01" , "Titiwangsa", "SS03", "Sultan Ismail", 1.2, 12, dt, "4:20PM");

    DisplayStartOptions(q, head, station);
    return 0;
}