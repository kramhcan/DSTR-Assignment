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
void PaymentList::AddPayment(PaymentNode** pHead, string usr, string fst, string lst, string ic, string startID, string startName,string endID, string endName, double amount, int duration, string date, string dpt)
{
    PaymentNode* newNode = new PaymentNode;
    PaymentNode* last = *pHead;
    PaymentNode* last1 = last;
    int id = 0;

    if (last1 != NULL)
    {
        while (last1->next != NULL)
            last1 = last1->next;
        id = stoi(last1->PaymentID);
    }    
    
    id++;
    stringstream ss;
    string idString;
    ss << id;
    ss >> idString;

    newNode->PaymentID = idString;
    newNode->Username = usr;
    newNode->FirstName = fst;
    newNode->LastName = lst;
    newNode->UserIC = ic;
    newNode->StartID = startID;
    newNode->StartName = startName;
    newNode->EndID = endID;
    newNode->EndName = endName;
    newNode->Duration = duration;
    newNode->Amount = amount;
    newNode->TransactionDate = date;
    newNode->DepartureTime = dpt;
    newNode->next = nullptr;

    if(*pHead == NULL)
    {
        *pHead = newNode;
        return;
    }
    
    while (last->next != NULL)
        last = last->next;

    last->next = newNode;
    newNode->prev = last;
    return; 
}

void PaymentList::ViewPaymentDetails(PaymentNode * pHead, string role, string id)
{
    //admin view
    PaymentNode *curr = pHead;
    int size = GetListSize(pHead);
    int page = 1, tId = 0;
    string input;

    while(curr->PaymentID != id)
        curr = curr->next;
    

    while(page)
    {
        cout << "\n========================Ticket["<<id<<"]========================\n";
        cout << left << setw(30)<< "Ticket ID : " << curr->PaymentID <<endl;
        cout << left << setw(30)<< "Username : " << curr->Username <<endl;
        cout << left << setw(30)<< "First Name : " << curr->FirstName <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Identification Number : " << curr->UserIC <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Start Station ID : " << curr->StartID <<endl;
        cout << left << setw(30)<< "Start Station Name : " << curr->StartName <<endl;
        cout << left << setw(30)<< "End Station ID : " << curr->EndID <<endl;
        cout << left << setw(30)<< "End Station Name : " << curr->EndName <<endl;
        cout << left << setw(30)<< "Estimated Travel Duration : " << curr->Duration <<" minutes" <<endl;
        cout << left << setw(30)<< "Departure Time: " << curr->DepartureTime <<endl;
        cout << left << setw(30)<< "Ticket Cost : " << "RM " << curr->Amount <<endl;
        cout << left << setw(30)<< "Time created : " << curr->TransactionDate << endl;
        cout << "============================================================\n" << endl;
        cout << "[1] Return To List\nEnter 'EDIT' to edit this purchase entry\nEnter 'DELETE' to delete this purchase history.\n";
        cout << "Selection >> ";
        cin >> input;
        if(input == "1"){
            break;
        }
        if(input == "DELETE"){
            cout<<"Are you sure? This action cannot be undone [Y/n]\nInput >> ";
            cin >> input;
            if (input =="Y" || input == "y")
                DeletePayment(&pHead, curr->PaymentID);
            break;
        }
        if(input == "EDIT"){
            return EditPaymentAdmin(pHead, curr);
        }
    }

    if (role == "admin"){ return ViewAllPayments(pHead, role);}
    
    //'role' here is username
    return ViewPaymentsMember(pHead, role);
    
    
}

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

//admin view all
void PaymentList::ViewAllPayments(PaymentNode*pHead, string role)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;

        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details. Enter 'BACK' to return to menu.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayAdminMenu(pHead); }
    int id = stoi(selection);
    if (id >= 1 && id <= count){
        return ViewPaymentDetails(pHead, role, selection);
    }
    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return ViewAllPayments(pHead, role);
}

