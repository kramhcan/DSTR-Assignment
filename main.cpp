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

Node* head = NULL;
Station station;
PaymentNode* pHead = NULL;
PaymentList pList;
Queue q(255);

void SelectPaymentOrStation(string role);
void DisplaySelectSearchBy();
string EST(int hour, int minute, int duration);

#pragma region StationList
void Station::DisplayAdminMenu(Node* hd)
{
    string selection;
    cout<<"\nWelcome back, Admin. What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. View all stations\n2. View Station Details\n3. Add a new station\n4. Show Payment Menu\n5. Exit system\n";
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
        return DisplayAdminMenu(hd);
    }
    //If selection is outside the range of optioons
    if (selectionInt <= 0 || selectionInt > 5) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayAdminMenu(hd);
    }
    if (selectionInt == 1) { return ViewAllStations(hd, "admin");}
    if (selectionInt == 2) { return ViewStationDetails(hd, "admin");}
    if (selectionInt == 3) {
        // int stationCount = 0;
        // stationCount = DisplaySelectionOfPositionsReturnCount(hd);
        string addSelection;
        cout<<"*========PLEASE SELECT========*\n";
        cout<<"1. Front\n2. End\n";
        cout<<"*=============================*\n";
        cout<<"Selection >> "; 
        cin>>addSelection;
        int addSelectionInt = 0;
        try
        {
            addSelectionInt = stoi(addSelection);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return DisplayAdminMenu(hd);
        }
        if (addSelectionInt <= 0 || addSelectionInt > 2) {
            cout<<"\nInvalid option, please select again.\n"<<endl;
            return DisplayAdminMenu(hd);
        }
        if (addSelectionInt == 1){ DisplayInsertFrontForm(hd, "", "", 0); }
        if (addSelectionInt == 2){ DisplayInsertBackForm(hd, "", "", 0); }
    } 
    if (selectionInt == 4) { return pList.DisplayAdminMenu(pHead); }
    if (selectionInt == 5) { 
        cout<< "Thank you, have a good day.";
        EXIT_SUCCESS;
    }
    return;
}
#pragma endregion

#pragma region Queue
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
#pragma endregion

#pragma region PaymentList
void PaymentList::DisplayAdminMenu(PaymentNode* pHead)
{
    string selection;
    cout<<"\nWelcome back, Admin. What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. View All Payments\n2. Search Payments List\n3. Show Station Menu\n4. Exit system\n";
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
        return DisplayAdminMenu(pHead);
    }
    //If selection is outside the range of optioons
    if (selectionInt <= 0 || selectionInt > 4) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayAdminMenu(pHead);
    }
    if (selectionInt == 1) { return ViewAllPayments(pHead, "admin");}
    if (selectionInt == 2) { 
        string searchSel, searchVal;
        DisplaySelectSearchBy();
        cin >> searchSel;
        if (searchSel == "6")
            return DisplayAdminMenu(pHead);
        cout << "Enter search value (Enter station names for option 4 and 5) : ";
        cin >> searchVal;
        if (searchSel == "1") { ViewPayments(pHead, "admin", "username", searchVal);}
        if (searchSel == "2") { ViewPayments(pHead, "admin", "firstName", searchVal);}
        if (searchSel == "3") { ViewPayments(pHead, "admin", "lastName", searchVal);}
        if (searchSel == "4") { ViewPayments(pHead, "admin", "startStation", searchVal);}
        if (searchSel == "5") { ViewPayments(pHead, "admin", "endStation", searchVal);}
    }
    if (selectionInt == 3) { station.DisplayAdminMenu(head); }
    if (selectionInt == 4) { 
        cout<< "Thank you, have a good day.";
        EXIT_SUCCESS;
    }
    return;
}

void PaymentList::StartPurchaseMenu(PaymentNode* hd, string usr)
{
    string selection;
    string direction, startStID, endStID;
    bool valid;
    cout<<"\nWhich direction are you headed?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Titiwangsa -> Chan Sow Lin\n2. Chan Sow Lin -> Titiwangsa\n3. Cancel\n";
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
        return StartPurchaseMenu(hd, usr);
    }
    if (selectionInt == 1){ direction = "Forward"; }
    if (selectionInt == 2){ direction = "Backward"; }
    if (selectionInt == 3){ return DisplayMemberMenu(hd, usr);}
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

