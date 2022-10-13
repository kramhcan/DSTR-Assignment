#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
//Joey's Edit Request
//Second edit test

//Linked List node -- stations
class Node {
    public:
        string StationID;
        string StationName;
        //Previous station
        string PreviousStationID;
        string PreviousStationName;
        int PreviousStationDistance;
        // double PreviousStationCost;
        //Next station
        string NextStationID;
        string NextStationName;
        int NextStationDistance;
        // double NextStationCost;

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
        void AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance);
        // void AddStationBack(Node** head, string newID, string newName, int previousID, string previousName, double previousDistance, double previousCost, string nextID, string nextName, double nextDistance, double nextCost);
        void ViewAllStations(Node* head);
        double CalculatePriceByDistance(Node* head, string direction);
        int CalculateTimeByDistance(Node* head, string direction);

        int DisplaySelectionOfPositionsReturnCount(Node* head);
        void DisplayAdminMenu(Node* hd);
};


class Queue {
    public:
        string* username;
        string* password;
        string* role;

        int capacity, front, rear;
        // int * count;

        Queue(int size)
        {
            username = new string[size];
            password = new string[size];
            role = new string[size];

            front = rear = 0;
            capacity = size;
            // count = new int;
        }
        void Enqueue(string username, string password, string role);
        void LoginUser(Node* hd, Station st);
        int ValidateLogin(string name, string password);
};

#pragma region LinkedList
void Station::AddStationFront(Node** head, string newID, string newName, string previousID, string previousName, int previousDistance)
{
	Node* newNode = new Node;
	Node* last = *head;

	newNode->StationID = newID;
	newNode->StationName = newName;
	newNode->PreviousStationID = previousID;
	newNode->PreviousStationName = previousName;
	newNode->PreviousStationDistance = previousDistance;
	// // newNode->PreviousStationCost = previousCost;
	// newNode->NextStationID = nextID;
	// newNode->NextStationName = nextDistance;
	newNode->NextStationDistance = 0;
    // // newNode->NextStationCost = nextCost;
	newNode->next = nullptr;

    // If list is empty, make new head
	if (*head == NULL)
	{
		*head = newNode;
		return;
	}

    
	while (last->next != NULL)
		last = last->next;



    //change next of last node as well as the next station values
	last->next = newNode;

    last->NextStationID = newID;
    last->NextStationName = newName;
    last->NextStationDistance = previousDistance;

    //make last node as previous of new node
    newNode->prev = last;

	return;
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

//Displays summary of all stations
void Station::ViewAllStations(Node* head)
{
    Node* curr = head;
    string choice;
    bool IsValid = true;
    
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

    return count;
}

#pragma endregion

#pragma region Queue
    void Queue::Enqueue(string usr, string pwd, string rl)
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
            return st.DisplayAdminMenu(hd);
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

#pragma endregion

#pragma region
void Station::DisplayAdminMenu(Node* hd)
{
    int selection;
    cout<<"\nWelcome back, Admin. What do you want to do today?" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. View all stations\n";
    cout<<"2. Add a new station\n";
    cout<<"3. Exit system\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    //If selection is outside the range of optioons
    if (selection <= 0 || selection > 3) { 
        cout<<"\nInvalid option, please select again. \n";
        return DisplayAdminMenu(hd);
    }
    // if (selection == 1) { return ViewAllStations(hd)}
    return;
}

void DisplayStartOptions(Queue q, Node* hd, Station st)
{
    int selection;
    cout<<"\n*****KUALA LUMPUR LIGHT RAIL TRANSIT (LRT) TICKET PURCHASE SYSTEM*****" << endl;
    cout<<"========== Please enter the corresponding option number ==========" << endl;
    cout<<"1. Login\n";
    cout<<"2. Register\n";
    cout<<"==================================================================" <<endl;
    cout<<"Selection >> ";
    cin >> selection;
    if(selection == 1) { return q.LoginUser(hd, st); }
    if(selection == 2) { 
        //Register user function
    }
    cout<<"\nInvalid option, please select again.\n";
    return DisplayStartOptions(q, hd, st);
}

void ReturnToAdminMenu(){
    // int res = 0;
    // cout<<"Return to menu? (Enter '1')"<<endl;
    // cin >> res;
    // if (res == 1){
    //     DisplayAdminMenu();
    // }
}

int main()
{
    Node* head = NULL;
    Station station;
    //Add default stations
    station.AddStationFront(&head, "SS01", "Titiwangsa", "N/A", "N/A", 0);
    station.AddStationFront(&head, "SS02", "PTWC", "SS01", "Titiwangsa", 4);
    station.AddStationFront(&head, "SS03", "Sultan Ismail", "SS02", "PTWC", 8);
    station.AddStationFront(&head, "SS04", "Majlis Jamek", "SS03", "Sultan Ismail", 8);
    station.AddStationFront(&head, "SS05", "Plaza Rakyat", "SS04", "Majlis Jamek", 6);
    station.AddStationFront(&head, "SS06", "Hang Tuah", "SS05", "Plaza Rakyat", 10);
    station.AddStationFront(&head, "SS07", "Pudu", "SS06", "Hang Tuah", 5);
    station.AddStationFront(&head, "SS08", "Chan Sow Lin", "SS07", "Pudu", 5);

    //sussy
    //Add default users
    Queue q(5);
    q.Enqueue("usr0", "1234", "admin");
    q.Enqueue("usr1", "1234", "admin");
    q.Enqueue("usr2", "1234", "admin");

    DisplayStartOptions(q, head, station);

    // DisplayStartOptions(q, station);
    //     if(q.LoginUser() == 1){
    //         option = DisplayAdminMenu();
    //         if (option == 1) { station.ViewAllStations(head);}
    //     } else {

    //     }
    // }
    return 0;
}

// push pull lmfao
//pekyen push
//mark push
//pekyen branch