void PaymentList::ViewPayments(PaymentNode*pHead, string role, string searchBy, string searchValue)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets ["<< searchBy << " : " << searchValue <<"]========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        if(searchBy == "username" && curr->Username == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "firstName" && curr->FirstName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "lastName" && curr->LastName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "startStation" && curr->StartName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        if(searchBy == "endStation" && curr->EndName == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        
        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details.\nEnter 'BACK' to return to menu.\nEnter 'SORT' to sort list by first name.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayAdminMenu(pHead); }
    if (selection == "SORT"){}
    int id = stoi(selection);
    if (id >= 1 && id <= count){
        return ViewPaymentDetails(pHead, role, selection);
    }
    cout << "***ID Out of Bounds or invalid input!***" << endl;
    return ViewAllPayments(pHead, role);
}

void PaymentList::ViewPaymentsMember(PaymentNode*pHead, string searchValue)
{
    PaymentNode* curr = pHead;
    int count = 0, page = 1;
    int size = GetListSize(pHead);
    string selection;

    cout << "\n*========================================Tickets [User : " << searchValue <<"]========================================*\n\n";
    cout    << left << setw(5) << "ID" << left << setw(10) << "User" << left << setw(15) << "Start Station" << left
            << setw(15) << "End Station" << endl;
    while (curr != NULL){
        if(curr->Username == searchValue){
            cout << left << setw(5) << curr->PaymentID << left << setw(10) << curr-> Username << left << setw(15) << curr->StartName << left
            << setw(15) << curr-> EndName << endl;
        }
        
        count++;
        curr = curr->next;
    }
    cout << "\n*=======================================================================================*\n\n";
    cout << "Enter the Payment ID of the ticket to view the details.\nEnter 'BACK' to return to menu.\n";
    cout << "Selection >> ";
    cin >> selection;
    if (selection == "BACK"){ return DisplayMemberMenu(pHead, searchValue); }
    int id = stoi(selection);
    if (id >= 1 && id <= count){
        return ViewPaymentDetails(pHead, searchValue, selection);
    }
    cout << "***Out of Bounds or invalid input!***" << endl;
    return ViewPaymentsMember(pHead, searchValue);
}

void PaymentList::DisplayAdminMenu(PaymentNode* pHead)
{
    int selection;
    cout<<"\nWelcome back, Admin. What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. View All Payments\n2. Search Payments List\n3. Show Station Menu\n4. Exit system\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    //If selection is outside the range of optioons
    if (selection <= 0 || selection > 4) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayAdminMenu(pHead);
    }
    if (selection == 1) { return ViewAllPayments(pHead, "admin");}
    if (selection == 2) { 
        string searchSel, searchVal;
        DisplaySelectSearchBy();
        cin >> searchSel;
        cout << "Enter search value (Enter station names for option 4 and 5) : ";
        cin >> searchVal;
        if (searchSel == "1") { ViewPayments(pHead, "admin", "username", searchVal);}
        if (searchSel == "2") { ViewPayments(pHead, "admin", "firstName", searchVal);}
        if (searchSel == "3") { ViewPayments(pHead, "admin", "lastName", searchVal);}
        if (searchSel == "4") { ViewPayments(pHead, "admin", "startStation", searchVal);}
        if (searchSel == "5") { ViewPayments(pHead, "admin", "endStation", searchVal);}
    }
    if (selection == 3) { station.DisplayAdminMenu(head); }
    cout << "Thank you, have a good day.";
    return;
}

void PaymentList::DisplayMemberMenu(PaymentNode* pHead, string usr)
{
    int selection;
    cout<<"\nWelcome back, "<< usr <<". What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Start New Purchase\n2. View Transaction History\n3. Exit system\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    //If selection is outside the range of optioons
    if (selection <= 0 || selection > 4) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayMemberMenu(pHead, usr);
    }
    if (selection == 1) { return StartPurchaseMenu(pHead, usr);}
    if (selection == 2) { 
        ViewPaymentsMember(pHead, usr);
    }
    if (selection == 3){    
        cout << "Thank you, have a good day.";
        return;
    }
}

