#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;

//Linked List node -- stations
class Node {
    public:
        string StationID;
        string StationName;
        //Previous station
        string PreviousStationID;
        string PreviousStationName;
        int PreviousStationDistance;
        double PreviousStationCost;
        int PreviousStationTime;
        //Next station
        string NextStationID;
        string NextStationName;
        int NextStationDistance;
        double NextStationCost;
        int NextStationTime;

        //Linked list pointer
        Node* next;

        Node* prev;
};

//Linked List
class Station {
    Node* head;
    public:
        // void AddStation(Node** head, string newID, string newName, int previousID, string previousName, 
        //                 double previousDistance, double previousCost, string nextID, 
        //                 string nextName, double nextDistance, double nextCost, string position);
        void AddStationBack(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance); //Append
        void AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int nextDistance); //Insert
        void EditStationDetails(Node** head, string oldID, string editName, double editedPrevPrice, int editedPrevTime, double editedNextPrice, int editedNextTime);
        void ViewAllStations(Node* head, string role);
        void ViewStationDetails(Node*head, string role);
        // void AddStationBetween();
        // void EditStationDetails();
        double CalculatePriceByDistance(Node* head, string direction);
        int CalculateTimeByDistance(Node* head, string direction);
        int GetListSize(Node* head);
        int DisplaySelectionOfPositionsReturnCount(Node* head);
        void DisplayAdminMenu(Node* hd);
        void DisplayInsertBackForm(Node* hd, string stID, string stName, int prevDist);
        void DisplayInsertFrontForm(Node* hd, string stID, string stName, int nextDist);
        void DisplayEditForm(Node * main, Node * curr);
        
};


class Queue {
    public:
        string *username, *password, *firstName, *lastName, *role;
        int capacity, front, rear;

        Queue(int size)
        {
            username = new string[size];
            password = new string[size];
            firstName = new string[size];
            lastName = new string[size];
            role = new string[size];

            front = rear = 0;
            capacity = size;
            // count = new int;
        }
        void Enqueue(string username, string password, string firstName, string lastName, string role);
        void LoginUser(Node* hd, Station st);
        int ValidateLogin(string name, string password);
        void RegisterUser(Node* hd, Station st);
        bool CheckExistingUsername(string usr);
};

class PaymentNode {
    public:
        string PaymentID;
        string Username;
        string FirstName;
        string LastName;
        string UserIC;//*
        string StartID;
        string StartName;
        string EndID;
        string EndName;
        int Duration;
        double Amount;
        string TransactionDate;
        string DepartureTime;//*



        PaymentNode * next;
        PaymentNode * prev;
};

class PaymentList {
    PaymentNode * Head;
    public:
    void AddPayment(PaymentNode** head, string usr, string fst, string lst, string startID, string startName,string endID, string endName, double amount, int duration, string date);
    void ViewPaymentDetails(PaymentNode*head, string role, string id);
    void ViewPaymentDetails(PaymentNode*head, string role, string id, string usr);
    void ViewAllPayments(PaymentNode*head, string role);
    void ViewAllPayments(PaymentNode*head, string role, string id, string usr);
    void ViewPayments(PaymentNode*pHead, string role, string searchBy, string searchValue);
    void DisplayAdminMenu(PaymentNode* hd);

    int GetListSize(PaymentNode* head);
    PaymentNode* SortList(PaymentNode* pHead, string sortBy);
    string Minimum(string Member, PaymentNode* curr);
};

void SelectPaymentOrStation();
void DisplaySelectSearchBy();

Node* head = NULL;
Station station;
PaymentNode* pHead = NULL;
PaymentList pList;
Queue q(255);

PaymentNode* sortedHead = NULL;

#pragma region LinkedList
void Station::AddStationBack(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance)
{
	Node* newNode = new Node;
	Node* last = *head;

	newNode->StationID = newID;
	newNode->StationName = newName;
	newNode->PreviousStationID = previousID;
	newNode->PreviousStationName = previousName;
	newNode->PreviousStationDistance = previousDistance;
    if (previousDistance != 0){
        newNode->PreviousStationCost = previousDistance*0.1;
        newNode->PreviousStationTime = previousDistance-1; 
    } else {
        newNode->PreviousStationCost = 0;
        newNode->PreviousStationTime = 0;
    }
    newNode->NextStationID = "N/A";
	newNode->NextStationName = "N/A";
	newNode->NextStationDistance = 0;
    newNode->NextStationCost = 0;
    newNode->NextStationTime = 0;
	newNode->next = nullptr;

    // If list is empty, make new head
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

    //Traverse to end of list
	while (last->next != NULL)
		last = last->next;

    //change next of last node as well as the next station values
	last->next = newNode;

    last->NextStationID = newID;
    last->NextStationName = newName;
    last->NextStationDistance = previousDistance;
    last->NextStationCost = previousDistance*0.1;
    last->NextStationTime = previousDistance-1;

    //make last node as previous of new node
    newNode->prev = last;

	return;
}