void PaymentList::DisplayNewTicketDetails(PaymentNode* pHead, string usr, string startStID, string endStID, string direction)
{
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
    
    try
    {
        tId = stoi(curr->PaymentID);
    }
    catch(const std::exception& e)
    {
        // std::cerr << e.what() << '\n';
        cout << "Error converting string to int, please enter whole numbers\n";
        return DisplayNewTicketDetails(pHead, usr, startStID, endStID, direction);
    }
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

void PaymentList::EditPaymentAdmin(PaymentNode * hd, PaymentNode * curr)
{
    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);
    
    string newStartID, newEndID, direction, newDeparture;
    int newDuration = 0;
    string selection;
    double newCost = 0, prevCost = 0;

    Node * currNew = head;

    //Select new line direction
    cout<<"\nSelect the new direction for the ticket" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Titiwangsa -> Chan Sow Lin\n2. Chan Sow Lin -> Titiwangsa\n3. Cancel\n";
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
        return EditPaymentAdmin(hd, curr);
    }
    if (selectionInt == 1){ direction = "Forward"; }
    if (selectionInt == 2){ direction = "Backward"; }

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

    if(selectionInt == 1){
        EditPaymentDetails(&pHead, curr->PaymentID, newStartID, newStartName, newEndID, newEndName, newDuration, newDeparture, newCost, dt);
        return DisplayAdminMenu(pHead);
    }
    return DisplayAdminMenu(pHead);
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
    string selection;
    cout<<"\n*****KUALA LUMPUR LIGHT RAIL TRANSIT (LRT) TICKET PURCHASE SYSTEM*****" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Payments\n2. Stations\n";
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
        return SelectPaymentOrStation(role);
    }
    if(selectionInt == 1) { return pList.DisplayAdminMenu(pHead); }
    if(selectionInt == 2) { return station.DisplayAdminMenu(head); } 
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
    q.Enqueue("mbr0", "1234", "Ben", "Dover", "member");
    q.Enqueue("mbr1", "1234", "Pill", "Cosby", "member");
    q.Enqueue("mbr2", "1234", "Mike", "Hawk", "member");
    q.Enqueue("mbr3", "1234", "Chris", "Peacock", "member");

    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);

    //header pointer, username, first name, last name, ic, first station id
    //,first station name, last station id, last station name, cost
    //, distance, current date time, departure time
    pList.AddPayment(&pHead, "mbr0", "Ben", "Dover", "012345678901", "SS02" , "PWTC", "SS07", "Pudu", 3.7, 37, dt, "4:20 PM");
    pList.AddPayment(&pHead, "mbr0", "Ben", "Dover", "012345678901", "SS04" , "Majlis Jamek", "SS08", "Chan Sow Lin", 2.6, 26, dt, "3:30 PM");
    pList.AddPayment(&pHead, "mbr1", "Pill", "Cosby", "011214111234", "SS05" , "Plaza Rakyat", "SS02", "PWTC", 2.2, 22, dt, "8:10 AM");
    pList.AddPayment(&pHead, "mbr1", "Pill", "Cosby", "011214111234", "SS04" , "Majlis Jamek", "SS06", "Hang Tuah", 1.6, 16, dt, "10:30 PM");
    pList.AddPayment(&pHead, "mbr2", "Mike", "Hawk", "010211011360", "SS05" , "Plaza Rakyat", "SS04", "Majlis Jamek", 0.6, 6, dt, "5:20 PM");
    pList.AddPayment(&pHead, "mbr2", "Mike", "Hawk", "010211011360", "SS03" , "Sultan Ismail", "SS05", "Plaza Rakyat", 1.4, 14, dt, "9:20 AM");
    pList.AddPayment(&pHead, "mbr3", "Chris", "Peacock", "012345678901", "SS01" , "Titiwangsa", "SS08", "Chan Sow Lin", 4.6, 46, dt, "5:50 PM");
    pList.AddPayment(&pHead, "mbr3", "Chris", "Peacock", "012345678901", "SS01" , "Titiwangsa", "SS02", "PWTC", 0.4, 4, dt, "6:00 PM");

    DisplayStartOptions(q, head, station);
    return 0;
}