int PaymentList::GetListSize(PaymentNode* pHead)
{
    int count=0;
    PaymentNode* curr = pHead;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

void PaymentList::StartPurchaseMenu(PaymentNode* hd, string usr)
{
    int selection;
    string direction, startStID, endStID;
    bool valid;
    cout<<"\nWhich direction are you headed?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Titiwangsa -> Chan Sow Lin\n2. Chan Sow Lin -> Titiwangsa\n3. Cancel\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    if (selection == 1){ direction = "Forward"; }
    if (selection == 2){ direction = "Backward"; }
    station.ViewAllStationsDirectional(head, direction); 
    //enter start station ID
    cout<<"Enter the starting Station ID >> ";
    cin >> startStID;
    valid = station.ValidateStationID(head, startStID);
    if(!valid) {
        cout << "Invalid Station ID!";
        return StartPurchaseMenu(hd, usr);
    }
    //enter end station ID
    cout<<"Enter the ending Station ID >> ";
    cin >> endStID;
    valid = station.ValidateStationID(head, endStID);
    if(!valid) {
        cout << "Invalid Station ID!";
        return StartPurchaseMenu(hd, usr);
    }
    DisplayNewTicketDetails(hd, usr, startStID, endStID, direction);
    return DisplayMemberMenu(hd, usr);
}

void PaymentList::DisplayNewTicketDetails(PaymentNode* pHead, string usr, string startStID, string endStID, string direction){

    PaymentNode *curr = pHead;
    Node* sCurr = head;
    string startName, endName;
    int dur = station.CalculateDurationBetweenStations(head, startStID, endStID, direction);
    double cost = station.CalculateCostBetweenStations(head, startStID, endStID, direction);

    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);

    //traverse to end of 
    while (curr->next != NULL)
        curr = curr->next;

    while (true)
    {   
        if(sCurr == NULL)
            break;
        if (startStID == sCurr->StationID) { startName = sCurr->StationName; }
        if (endStID == sCurr->StationID) { endName = sCurr->StationName; }

        sCurr = sCurr->next;
    }

    int size = GetListSize(pHead);
    int page = 1, input = 0, tId = 0;
    tId = stoi(curr->PaymentID);
    cout << "\nReview Station Selection and Details Below";
    cout << "\n========================Purchase Details========================\n";
    cout << left << setw(30)<< "Start Station ID : " << startStID <<endl;
    cout << left << setw(30)<< "Start Station Name : " << startName <<endl;
    cout << left << setw(30)<< "End Station ID : " << endStID <<endl;
    cout << left << setw(30)<< "End Station Name : " << endName <<endl;
    cout << left << setw(30)<< "Estimated Travel Duration : " << dur << " minutes" <<endl;
    cout << left << setw(30)<< "Ticket Cost : " << "RM " << cost <<endl;
    cout << "============================================================\n" << endl;
    cout << "[1] to Proceed With Purchase; Enter Anything Else to Return to Menus" << endl;
    cout << "Selection >> ";
    int selection = 0;
    cin >> selection;
    cin.ignore();
    if (selection != 1) { 
        return StartPurchaseMenu(pHead, usr);
    }

    string dept, first, last, id; 

    cout << "\nEnter Your Departure Time (06:00AM to 01:00AM format)\nInput >> ";
    getline(cin, dept);

    cout << "\nEnter your First Name\nInput >> ";
    getline(cin, first);

    cout << "\nEnter your Last Name\nInput >> ";
    getline(cin, last);

    cout << "\nEnter your Identification Number\nInput >> ";
    getline(cin, id);

    cout << "\n========================New Ticket========================\n";
    cout << left << setw(30)<< "Ticket ID : " << tId + 1 <<endl;
    cout << left << setw(30)<< "Username : " << usr <<endl;
    cout << left << setw(30)<< "First Name : " << first <<endl;
    cout << left << setw(30)<< "Last Name : " << last <<endl;
    cout << left << setw(30)<< "Identification Number : " << id <<endl;
    cout << left << setw(30)<< "Start Station ID : " << startStID <<endl;
    cout << left << setw(30)<< "Start Station Name : " << startName <<endl;
    cout << left << setw(30)<< "End Station ID : " << endStID <<endl;
    cout << left << setw(30)<< "End Station Name : " << endName <<endl;
    cout << left << setw(30)<< "Estimated Travel Duration : " << dur << " minutes" <<endl;
    cout << left << setw(30)<< "Departure Time: "  << dept <<endl;
    cout << left << setw(30)<< "Ticket Cost : " << "RM " << cost <<endl;
    cout << left << setw(30)<< "Time created : " << dt <<endl;
    cout << "============================================================\n" << endl;
    cout << "[1] to Confirm; Enter Anything Else to Cancel and Return to Menus\n";
    cout << "Selection >> ";
    cin >> input;

    if(input == 1){
        pList.AddPayment(&pHead, usr, first, last, id, startStID , startName, endStID, endName, cost, dur, dt, dept);
        cout << "\nSuccessfully Purchased A New Ticket!\n";
        return DisplayMemberMenu(pHead, usr);
    }


    return DisplayMemberMenu(pHead, usr);
}