void Station::AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int nextDistance)
{
    Node* newNode = new Node;

    //Set new node data
    newNode->StationID = newID;
	newNode->StationName = newName;
	newNode->NextStationID = (*head)->StationID;
	newNode->NextStationName = (*head)->StationName;
	newNode->NextStationDistance = nextDistance;
    newNode->NextStationCost = nextDistance*0.1;
    newNode->NextStationTime = nextDistance-1;

    //Set previous data of following node
    (*head)->PreviousStationID = newID;
    (*head)->PreviousStationName = newName;
    (*head)->PreviousStationDistance = nextDistance;
    if (nextDistance != 0){
        (*head)->PreviousStationCost = nextDistance*0.1;
        (*head)->PreviousStationTime = nextDistance-1;
    } else {
        (*head)->PreviousStationCost = 0;
        (*head)->PreviousStationTime = 0;
    }
    
    
    //Set next pointer of new node
	newNode->next = (*head);

    //Set head to new node
    (*head) = newNode;
}

double Station::CalculatePriceByDistance(Node* head, string direction)
{
    double price = 0.0;
    if (direction == "Forward") {
        // if (head->NextStationDistance == 0) { return 0; }
        price =  head->NextStationDistance * 0.1;
    } else if (direction == "Backward") {
        // if (head->PreviousStationDistance == 0) { return 0; }
        price =  head->PreviousStationDistance * 0.1;
    }
    return price;
}

int Station::CalculateTimeByDistance(Node* head, string direction)
{
    int time = 0;
    if (direction == "Forward") {
        // if (head->NextStationDistance == 0) { return 0; }
        time =  head->NextStationDistance - 1 ;
    } else if (direction == "Backward") {
        // if (head->PreviousStationDistance == 0) { return 0; }
        time =  head->PreviousStationDistance - 1;
    }
    return time;
}

int Station::GetListSize(Node* head){
    int count=0;
    Node* curr = head;
    while (curr!= NULL){
        count++;
        curr = curr->next;
    }
    return count;
}

//Displays summary of all stations
void Station::ViewAllStations(Node* head, string role)
{
    Node* curr = head;

    cout<<"\nKUALA LUMPUR LIGHT RAIL TRANSIT (LRT) - 'TITIWANGSA -> CHAN SOW LIN' STATION ROUTE \n";

    //Forward linked list traversal
    while(curr!= NULL){
        //Initialize price
        double price = 0.0;
        //Function called to calculate price
        price = CalculatePriceByDistance(curr, "Forward");
        //Print out stationID and stationName
        cout << "\n==============================\n\n";
        cout << "Station ID : " << curr->StationID <<endl;
        cout << "Station Name : " << curr->StationName <<endl;
        cout << "\n==============================" << endl;
        //IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
        if (curr->NextStationDistance != 0) {
            cout << "\t\t|" << endl;
            cout << "\t\t| " << curr->NextStationDistance << " KM" << endl;
            cout << "\t\t|" << " RM " << CalculatePriceByDistance(curr, "Forward") << endl;
            cout << "\t\t| " << CalculateTimeByDistance(curr, "Forward") << " minutes\n\t\t|" << endl;
            cout << "\t\tV";
        }
        //Set current node to next node and repeat loop
        curr = curr->next;
    }
    int inp = 0;
    while (inp != 1)
    {
        cout << "\nInput '1' to return to menu >> ";
        cin >> inp;
    }
    if (role == "admin") { return DisplayAdminMenu(head); }
}

