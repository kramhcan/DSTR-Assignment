#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>

using namespace std;
// station codes go here
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
        void AddStationBack(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance); //Append
        void AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int nextDistance); //Insert
        void EditStationDetails(Node** head, string oldID, string editName, double editedPrevPrice, int editedPrevTime, double editedNextPrice, int editedNextTime);
        void ViewAllStations(Node* head, string role);
        void ViewAllStationsDirectional(Node* head, string direction);
        void ViewStationDetails(Node*head, string role);
        double CalculatePriceByDistance(Node* head, string direction);
        int CalculateTimeByDistance(Node* head, string direction);
        int GetListSize(Node* head);
        int DisplaySelectionOfPositionsReturnCount(Node* head);
        void DisplayAdminMenu(Node* hd);
        void DisplayInsertBackForm(Node* hd, string stID, string stName, int prevDist);
        void DisplayInsertFrontForm(Node* hd, string stID, string stName, int nextDist);
        void DisplayEditForm(Node * main, Node * curr);
        bool ValidateStationID(Node* main, string stID);
        int CalculateDurationBetweenStations(Node* hd, string station1, string station2, string direction);
        double CalculateCostBetweenStations(Node* hd, string station1, string station2, string direction);
        
};

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
        newNode->prev = NULL;
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