void PaymentList::DeletePayment(PaymentNode** pHead, string id)
{
    // Store head node
    PaymentNode* temp = *pHead;
    PaymentNode* prev = NULL;
     
    // If head node itself holds
    // the id to be deleted
    if (temp != NULL && temp->PaymentID == id)
    {
        *pHead = temp->next; // Changed head
        delete temp;            // free old head
        return;
    }
 
    // Else Search for the id to be deleted,
    // keep track of the previous node as we
    // need to change 'prev->next' */
      else
    {
    while (temp != NULL && temp->PaymentID != id)
    {
        prev = temp;
        temp = temp->next;
    }
 
    // If id was not present in linked list
    if (temp == NULL)
        return;
 
    // Unlink the node from linked list
    prev->next = temp->next;
 
    // Free memory
    delete temp;
    }
}

void PaymentList::EditPaymentAdmin(PaymentNode * hd, PaymentNode * curr)
{
    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);
    
    string newStartID, newEndID, direction, newDeparture;
    int newDuration = 0, selection = 0;
    double newCost = 0, prevCost = 0;

    Node * currNew = head;

    //Select new line direction
    cout<<"\nSelect the new direction for the ticket" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Titiwangsa -> Chan Sow Lin\n2. Chan Sow Lin -> Titiwangsa\n3. Cancel\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    if (selection == 1){ direction = "Forward"; }
    if (selection == 2){ direction = "Backward"; }

    cout<< "Input new starting station ID, replace spaces with '_' (Currently " << curr->StartID << ") : "; 
    cin>>newStartID;
    replace(newStartID.begin(), newStartID.end(), '_', ' ');
    
    //Traverse list to get station Name
    while(currNew != NULL && currNew->StationID != newStartID)
    {
        if(currNew == NULL)
            {
                cout<<"No such station!";
                return EditPaymentAdmin(hd, curr);
            }
        currNew = currNew->next;
    }
    
    //declare new vars for new starting name
    string newStartName = currNew->StationName;
    cout<< "\nNew start station is " << newStartID << ", " << newStartName<< endl; 


    //reset currNew list
    currNew = head;

    cout<< "Input new ending station ID, replace spaces with '_' (Currently " << curr->EndID << ") : "; 
    cin>>newEndID;
    replace(newEndID.begin(), newEndID.end(), '_', ' ');

    //Traverse list to get station name
    while(currNew != NULL && currNew->StationID != newEndID)
    {
        if(currNew == NULL)
            {
                cout<<"No such station!";
                return EditPaymentAdmin(hd, curr);
            }
        currNew = currNew->next;
    }
    
    //declare new vars for new starting name
    string newEndName = currNew->StationName;
    cout<< "\nNew end station is " << newEndID << ", " << newEndName << endl; 

    cout<< "Input new departure time (Currently "<< curr->DepartureTime <<") : ";
    cin >> newDeparture;

    newCost = station.CalculateCostBetweenStations(head,newStartID,newEndID,direction);
    if (newCost == 0){
        cout << "There was an error with the station input! Please re-enter details!";
        return EditPaymentAdmin(hd, curr);
    }

    newDuration = station.CalculateDurationBetweenStations(head,newStartID,newEndID,direction);
    if (newDuration == 0){
        cout << "There was an error with the station input! Please re-enter details!";
        return EditPaymentAdmin(hd, curr);
    }


    cout << "\n========================New Ticket========================\n";
    cout << left << setw(30)<< "Ticket ID : " << curr->PaymentID <<endl;
    cout << left << setw(30)<< "Username : " << curr->Username <<endl;
    cout << left << setw(30)<< "First Name : " << curr->FirstName <<endl;
    cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
    cout << left << setw(30)<< "Identification Number : " << curr->UserIC <<endl;
    cout << left << setw(30)<< "Start Station ID : " << newStartID <<endl;
    cout << left << setw(30)<< "Start Station Name : " << newStartName <<endl;
    cout << left << setw(30)<< "End Station ID : " << newEndID <<endl;
    cout << left << setw(30)<< "End Station Name : " << newEndName <<endl;
    cout << left << setw(30)<< "Estimated Travel Duration : " << newDuration << " minutes" <<endl;
    cout << left << setw(30)<< "Departure Time: "  << newDeparture <<endl;
    cout << left << setw(30)<< "Ticket Cost : " << "RM " << newCost <<endl;
    cout << left << setw(30)<< "Time created : " << dt <<endl;
    cout << "============================================================\n" << endl;
    cout << "[1] to Confirm; Enter Anything Else to Cancel and Return to Menus\n";
    cout << "Selection >> ";
    cin >> selection;

    if(selection == 1){
        EditPaymentDetails(&pHead, curr->PaymentID, newStartID, newStartName, newEndID, newEndName, newDuration, newDeparture, newCost, dt);
        return DisplayAdminMenu(pHead);
    }
    return DisplayAdminMenu(pHead);
}