void Station::ViewStationDetails(Node*head, string role)
{
    Node* curr = head;

    //Initialize price
    double price = 0.0;
    int size = GetListSize(head);
    int page = 1;
    int input = 0;
    while(page)
    {
        //Print out stationID and stationName
        cout << "\n========================Station["<<page<<"/"<<size<<"]========================\n";
        cout << "Station ID : " << curr->StationID <<endl;
        cout << "Station Name : " << curr->StationName <<endl;
        cout << "Previous Station ID : " << curr->PreviousStationID <<endl;
        cout << "Previous Station Name : " << curr->PreviousStationName <<endl;
        cout << "Distance between previous station : " << curr->PreviousStationDistance <<endl;
        cout << "Time between previous station : " << curr->PreviousStationTime <<endl;
        cout << "Cost between previous station : RM" << curr->PreviousStationCost <<endl;
        cout << "Next Station ID : " << curr->NextStationID <<endl;
        cout << "Next Station Name : " << curr->NextStationName <<endl;
        cout << "Distance between next station : " << curr->NextStationDistance <<endl;
        cout << "Time between next station : " << curr->NextStationTime <<" minutes" <<endl;
        cout << "Cost between next station : RM" << curr->NextStationCost <<endl;
        cout << "\n============================================================\n" << endl;
        cout << "Next Page [1] || Previous Page [2] || Edit Current Station [3] || Return to menu [4]\n";
        cout << "Selection >> ";
        cin >> input;
        if (input == 1){
            if(page == size) { 
                cout << "\n***********OUT OF PAGE BOUNDS!***********!\n";
                continue;
            } else {
                page++;
                curr = curr->next;
                continue;
            }
        }
        if (input == 2){
            if(page == 1) { 
                cout << "\n***********OUT OF PAGE BOUNDS!***********\n";
                continue;
            } else {
                page--;
                curr = curr->prev;
                continue;
            }
        }
        if(input == 3){
            //Show editable details
            return DisplayEditForm(head, curr);
        }
        //Break if selected return
        if(input ==4){
            break;
        }
    }
    if (role == "admin")
        { return DisplayAdminMenu(head); }
}

int Station::DisplaySelectionOfPositionsReturnCount(Node* head)
{
    Node* curr = head;
    int count = 0;

    cout << "\n*======================Select Position======================*\n\n";
    while (curr != NULL){
        cout << count << "--->> " <<  endl;
        cout << "     Station ID : " << curr->StationID << " || Station Name : " << curr->StationName <<endl;

        count++;

        //stops cout at last station
        if (curr->NextStationDistance == 0){
            cout << count << "--->> " <<  endl;
        }

        curr = curr->next;
    }
    cout << "\n*===========================================================*\n\n";
    cout << "Selection >> ";

    return count;
}

void Station::DisplayInsertBackForm(Node* hd, string stID, string stName, int prevDist)
{
    Node* curr = hd;
    //Traverse to end
    while(curr->next != NULL)
        curr = curr->next;
    
    //Form
    cout<<"\n**==============INSERT AT END==============**\n";
    cout<<"1. Station ID : " << stID <<endl;
    cout<<"2. Station Name : " << stName <<endl;
    cout<<"3. Previous Station ID : "<<curr->StationID<<endl;
    cout<<"4. Previous Station Name : "<<curr->StationName<<endl;
    cout<<"5. Distance between previous station : " << prevDist;
    cout<<"\n**=========================================**\n";
    cout<<"Type in 'CANCEL' to stop operation and return to previous page*\n\n";
    if(stID == "") { 
        cout<<"Enter Station ID : ";
        cin>>stID;
        return DisplayInsertBackForm(hd, stID, stName, prevDist);
    } else if (stID == "CANCEL") { return DisplayAdminMenu(hd); }
    if(stName == "") { 
        cout<<"Enter Station Name : ";
        getline(cin, stName);
        return DisplayInsertBackForm(hd, stID, stName, prevDist);
    } else if (stName == "CANCEL") { return DisplayAdminMenu(hd); }
    if(prevDist == 0) { 
        string dist;
        cout<<"Enter Distance Between Previous Station : ";
        cin>>dist;
        if (dist == "CANCEL") { return DisplayAdminMenu(hd); }
        prevDist = stoi(dist);
        return DisplayInsertBackForm(hd, stID, stName, prevDist);
    }   
    //Confirmation Check
    string res1;
    cout<<"\nAre you sure? [Y/n]\n";
    cin>>res1;
    if (res1 == "Y" || res1 == "y"){
        AddStationBack(&hd, stID, stName, curr->StationID, curr->StationName, prevDist);
        return DisplayAdminMenu(hd);
    } else if (res1 == "N" || res1 == "n") {
        //Cancel operation check
        string res2;
        cout<<"\nCancel Operation? [Y/n]\n";
        cin>>res2;
        if(res2 == "Y" || res2 == "y"){
            return DisplayAdminMenu(hd);
        } else {
            return DisplayInsertBackForm(hd, "", "", 0);
        }
    }
    cout<<"An error has occurred :(";
    return;
}