void Station::ViewAllStationsDirectional(Node* head, string direction)
{
    Node* curr = head;

    if (direction == "Backward"){
        cout<<"\nKUALA LUMPUR LIGHT RAIL TRANSIT (LRT) - 'CHAN SOW LIN -> TITIWANGSA' STATION ROUTE \n";
        //if 'direction' is Backwards, traverse to end of list for reverse traversal
        while (curr->next != NULL){
            curr = curr->next;
        }
        while(curr!= NULL){
            //Initialize price
            double price = 0.0;
            //Function called to calculate price
            price = CalculatePriceByDistance(curr, direction);
            //Print out stationID and stationName
            cout << "\n==============================\n";
            cout << "Station ID : " << curr->StationID <<endl;
            cout << "Station Name : " << curr->StationName <<endl;
            cout << "==============================" << endl;
            //IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
            if (curr->PreviousStationDistance != 0) {
                cout << "\t\t| " << curr->PreviousStationDistance << " KM" << endl;
                cout << "\t\t|" << " RM " << CalculatePriceByDistance(curr, direction) << endl;
                cout << "\t\t| " << CalculateTimeByDistance(curr, direction) << " minutes" << endl;
                cout << "\t\tV";
            }
            //Set current node to previous node and repeat loop
            curr = curr->prev;
        }
    }
    
    if(direction == "Forward"){
        cout<<"\nKUALA LUMPUR LIGHT RAIL TRANSIT (LRT) - 'TITIWANGSA -> CHAN SOW LIN' STATION ROUTE \n";
        while(curr!= NULL){
            //Initialize price
            double price = 0.0;
            //Function called to calculate price
            price = CalculatePriceByDistance(curr, "Forward");
            //Print out stationID and stationName
            cout << "\n==============================\n";
            cout << "Station ID : " << curr->StationID <<endl;
            cout << "Station Name : " << curr->StationName <<endl;
            cout << "==============================" << endl;
            //IF statement to check if there is next station; If next distance is 0, there is no next station, therefore will not run the commands below
            if (curr->NextStationDistance != 0) {
                cout << "\t\t| " << curr->NextStationDistance << " KM" << endl;
                cout << "\t\t|" << " RM " << CalculatePriceByDistance(curr, "Forward") << endl;
                cout << "\t\t| " << CalculateTimeByDistance(curr, "Forward") << " minutes" << endl;
                cout << "\t\tV";
            }
            //Set current node to next node and repeat loop
            curr = curr->next;
        }
    }
    return;
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
        try
        {
            prevDist = stoi(dist);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return DisplayInsertBackForm(hd, stID, stName, prevDist);
        }
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
        try
        {
            nextDist = stoi(dist);
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            cout << "Error converting string to int, please enter whole numbers\n";
            return DisplayInsertFrontForm(hd, stID, stName, nextDist);
        }
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
    bool first = false, last = false;

    cout<< "Input new station name, replace spaces with '_' (Currently " << curr->StationName << ") : "; 
    cin>>newName;
    replace(newName.begin(), newName.end(), '_', ' ');
    if(curr->PreviousStationTime != 0)
    {
        cout<< "Input new time between previous station (Currently "<< curr->PreviousStationTime <<" minutes) : ";
        cin >> prevTime;
    } else { 
        first = true; 
    }
    if(curr->PreviousStationCost != 0) {
        cout<< "Input new cost between previous station (Currently RM "<< curr->PreviousStationCost <<") : ";
        cin >> prevCost;
    } else {
        first = true;
    }
    if(curr->NextStationTime != 0) {
        cout<< "Input new time between next station (Currently "<< curr->NextStationTime <<" minutes) : ";
        cin >> nextTime;
    } else {
        last = true;
    }
    if(curr->NextStationCost != 0) {
        cout<< "Input new cost between next station (Currently RM "<< curr->NextStationCost <<") : ";
        cin >> nextCost;
    } else {
        last = true;
    }
    
    if (newName == ""){
        cout<<"***Input cannot be empty!***\n";
        return DisplayEditForm(main, curr);
    }

    if(!first)
    {
        if (prevTime == 0 || prevCost == 0) {
            cout<<"***Input cannot be empty!***";
            return DisplayEditForm(main, curr);
        }
    }

    if(!last)
    {
        if (nextTime == 0 || nextCost == 0) {
            cout<<"***Input cannot be empty!***";
            return DisplayEditForm(main, curr);
        }
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

void Station::EditStationDetails(Node** head, string ID, string editName, double editedPrevPrice, int editedPrevTime, double editedNextPrice, int editedNextTime)
{
    // Node* curr = new Node;
    Node* last = *head;

    while (last->StationID != ID)
        last = last->next;

    last->StationName = editName;
    last->PreviousStationCost = editedPrevPrice;
    last->PreviousStationTime = editedPrevTime;
    last->NextStationCost = editedNextPrice;
    last->NextStationTime = editedNextTime;
}

bool Station::ValidateStationID(Node* main, string stID)
{
    Node* curr = main;
    int loop = 1;

    while(true){
        if(curr->StationID == stID){ return true; }
        if(curr == NULL)
            break;
        curr = curr->next;
    }

    return false;
}

int Station::CalculateDurationBetweenStations(Node* hd, string station1, string station2, string direction)
{
    Node* curr = new Node;
    curr = hd;
    int res = 0;

    if (direction == "Forward"){
        //loop until first station matches
        while(curr->next != NULL && curr->StationID != station1)
            curr = curr->next;
        //from first station add next station time until end station is reached
        while(curr->StationID != station2)
        {
            if (curr == NULL)
                break;
            res += curr->NextStationTime;
            curr = curr->next;
        }
        return res;
    }

    if (direction == "Backward"){
        //loop list until the end first
        while(curr->next != NULL)
            curr = curr->next;

        //traverse backward until first station matches
        while(curr->prev != NULL && curr->StationID != station1)
            curr = curr->prev;
        //from first station add next station time until end station is reached
        while(curr->StationID != station2)
        {
            if (curr == NULL)
                break;
            res += curr->PreviousStationTime;
            curr = curr->prev;
        }
        return res;
    }
    return 0;
}

double Station::CalculateCostBetweenStations(Node* hd, string station1, string station2, string direction)
{
    Node* curr = new Node;
    curr = hd;
    double res = 0;

    if (direction == "Forward"){
        //loop until first station matches
        while(curr->next != NULL && curr->StationID != station1)
            curr = curr->next;
        //from first station add next station time until end station is reached
        while(curr->StationID != station2)
        {
            if (curr == NULL)
                break;
            res += curr->NextStationCost;
            curr = curr->next;
        }
        return res;
    }

    if (direction == "Backward"){
        //loop list until the end first
        while(curr->next != NULL)
            curr = curr->next;

        //traverse backward until first station matches
        while(curr->prev != NULL && curr->StationID != station1)
            curr = curr->prev;
        //from first station add next station time until end station is reached
        while(curr->StationID != station2)
        {
            if (curr == NULL)
                break;
            res += curr->PreviousStationCost;
            curr = curr->prev;
        }
        return res;
    }
    return 0;
}