void PaymentList::EditPaymentDetails(PaymentNode** head, string targetID, string newStartID, string newStartName, string newEndID, string newEndName, int newDuration, string newDeparture, double newCost, string dt)
{
    // Node* curr = new Node;
    PaymentNode* last = *head;

    while (last->PaymentID != targetID)
        last = last->next;

    last->StartID = newStartID;
    last->StartName = newStartName;
    last->EndID = newEndID;
    last->EndName = newEndName;
    last->Duration = newDuration;
    last->DepartureTime = newDeparture;
    last->Amount = newCost;
    last->TransactionDate = dt;
}


PaymentNode* PaymentList::SortList(PaymentNode* pHead, string sortBy){
    PaymentNode *curr = pHead;
    PaymentNode *sorted = new PaymentNode;

    string mini;

    if (sortBy == "username"){
        mini = Minimum(sortBy, curr);
        while(curr->Username != mini)
            curr = curr->next;
        sorted = curr;
        sorted->next = NULL;

    }
        
}

string PaymentList::Minimum(string member, PaymentNode* curr)
{
    PaymentNode *p = curr;
    string minimum;
    if (member == "username")
        {
            minimum = p->Username;

        while (p->next != NULL)
        {
            p = p->next;
            if(minimum > p->Username)
            {
                    minimum = p->Username;
            }
        }
    }
    if (member == "firstName")
        {
            minimum = p->FirstName;

        while (p->next != NULL)
        {
            p = p->next;
            if(minimum > p->FirstName)
            {
                    minimum = p->FirstName;
            }
        }
    }
    if (member == "lastName")
        {
            minimum = p->LastName;

        while (p->next != NULL)
        {
            p = p->next;
            if(minimum > p->LastName)
            {
                    minimum = p->LastName;
            }
        }
    }
    if (member == "startStation")
        {
            minimum = p->StartName;

        while (p->next != NULL)
        {
            p = p->next;
            if(minimum > p->StartName)
            {
                    minimum = p->StartName;
            }
        }
    }
    if (member == "endStation")
        {
            minimum = p->EndName;

        while (p->next != NULL)
        {
            p = p->next;
            if(minimum > p->EndName)
            {
                    minimum = p->EndName;
            }
        }
    }

    return minimum;

}
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