void Station::DisplayInsertFrontForm(Node* hd, string stID, string stName, int nextDist)
{
    Node* curr = hd;
    
    //Form
    cout<<"\n**=============INSERT AT FRONT=============**\n";
    cout<<"1. Station ID : " << stID <<endl;
    cout<<"2. Station Name : " << stName <<endl;
    cout<<"3. Next Station ID : "<<curr->StationID<<endl;
    cout<<"4. Next Station Name : "<<curr->StationName<<endl;
    cout<<"5. Distance between next station : " << nextDist;
    cout<<"\n**=========================================**\n";
    cout<<"Type in 'CANCEL' to stop operation and return to previous page*\n\n";
    if(stID == "") { 
        cout<<"Enter Station ID : ";
        cin>>stID;
        return DisplayInsertFrontForm(hd, stID, stName, nextDist);
    } else if (stID == "CANCEL") { return DisplayAdminMenu(hd); }
    if(stName == "") { 
        cout<<"Enter Station Name : ";
        getline(cin, stName);
        return DisplayInsertFrontForm(hd, stID, stName, nextDist);
    } else if (stName == "CANCEL") { return DisplayAdminMenu(hd); }
    if(nextDist == 0) { 
        string dist;
        cout<<"Enter Distance Between Next Station : ";
        cin>>dist;
        if (dist == "CANCEL") { return DisplayAdminMenu(hd); }
        nextDist = stoi(dist);
        return DisplayInsertFrontForm(hd, stID, stName, nextDist);
    }   
    //Confirmation Check
    string res1;
    cout<<"\nAre you sure? [Y/n]\n";
    cin>>res1;

    if (res1 == "Y" || res1 == "y"){
        AddStationFront(&hd, stID, stName, curr->StationID, curr->StationName, nextDist);
        return DisplayAdminMenu(hd);
    } else if (res1 == "N" || res1 == "n") {
        //Cancel operation check
        string res2;
        cout<<"\nCancel Operation? [Y/n]\n";
        cin>>res2;
        if(res2 == "Y" || res2 == "y"){
            return DisplayAdminMenu(hd);
        } else {
            return DisplayInsertFrontForm(hd, "", "", 0);
        }
    }
    cout<<"An error has occurred :(";
    return;
}

void Station::DisplayEditForm(Node * main, Node * curr)
{
    string newName;
    int nextTime = 0, prevTime = 0;
    double nextCost = 0, prevCost = 0;

    cout<< "Input new station name, replace spaces with '_' (Currently " << curr->StationName << ") : "; 
    cin>>newName;
    replace(newName.begin(), newName.end(), '_', ' ');
    if(curr->PreviousStationTime != 0)
    {
        cout<< "Input new time between previous station (Currently "<< curr->PreviousStationTime <<" minutes) : ";
        cin >> prevTime;
    }
    if(curr->PreviousStationCost != 0) {
        cout<< "Input new cost between previous station (Currently RM "<< curr->PreviousStationCost <<") : ";
        cin >> prevCost;
    }
    if(curr->NextStationTime != 0) {
        cout<< "Input new time between next station (Currently "<< curr->NextStationTime <<" minutes) : ";
        cin >> nextTime;
    }
    if(curr->NextStationCost != 0) {
        cout<< "Input new cost between next station (Currently RM "<< curr->NextStationCost <<") : ";
        cin >> nextCost;
    }
    
    if (newName == ""){
        cout<<"***Input cannot be empty!***\n";
        return DisplayEditForm(main, curr);
    }
    if (prevTime == 0 || prevCost == 0) {
        cout<<"***Input cannot be empty!***";
        return DisplayEditForm(main, curr);
    }
    if (nextTime == 0 || nextCost == 0){
        cout<<"***Input cannot be empty!***";
        return DisplayEditForm(main, curr);
    }

    string input;
    //Form
    cout<<"\n**=============Edit Output=============**\n";
    cout << "Station ID : " << curr->StationID <<endl;
    cout << "Station Name : " << newName <<endl;
    cout << "Previous Station ID : " << curr->PreviousStationID <<endl;
    cout << "Previous Station Name : " << curr->PreviousStationName <<endl;
    cout << "Distance between previous station : " << curr->PreviousStationDistance <<endl;
    cout << "Time between previous station : " << prevTime << " minutes" <<endl;
    cout << "Cost between previous station : RM" << prevCost <<endl;
    cout << "Next Station ID : " << curr->NextStationID <<endl;
    cout << "Next Station Name : " << curr->NextStationName <<endl;
    cout << "Distance between next station : " << curr->NextStationDistance <<endl;
    cout << "Time between next station : " << nextTime <<" minutes" << endl;
    cout << "Cost between next station : RM" << nextCost <<endl;
    cout<<"\n**=========================================**\n";
    cout<<"Type in 'CANCEL' to stop operation and return to previous page*\n";
    cout<<"Type in 'CONFIRM' to proceed with the edit operation*\n";
    cout<<">>";
    cin>>input;
    
    if (input == "CANCEL"){ return DisplayAdminMenu(main); }
    if (input == "CONFIRM"){
        EditStationDetails(&main, curr->StationID, newName, prevCost, prevTime, nextCost, nextTime);
        return DisplayAdminMenu(main);
    }
}

void Station::EditStationDetails(Node** head, string oldID, string editName, double editedPrevPrice, int editedPrevTime, double editedNextPrice, int editedNextTime)
{
    // Node* curr = new Node;
    Node* last = *head;

    while (last->StationID != oldID)
        last = last->next;

    last->StationName = editName;
    last->PreviousStationCost = editedPrevPrice;
    last->PreviousStationTime = editedPrevTime;
    last->NextStationCost = editedNextPrice;
    last->NextStationCost = editedNextTime;
}

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
            return SelectPaymentOrStation();
        } else if (res == 2) {
            return;
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
void PaymentList::AddPayment(PaymentNode** pHead, string usr, string fst, string lst, string startID, string startName,string endID, string endName, double amount, int duration, string date)
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
    newNode->StartID = startID;
    newNode->StartName = startName;
    newNode->EndID = endID;
    newNode->EndName = endName;
    newNode->Duration = duration;
    newNode->Amount = amount;
    newNode->TransactionDate = date;
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
    int page = 1, input = 0, tId = 0;

    while(curr->PaymentID != id)
        curr = curr->next;
    

    while(page)
    {
        cout << "\n========================Ticket["<<id<<"]========================\n";
        cout << left << setw(30)<< "Ticket ID : " << curr->PaymentID <<endl;
        cout << left << setw(30)<< "Username : " << curr->Username <<endl;
        cout << left << setw(30)<< "First : " << curr->FirstName <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Customer Identity Card : " << curr->UserIC <<endl;
        cout << left << setw(30)<< "Last Name : " << curr->LastName <<endl;
        cout << left << setw(30)<< "Start Station ID : " << curr->StartID <<endl;
        cout << left << setw(30)<< "Start Station Name : " << curr->StartName <<endl;
        cout << left << setw(30)<< "End Station ID : " << curr->EndID <<endl;
        cout << left << setw(30)<< "End Station Name : " << curr->EndName <<endl;
        cout << left << setw(30)<< "Estimated Travel Duration : " << curr->Duration <<" minutes" <<endl;
        cout << left << setw(30)<< "Departure Time: " << curr->EndName <<endl;
        cout << left << setw(30)<< "Ticket Cost : RM " << curr->Amount <<endl;
        cout << left << setw(30)<< "Time created : " << curr->TransactionDate;
        cout << "============================================================\n" << endl;
        cout << "Return To List [1]\n";
        cout << "Selection >> ";
        cin >> input;
        if(input == 1){
            break;
        }
    } 
    return ViewAllPayments(pHead, role);
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
    if (selection <= 0 || selection > 3) { 
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

int PaymentList::GetListSize(PaymentNode* pHead){
    int count=0;
    PaymentNode* curr = pHead;
    while (curr != NULL){
        count++;
        curr = curr->next;
    }
    return count;
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

void SelectPaymentOrStation()
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

    cout<<"\nInvalid option, please select again.\n";
    return SelectPaymentOrStation();
}
#pragma endregion

void DisplaySelectSearchBy()
{
    cout<<"================= Search Payments By ==================" << endl;
    cout<<"1. Username\n2. First Name\n3. Last Name\n4. Start Station\n5. End Station\n6. Back" << endl;
    cout<<"=======================================================" <<endl;
    cout<<"Selection >> ";
}

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

    //Set variable for current date & time
    time_t now = time(0);
    char* dt = ctime(&now);

    pList.AddPayment(&pHead, "member1", "Member", "Dummy", "SS01" , "Titiwangsa", "SS03", "Sultan Ismail", 1.2, 12, dt);
    pList.AddPayment(&pHead, "member2", "Member", "Two", "SS01" , "Titiwangsa", "SS03", "Sultan Ismail", 1.2, 12, dt);

    DisplayStartOptions(q, head, station);
    return 0;
}